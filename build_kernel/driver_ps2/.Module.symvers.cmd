cmd_/home/phuoc/Myproject/Rasp_project/Kernel/driver_ps2/Module.symvers := sed 's/ko$$/o/' /home/phuoc/Myproject/Rasp_project/Kernel/driver_ps2/modules.order | scripts/mod/modpost -m -a   -o /home/phuoc/Myproject/Rasp_project/Kernel/driver_ps2/Module.symvers -e -i Module.symvers   -T -