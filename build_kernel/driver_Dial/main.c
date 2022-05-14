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

#define GLOBAL_DEFINE (1)

#include "main.h"

#include "Op_InterruptManager.h"
#include "Mid_DialControl.h"

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
 
 
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
  len = 2;
  uint8_t ubDataToSend[2]; 
  ubDataToSend[0] = g_ubUpDownMoveValue;
  ubDataToSend[1] = g_bMoveEncoderCount;
  g_ubUpDownMoveValue = NO_CHANGE;

  if( copy_to_user(buf, ubDataToSend, len) > 0) {
    pr_err("ERROR: Not all the bytes have been copied to user\n");
  }

  return 0;
}

/*
** This function will be called when we write the Device file
*/ 
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
  uint8_t rec_buf[10] = {0};
  
  if( copy_from_user( rec_buf, buf, len ) > 0) {
    pr_err("ERROR: Not all the bytes have been copied from user\n");
  }
  
  return len;
}

/*
** Module Init function
*/ 
static int __init etx_driver_init(void)
{
  /*Allocating Major number*/
  if((alloc_chrdev_region(&dev, 0, 1, DRIVER_NAME)) <0){
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
  /*--- User init ---*/
  
  if(Mid_DialInit() != 0)
  {
    pr_err( "Cannot init Dial \n");
    goto r_device;
  }
  

  if(Op_InterruptManagerInit() != 0)
  {
    pr_err( "Thread error\n");
    goto r_device;
  }

  /*----------------*/
  pr_info("Device Driver Insert...Done!!!\n");
  return 0;
 
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
  Mid_DialDeinit();
  Op_InterruptManagerDeinit();
  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  cdev_del(&etx_cdev);
  unregister_chrdev_region(dev, 1);
  pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE(MODULE_LICENSE_NAME);
MODULE_AUTHOR(MODULE_AUTHOR_NAME);
MODULE_DESCRIPTION(MODULE_DESCRIPTION_NAME);
MODULE_VERSION(MODULE_VERSION_NAME);