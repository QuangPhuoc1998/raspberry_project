cmd_/home/phuoc/Myproject/Rasp_project/Kernel/spi/modules.order := {   echo /home/phuoc/Myproject/Rasp_project/Kernel/spi/spi_driver.ko; :; } | awk '!x[$$0]++' - > /home/phuoc/Myproject/Rasp_project/Kernel/spi/modules.order
