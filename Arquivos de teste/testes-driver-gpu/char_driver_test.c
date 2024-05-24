#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

/* Meta information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Camila Boa Morte");
MODULE_DESCRIPTION("A driver to...");


#define DRIVER_NAME "my_char_driver"

static struct
{
  dev_t devnum;
  struct cdev cdev;
  char buffer[256];  
} char_driver_data;


static int char_driver_open(struct inode *device_file, struct file *instance){
  pr_info("%s: open was called!\n", DRIVER_NAME);
  return 0;
}

static int char_driver_close(struct inode *device_file, struct file *instance){
  pr_info("%s: close was called!\n", DRIVER_NAME);
  return 0;
}

static ssize_t char_driver_read(struct file *file, char* __user buf, size_t count, 
loff_t *offset){

  ssize_t size = min(sizeof(char_driver_data.buffer) - *offset, count);

  if (size <= 0)
  {
    return 0;
  }

  if(copy_to_user(buf, char_driver_data.buffer+ *offset, size)){
    return -EFAULT;
  }
  
  *offset += size;

  return size;
}

static ssize_t char_driver_write(struct file *file, const char* __user buf, size_t count,
loff_t *offset){

  ssize_t size = min(sizeof(char_driver_data.buffer) - *offset, count);

  if(size <= 0){
    return 0;
  }
  if (copy_from_user(char_driver_data.buffer + *offset, buf, size))
  {
    return -EFAULT;
  }


int  result;
char *str = "7";  // Example string to be converted
int value;

result = kstrtoint(str, 2, &value);  // Convert base 10 string to integer

if (result == 0) {
    printk(KERN_INFO "Converted value: %d\n", value);
} else {
    printk(KERN_ERR "Conversion failed\n");
}

  *offset += size;
  return size;
}

static const struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = char_driver_open,
  .release = char_driver_close,
  .write = char_driver_write,
  .read = char_driver_read,

};


static int __init char_driver_init(void){

  int result;

  result = alloc_chrdev_region(&char_driver_data.devnum, 0, 1, DRIVER_NAME);

  if (result)
  {
    pr_err("%s: failed to allocate device number!\n",DRIVER_NAME);
    return result;
  }

  cdev_init(&char_driver_data.cdev, &fops);

  result = cdev_add(&char_driver_data.cdev, char_driver_data.devnum, 1);

  if (result)
  {
    pr_err("%s: char device registration failed!\n",DRIVER_NAME);
    unregister_chrdev_region(char_driver_data.devnum, 1);
    return result;
  }

  pr_info("%s: initialized!\n",DRIVER_NAME);
  return 0;

}

static void __exit char_driver_exit(void){
  cdev_del(&char_driver_data.cdev);
  unregister_chrdev_region(char_driver_data.devnum, 1);
  pr_info("%s: exiting!\n",DRIVER_NAME);

}

module_init(char_driver_init);
module_exit(char_driver_exit);








