obj-m :=mmp_drv.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) M=$(PWD) modules
install:
	sudo insmod mmp_drv.ko && sudo chmod 666 /dev/ubuntu_lcd 
clean:
	rm *.o *.ko *.mod.c
