#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include "/usr/src/3.18.0/arch/arm/include/asm/io.h"
#include "./address_map_arm.h"

/* Meta information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Brenda Barbosa, Camila Boa Morte, Maike de Oliveira");
MODULE_DESCRIPTION("Um driver para realizar a comunicação com o processador gráfico na FPGA");

/* Barramentos do processador gráfico */
#define DATAA 0x80
#define DATAB 0x70
#define WRFULL 0xb0
#define WRREG 0xc0
#define SCREEN 0xa0
#define RESET_PULSECOUNTER 0x90

/*Opcodes */
#define WBR 0 //0000
#define WSM 1 //0001
#define WBM 2 //0010
#define DP 3 //0011

/*Nome do driver */
#define DRIVER_NAME "colenda_driver"

#define BUFF_SIZE 8

/* Definição da(s) thread(s) */
static struct task_struct *kthread_buffer_manager;

/* Definição de mutexes */
DEFINE_MUTEX(read_mutex);
DEFINE_MUTEX(write_mutex);

/*Driver data*/
static struct
{
  dev_t devnum;
  struct cdev cdev;
  size_t buffer_size;
  atomic_t counter; //numero de processos que estão conectados ao driver
  void *LW_virtual;
  volatile int *data_a;
  volatile int *data_b;
  volatile int *wr_full;
  volatile int *wr_reg;
  volatile int *screen;
  volatile int *reset_pulsecounter;
  
} colenda_driver_data;

/* Task realizada pela thread */
int manage_instruction_buffer(void *data){



  return 0;
}


static int colenda_driver_open(struct inode *device_file, struct file *instance){
  pr_info("%s: open was called!\n", DRIVER_NAME);

  if(atomic_inc_return(&colenda_driver_data.counter) == 1){
    wake_up_process(kthread_buffer_manager);
    pr_info("%s: kthread buffer manager is running now!", DRIVER_NAME);
  }

  return 0;
}

static int colenda_driver_close(struct inode *device_file, struct file *instance){
  pr_info("%s: close was called!\n", DRIVER_NAME);

  if(atomic_dec_and_test(&led_driver_data.counter)){
    kthread_stop(kthread_buffer_manager);
    pr_info("%s: kthread buffer manager stopped!", DRIVER_NAME); //fix bug with completion
  }

  return 0;
}

static ssize_t colenda_driver_write(struct file *file, const char __user *buffer, size_t count,
loff_t *ppos){
  char kbuffer[colenda_driver_data.buffer_size];
  ssize_t size = min(sizeof(kbuffer), count); 

  /* Atualizando offset passado pelo usuario*/
  *ppos = 0;

  if(size == 0){ //sem bytes a serem escritos
    return 0;
  }

  *colenda_driver_data.wr_reg = 0;
  

  if (!*colenda_driver_data.screen){
    printk("tela em renderização\n");
    return -1;
  }
  
  /* Copiando buffer do usuário*/
  if(copy_from_user(kbuffer, buffer, size)){
    return -EFAULT;
  }

  if(*colenda_driver_data.wr_full){
    
    printk("fila cheia\n");
    return -1;
  }
  //printk("%lld\n", kbuffer);

  
  *colenda_driver_data.data_a = (kbuffer[4]) << 24 | (kbuffer[5]) << 16 | (kbuffer[6]) << 8 | (kbuffer[7]);
  *colenda_driver_data.data_b = (kbuffer[0]) << 24 | (kbuffer[1]) << 16 | (kbuffer[2]) << 8 | (kbuffer[3]);
  



  //Envia sinal para escrita na fila
  *colenda_driver_data.wr_reg = 1;
  *colenda_driver_data.wr_reg = 0;
  return size;

}

/* Registrando callbacks*/
static const struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = colenda_driver_open,
  .release = colenda_driver_close,
  .write = colenda_driver_write
};


static int __init colenda_driver_init(void){

  int result;
  /*Alocando device number*/
  result = alloc_chrdev_region(&colenda_driver_data.devnum, 0, 1, DRIVER_NAME);

  /*Inicializando o tamanho do buffer*/
  colenda_driver_data.buffer_size = BUFF_SIZE;

  if(result)
  {
    pr_err("%s: failed to allocate device number!\n",DRIVER_NAME);
    return result;
  }

  /*Registrando dispositivo de caractere*/
  cdev_init(&colenda_driver_data.cdev, &fops);

  /* Inicializando contador de processos */
  atomic_set(&led_driver_data.counter, 0);

  /*Mapeando lightweight HPS-to-FPGA brigde*/
  colenda_driver_data.LW_virtual = ioremap(LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
  
  /*Mapeando barramentos e sinais do processador grafico*/
  colenda_driver_data.data_a = (int*) (colenda_driver_data.LW_virtual + DATAA);
  colenda_driver_data.data_b = (int*) (colenda_driver_data.LW_virtual + DATAB);
  colenda_driver_data.wr_reg = (int*) (colenda_driver_data.LW_virtual + WRREG);
  colenda_driver_data.wr_full = (int*) (colenda_driver_data.LW_virtual + WRFULL);
  colenda_driver_data.screen = (int*) (colenda_driver_data.LW_virtual + SCREEN);
  colenda_driver_data.reset_pulsecounter = (int*) (colenda_driver_data.LW_virtual + RESET_PULSECOUNTER);

  /* Criando thread de gerenciamento de instruções */
  kthread_buffer_manager = kthread_create(manage_instruction_buffer, &t1, "instruction_kthread");

  /* Criando kthread de gerenciamento do buffer de instruções */
  if (kthread_buffer_manager != NULL)
  {
    pr_info("%s: kthread buffer manager created!", DRIVER_NAME);
  }else{
    pr_err("%s: failed to create kthread buffer manager!", DRIVER_NAME); //refactor this part with go to
    iounmap(colenda_driver_data.LW_virtual);
    unregister_chrdev_region(colenda_driver_data.devnum, 1);
    return -1; //change to a error code
  }

  /* Adicionando dispositivo de caractere */
  result = cdev_add(&colenda_driver_data.cdev, colenda_driver_data.devnum, 1);

  if (result)
  {
    pr_err("%s: char device registration failed!\n",DRIVER_NAME);
    iounmap(colenda_driver_data.LW_virtual);
    unregister_chrdev_region(colenda_driver_data.devnum, 1);
    return result;
  }

  pr_info("%s: initialized!\n",DRIVER_NAME);
  return 0;

}

static void __exit colenda_driver_exit(void){
  iounmap(colenda_driver_data.LW_virtual);
  cdev_del(&colenda_driver_data.cdev);
  unregister_chrdev_region(colenda_driver_data.devnum, 1);
  pr_info("%s: exiting!\n",DRIVER_NAME);

}

module_init(colenda_driver_init);
module_exit(colenda_driver_exit);