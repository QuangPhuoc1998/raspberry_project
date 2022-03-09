obj-m += spi_driver.o 
spi_driver-objs += main.o bsp_gpio.o

TARGET = pi@192.168.0.50:MyProject/Kernel
FILE_DRIVER = spi_driver.ko

KDIR = /home/phuoc/Myproject/Kernel/linux
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean

update:
	scp $(FILE_DRIVER) $(TARGET)