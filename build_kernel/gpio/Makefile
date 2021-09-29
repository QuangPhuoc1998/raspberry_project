obj-m += gpio_driver.o
gpio_driver-objs += main.o bsp_gpio.o

TARGET = pi@192.168.0.10:phuoc/driver/gpio
FILE_DRIVER = gpio_driver.ko

KDIR = /home/phuoc/phuoc/raspberry_linux/linux
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean

update:
	scp $(FILE_DRIVER) $(TARGET)