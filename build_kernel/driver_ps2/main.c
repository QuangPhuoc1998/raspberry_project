/***************************************************************************//**
*  \file       main.c
*
*  \details    template driver
*
*  \author     Pham Quang Phuoc
*
*  \Tested with Linux raspberrypi 5.10.92-v7l+
*
*******************************************************************************/

#include "main.h"
    
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
 
static struct task_struct *etx_thread;

int thread_function(void *pv) 
{
 msleep(2000);
 PS2_SetInit();
 msleep(2000);
 while(!kthread_should_stop())
 {
   PS2_Read();
   msleep(100);
 } 
 return 0; 
}

/*************** Driver functions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t * off);
/******************************************************/
 
//File operation structure 
static struct file_operations fops =
{
  .owner          = THIS_MODULE,
  .read           = etx_read,
  .write          = etx_write,
  .open           = etx_open,
  .release        = etx_release,
};

/*
** This function will be called when we open the Device file
*/ 
static int etx_open(struct inode *inode, struct file *file)
{
  pr_info("Device File Opened...!!!\n");
  return 0;
}

/*
** This function will be called when we close the Device file
*/
static int etx_release(struct inode *inode, struct file *file)
{
  pr_info("Device File Closed...!!!\n");
  return 0;
}

/*
** This function will be called when we read the Device file
*/ 
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
  uint8_t aubPs2ReadData[9] = {0};

  uint8_t i = 0;

  for(i = 0 ; i < 9 ; i++)
  {
    pr_info("Data[%d] = 0x%X", i, Data[i]);
    aubPs2ReadData[i] = Data[i];
  }
  /*
  aubPs2ReadData[0] = PS2_KEY;
  aubPs2ReadData[1] = PS2_LX;
  aubPs2ReadData[2] = PS2_LY;
  aubPs2ReadData[3] = PS2_RX;
  aubPs2ReadData[4] = PS2_RY;
  */
  len = 9;
  if( copy_to_user(buf, aubPs2ReadData, len) > 0) {
    pr_err("ERROR: Not all the bytes have been copied to user\n");
  }

  return 0;
}

/*
** This function will be called when we write the Device file
*/ 
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
  uint8_t * TxData = vmalloc(sizeof(uint8_t)*len);
  
  if( copy_from_user( TxData, buf, len ) > 0) {
    pr_err("ERROR: Not all the bytes have been copied from user\n");
  }


  vfree(TxData);
  return len;
}

/*
** Module Init function
*/ 
static int __init etx_driver_init(void)
{
  /*Allocating Major number*/
  if((alloc_chrdev_region(&dev, 0, 1, "temp_Dev")) <0){
    pr_err("Cannot allocate major number\n");
    goto r_unreg;
  }
  pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
  /*Creating cdev structure*/
  cdev_init(&etx_cdev,&fops);
 
  /*Adding character device to the system*/
  if((cdev_add(&etx_cdev,dev,1)) < 0){
    pr_err("Cannot add the device to the system\n");
    goto r_del;
  }
 
  /*Creating struct class*/
  if((dev_class = class_create(THIS_MODULE,CLASS_NAME)) == NULL){
    pr_err("Cannot create the struct class\n");
    goto r_class;
  }
 
  /*Creating device*/
  if((device_create(dev_class,NULL,dev,NULL,DEVICE_NAME)) == NULL){
    pr_err( "Cannot create the Device \n");
    goto r_device;
  }
  /*User init here*/
  if(Dev_Ps2SoftInit() != 0)
  {
    pr_err( "Cannot init Sp2 \n");
    goto r_peripheral;
  }
  etx_thread = kthread_create(thread_function,NULL,"PS2 Thread");
  if(etx_thread) {
      wake_up_process(etx_thread);
  } else {
      pr_err("Cannot create kthread\n");
      goto r_device;
  }
  /*--------------*/
  pr_info("Device Driver Insert...Done!!!\n");
  return 0;

r_peripheral:
  
r_device:
  device_destroy(dev_class,dev);
r_class:
  class_destroy(dev_class);
r_del:
  cdev_del(&etx_cdev);
r_unreg:
  unregister_chrdev_region(dev,1);
  
  return -1;
}

/*
** Module exit function
*/ 
static void __exit etx_driver_exit(void)
{
  /*--- User deinit here ---*/
  Dev_Ps2SoftDeInit();
  kthread_stop(etx_thread);
  /*------------------------*/
  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  cdev_del(&etx_cdev);
  unregister_chrdev_region(dev, 1);
  pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbeTronicX <embetronicx@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - GPIO Driver");
MODULE_VERSION("1.32");