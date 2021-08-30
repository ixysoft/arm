obj-m :=event_drv.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

install:
	[ ! -x /dev/ubuntu_event ] && sudo insmod event_drv.ko && sudo chmod 666 /dev/ubuntu_event || echo 123
clean:
	rm *.o *.ko *.mod.c
