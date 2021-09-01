all: event_drv.ko mmp_drv.ko
event_drv.ko:
	cd event_drv && make && make install
mmp_drv.ko:
	cd mmap_drv && make && make install

.PHONY:
clean:
	cd event_drv && make clean && cd ../mmap_drv && make clean
