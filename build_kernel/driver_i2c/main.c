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
    
/*--- I2C config begin ---*/

static struct i2c_adapter * bmp_i2c_adapter = NULL;
static struct i2c_client * bmp280_i2c_client = NULL;

/* Defines for device identification */ 
#define I2C_BUS_AVAILABLE	1		/* The I2C Bus available on the raspberry */
#define SLAVE_DEVICE_NAME	"GY30"	/* Device and Driver Name */
#define BMP280_SLAVE_ADDRESS	0x23		/* BMP280 I2C address */

static const struct i2c_device_id bmp_id[] = {
		{ SLAVE_DEVICE_NAME, 0 }, 
		{ }
};

static struct i2c_driver bmp_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};

static struct i2c_board_info bmp_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, BMP280_SLAVE_ADDRESS)
};

/*--- I2C config end ---*/

static dev_t dev = 0;
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
  uint8_t temp[2] = {0};

  //uint16_t temperature = 0;
  uint16_t uwI2CData= 0;

  uwI2CData = i2c_smbus_read_word_data(bmp280_i2c_client, 0x13);
  temp[0] = (uwI2CData & 0xFF00 ) >> 8;
  temp[1] = (uwI2CData & 0x00FF );
  //temperature = uwI2CData / 1;
  pr_info("Data = %d\n", uwI2CData);
  //pr_info("Light = %d\n", temperature);
  len = 2;

  if( copy_to_user(buf,temp, len) > 0) {
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
  int ret = -1;
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
   
  /*--- I2C init ---*/

  bmp_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);
  if(bmp_i2c_adapter != NULL) 
  {
	  pr_info("I2C available\n");
	  bmp280_i2c_client = i2c_new_client_device(bmp_i2c_adapter, &bmp_i2c_board_info);
	  if(bmp280_i2c_client != NULL) 
	  {
		  if(i2c_add_driver(&bmp_driver) != -1) 
		  {
			  ret = 0;
		  }
		  else
		  {
			  printk("Can't add driver...\n");
			  goto i2c_err;
		  }
		  i2c_put_adapter(bmp_i2c_adapter);
	  }
  }
  /*--------- ------*/

  pr_info("Device Driver Insert...Done!!!\n");
  return ret;

i2c_err:

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
  i2c_unregister_device(bmp280_i2c_client);
  i2c_del_driver(&bmp_driver);
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