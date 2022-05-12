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
/*--- Peripheral header ---*/
#include <linux/gpio.h> 
/*--- Op header ----*/
#include "Op_HeaderDefine.h"
#include "Op_HeaderFlag.h"
#include "Op_HeaderVariable.h""
/*--- Mid header ---*/
#include "Mid_DialControl.h"
#endif // _MAIN_H_