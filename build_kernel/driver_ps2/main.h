#ifndef _MAIN_H_
#define _MAIN_H_

/*--- Systems header ---*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h> 
/*--- Dynamic allocation ---*/
#include <linux/slab.h>
/*--- Peripheral header ---*/
#include <linux/gpio.h> 
#include <linux/spi/spi.h>
/*--- Hal header ---*/
#include "Hal_Spi.h"
/*--- BSP heaer ---*/
#include "bsp_gpio.h"
/*--- Op header ----*/
#include "Op_Header_Define.h"
#include "Op_Header_Flag.h"
#include "Op_Header_Variable.h"
/*--- Dev heaer ---*/
#include "Dev_Ps2.h"

#endif // _MAIN_H_