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
  size_t buffer_pointer;
  
} char_driver_data;


static int char_driver_open(struct inode *device_file, struct file *instance){
  pr_info("%s: open was called!\n", DRIVER_NAME);
  return 0;
}

static int char_driver_close(struct inode *device_file, struct file *instance){
  pr_info("%s: close was called!\n", DRIVER_NAME);
  return 0;
}

static ssize_t char_driver_read(struct file *file, char* user_buffer, size_t count, 
loff_t *offs){

  int to_copy, not_copied, delta;

  //amout of data to copy
  to_copy = min(char_driver_data.buffer_pointer, count);
  
  //copy data to user
  not_copied = copy_to_user(user_buffer, char_driver_data.buffer, to_copy);

  delta = to_copy - not_copied;

  return delta;
  
}

static ssize_t char_driver_write(struct file *file, const char* user_buffer, size_t count,
loff_t *offs){

  int to_copy, not_copied, delta;

  //amout of data to copy
  to_copy = min(sizeof(char_driver_data.buffer), count);
  
  //copy data to user
  not_copied = copy_from_user(char_driver_data.buffer, user_buffer, to_copy);
  
  char_driver_data.buffer_pointer = to_copy;
  
  delta = to_copy - not_copied;

  return delta;

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








