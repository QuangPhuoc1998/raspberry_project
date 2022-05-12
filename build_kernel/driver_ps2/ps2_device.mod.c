#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x44afce, "module_layout" },
	{ 0xae651774, "cdev_del" },
	{ 0xaaad239e, "cdev_init" },
	{ 0xf9a482f9, "msleep" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xead0d68d, "gpio_to_desc" },
	{ 0xd132b42f, "device_destroy" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x999e8297, "vfree" },
	{ 0x5507ab8e, "spi_setup" },
	{ 0xe943dd1c, "kthread_create_on_node" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x5f754e5a, "memset" },
	{ 0xfef57891, "spi_busnum_to_master" },
	{ 0xc5850110, "printk" },
	{ 0x963ae58e, "kthread_stop" },
	{ 0x1d37eeed, "ioremap" },
	{ 0xf457f599, "spi_new_device" },
	{ 0x54535e55, "gpiod_direction_input" },
	{ 0xdb96c8a6, "device_create" },
	{ 0xc966bd13, "gpiod_direction_output_raw" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xb52423b7, "spi_sync" },
	{ 0xc2bcb805, "cdev_add" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xc1830521, "wake_up_process" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xfe990052, "gpio_free" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x7e2c4910, "gpiod_set_raw_value" },
	{ 0xedc03953, "iounmap" },
	{ 0xf0462214, "class_destroy" },
	{ 0xa036fee1, "spi_unregister_device" },
	{ 0x938ca289, "gpiod_get_raw_value" },
	{ 0x84e8af7f, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C1C323505C8C1FB28C896F6");
