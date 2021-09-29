#include "bsp.h"
#include "bsp_gpio.h"

#define LED 17

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
    uint8_t rec_buf[10] = {0};
    
    if( copy_from_user( rec_buf, buf, len ) > 0) {
        pr_err("ERROR: Not all the bytes have been copied from user\n");
    }
    
    pr_info("Write Function : GPIO_17 Set = %c\n", rec_buf[0]);
    
    if (rec_buf[0]=='1') {
        //set the GPIO value to HIGH
        bsp_gpio_write(LED, HIGH);
    } else if (rec_buf[0]=='0') {
        //set the GPIO value to LOW
        bsp_gpio_write(LED, LOW);
    } else {
        pr_err("Unknown command : Please provide either 1 or 0 \n");
    }
    return len;
}

static int __init etx_driver_init(void)
{
    /*Allocating Major number*/
    if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
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
    if((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL){
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }
    
    /*Creating device*/
    if((device_create(dev_class,NULL,dev,NULL,"etx_device")) == NULL){
        pr_err( "Cannot create the Device \n");
        goto r_device;
    }
    
    /*Init bsp gpio*/
    bsp_gpio_init();
    bsp_gpio_set_output(LED);

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

static void __exit etx_driver_exit(void)
{
    bsp_gpio_write(LED, LOW);
    bps_gpio_deinit();
    
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "GPIO removed Successfully...\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbeTronicX <embetronicx@gmail.com>");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("2:1.0");