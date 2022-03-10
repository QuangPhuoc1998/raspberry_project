DRIVER_NAME = temp

obj-m += $(DRIVER_NAME).o 
$(DRIVER_NAME)-objs += main.o

TARGET = pi@192.168.0.50:MyProject/Kernel
FILE_DRIVER = $(DRIVER_NAME).ko

KDIR = /home/phuoc/Myproject/Kernel/linux
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean

update:
	scp $(FILE_DRIVER) $(TARGET)