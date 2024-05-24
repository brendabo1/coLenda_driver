#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<asm/io>

/* Meta information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Brenda Barbosa, Camila Boa Morte, Maike de Oliveira");
MODULE_DESCRIPTION("Um driver para realizar a comunicação com o processador gráfico na FPGA");

/* Barramentos do processador gráfico */
#define DATAA 0x80
#define DATAB 0x70
#define WRFULL 0xb0
#define WRREG 0xc0

/*Nome do driver */
#define DRIVER_NAME "colenda_driver"
#define BUFF_SIZE 64 //tamanho das instruções


/*Driver data*/
static struct
{
  dev_t devnum;
  struct cdev cdev;
  char next_instruction[BUFF_SIZE];
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

static ssize_t colenda_driver_read(struct file *file, char __user buffer, size_t count, 
loff_t *ppos){ 
    //TODO
}

static ssize_t colenda_driver_write(struct file *file, const char __user buffer, size_t count,
loff_t *ppos){
  int size = BUFF_SIZE;

  if(size > count){
    size = count;
  }

  if(copy_from_user(colenda_driver_data.next_instruction, buffer, size)){
    return -EFAULT;
  }

  //processing data from buffer here
  
  return size;

}

/* Registrando callbacks*/
static const struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = colenda_driver_open,
  .release = colenda_driver_close,
  .write = colenda_driver_write,
  .read = colenda_driver_read,

};


static int __init colenda_driver_init(void){

  int result;
  /*Alocando device number*/
  result = alloc_chrdev_region(&colenda_driver_data.devnum, 0, 1, DRIVER_NAME);

  if(result)
  {
    pr_err("%s: failed to allocate device number!\n",DRIVER_NAME);
    return result;
  }

  /*Registrando dispositivo de caractere*/
  cdev_init(&colenda_driver_data.cdev, &fops);

  result = cdev_add(&colenda_driver_data.cdev, colenda_driver_data.devnum, 1);

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

