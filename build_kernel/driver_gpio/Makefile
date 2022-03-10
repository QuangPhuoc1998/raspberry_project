obj-m += driver_gpio.o 
driver_gpio-objs += main.o

TARGET = pi@192.168.0.50:MyProject/Kernel
FILE_DRIVER = driver_gpio.ko

KDIR = /home/phuoc/Myproject/Kernel/linux
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean

update:
	scp $(FILE_DRIVER) $(TARGET)