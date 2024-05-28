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

/*Opcodes */
#define WBR 0 //0000
#define WSM 1 //0001
#define WBM 2 //0010
#define DP 3 //0011

/*Nome do driver */
#define DRIVER_NAME "colenda_driver_teste"

#define BUFF_SIZE 65 

#define MAJOR 241


/*Driver data*/
static struct
{
  struct cdev cdev;
  size_t buffer_size;
  void *LW_virtual;
  volatile int *data_a;
  volatile int *data_b;
  volatile int *wr_full;
  volatile int *wr_reg;
  
} colenda_driver_data;

static int colenda_driver_open(struct inode *device_file, struct file *instance){
  pr_info("%s: open was called!\n", DRIVER_NAME);
  return 0;
}

static int colenda_driver_close(struct inode *device_file, struct file *instance){
  pr_info("%s: close was called!\n", DRIVER_NAME);
  return 0;
}

static ssize_t colenda_driver_write(struct file *file, const char __user *buffer, size_t count,
loff_t *ppos){
  char kbuffer[colenda_driver_data.buffer_size];
  ssize_t size = min(sizeof(kbuffer), count); 
  long long int value = 0;
  long long int opcode = 0;
  int i = 0;

  /* Atualizando offset passado pelo usuario*/
  *ppos = 0;

  if(size == 0){ //sem bytes a serem escritos
    return 0;
  }

  while (*colenda_driver_data.wr_full) //esperando espaço vazio na fila do processador grafico
  {
  }
  
  /* Copiando buffer do usuário*/
  if(copy_from_user(kbuffer, buffer, size)){
    return -EFAULT;
  }

  printk("%s\n", kbuffer);

  /* Convertendo string em inteiro*/ 
  while(kbuffer[i] != '\0'){
    if(kbuffer[i] == '1'){
      value = (value << 1) | 1;
      printk("value: %d\n", value);
      printk("caracter: %c\n", kbuffer[i]);
    }else if(kbuffer[i] == '0') {
      value = value << 1;
      printk("value: %d\n", value);
      printk("caracter: %c\n", kbuffer[i]);
    }
    i++;
  }

  /*String não pode ser convertida*/
  if(value == -1){
    pr_err("%s: fail to converto buffer to int", DRIVER_NAME);
    return -1;
  }

  /*Extrai o campo opcode*/
  opcode = (value & 0b1111);

  /* Separando as informações referentes ao dataA e dataB de acordo com a instrução*/
  switch (opcode)
  {
  //instrução WBR
  case WBR:
    *colenda_driver_data.data_a = (value & 0b111111111);
    *colenda_driver_data.data_b = (value >> 9);
    break;

  //instrução WSM
  case WSM:
    *colenda_driver_data.data_a = (value & 0b111111111111111111);
    *colenda_driver_data.data_b = (value >> 18);
    break;

  //instrução WBM
  case WBM:
    *colenda_driver_data.data_a = (value & 0b1111111111111111);
    *colenda_driver_data.data_b = (value >> 16);
    break;

  //instrução DP
  case DP:
    *colenda_driver_data.data_a = (value & 0b11111111);
    *colenda_driver_data.data_b = (value >> 8);
    break;
  }

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
  result = register_chrdev(241, "colenda_driver_teste", &fops);

  /*Inicializando o tamanho do buffer*/
  colenda_driver_data.buffer_size = BUFF_SIZE;

  if(result)
  {
    pr_err("%s: failed to allocate device number!\n Alocou em: %d %d",DRIVER_NAME, result>>20, result&0xfffff);
    return result;
  }
  if(result == 0)
  {
    pr_info("Registrou o driver em: %d", MAJOR);
  }
  else
  {
    pr_info("não resgistrou. F");
    return -1;
  }

  /*Registrando dispositivo de caractere*/
  cdev_init(&colenda_driver_data.cdev, &fops);

  result = cdev_add(&colenda_driver_data.cdev, MAJOR, 1);

  if (result)
  {
    pr_err("%s: char device registration failed!\n",DRIVER_NAME);
    unregister_chrdev_region(colenda_driver_data.devnum, 1);
    return result;
  }

  /*Mapeando lightweight HPS-to-FPGA brigde*/
  colenda_driver_data.LW_virtual = ioremap(LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
  
  /*Mapeando barramentos e sinais do processador grafico*/
  colenda_driver_data.data_a = (int*) (colenda_driver_data.LW_virtual + DATAA);
  colenda_driver_data.data_b = (int*) (colenda_driver_data.LW_virtual + DATAB);
  colenda_driver_data.wr_reg = (int*) (colenda_driver_data.LW_virtual + WRREG);
  colenda_driver_data.wr_full = (int*) (colenda_driver_data.LW_virtual + WRFULL);


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
