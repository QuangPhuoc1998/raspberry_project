/****************************************************************************//**
*  \file       spi_ssd1306_driver.c
*
*  \details    Simple linux driver (SPI Slave Protocol Driver)
*
*  \author     EmbeTronicX
*
*  \Tested with Linux raspberrypi 5.10.27-v7l-embetronicx-custom+
*
*******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>  
#include <linux/gpio.h>  
#include <linux/spi/spi.h>
#include "bsp.h"
#include "bsp_gpio.h"

#define SPI_BUS_NUM             (  1 )    // SPI 1

static struct spi_device *etx_spi_device;

//Register information about your slave device
struct spi_board_info etx_spi_device_info = 
{
  .modalias     = "spi_driver",
  .max_speed_hz = 100000,              // speed your device (slave) can handle
  .bus_num      = SPI_BUS_NUM,          // SPI 1
  .chip_select  = 0,                    // Use 0 Chip select (GPIO 18)
  .mode         = SPI_MODE_0            // SPI mode 0
};

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

/*************** Driver functions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);
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
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
  
  return 0;
}
/*
** This function will be called when we write the Device file
*/ 
static ssize_t etx_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
  uint8_t rx  = 0x00;
  uint8_t rec_buf[10] = {0};
    
  bsp_gpio_write(16, LOW);
  if( copy_from_user( rec_buf, buf, len ) > 0) {
      pr_err("ERROR: Not all the bytes have been copied from user\n");
  }
  pr_info("Received = 0x%02X \n", rec_buf[0]);

  if( etx_spi_device )
  {    
    struct spi_transfer  tr = 
    {
      .tx_buf  = &rec_buf[0],
      .rx_buf = &rx,
      .len    = 1,
    };

    spi_sync_transfer( etx_spi_device, &tr, 1 );
  }
  
  pr_info("Received = 0x%02X \n", rx);
  bsp_gpio_write(16, HIGH);
  return( len );
}

/****************************************************************************
 * Name: etx_spi_init
 *
 * Details : This function Register and Initilize the SPI.
 ****************************************************************************/
static int __init etx_spi_init(void)
{
  int     ret;
  struct  spi_master *master;
  
  master = spi_busnum_to_master( etx_spi_device_info.bus_num );
  if( master == NULL )
  {
    pr_err("SPI Master not found.\n");
    return -ENODEV;
  }
   
  // create a new slave device, given the master and device info
  etx_spi_device = spi_new_device( master, &etx_spi_device_info );
  if( etx_spi_device == NULL ) 
  {
    pr_err("FAILED to create slave.\n");
    return -ENODEV;
  }
  
  // 8-bits in a word
  etx_spi_device->bits_per_word = 8;

  // setup the SPI slave device
  ret = spi_setup( etx_spi_device );
  if( ret )
  {
    pr_err("FAILED to setup slave.\n");
    spi_unregister_device( etx_spi_device );
    return -ENODEV;
  }
  
  pr_info("SPI driver Registered\n");

  /*Allocating Major number*/
    if((alloc_chrdev_region(&dev, 0, 1, "spi_Dev")) <0){
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
    if((dev_class = class_create(THIS_MODULE,"spi_class")) == NULL){
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }
    
    /*Creating device*/
    if((device_create(dev_class,NULL,dev,NULL,"spi_device")) == NULL){
        pr_err( "Cannot create the Device \n");
        goto r_device;
    }
    
    /*Init bsp gpio*/
    bsp_gpio_init();
    bsp_gpio_set_output(16);
    bsp_gpio_write(16, HIGH);
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

  return 0;
}
 
/****************************************************************************
 * Name: etx_spi_exit
 *
 * Details : This function Unregister and DeInitilize the SPI.
 ****************************************************************************/
static void __exit etx_spi_exit(void)
{ 
  if( etx_spi_device )
  {
    spi_unregister_device( etx_spi_device );    // Unregister the SPI slave
    pr_info("SPI driver Unregistered\n");
  }
}
 
module_init(etx_spi_init);
module_exit(etx_spi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbeTronicX <embetronicx@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - SPI Slave Protocol Driver");
MODULE_VERSION("1.44");