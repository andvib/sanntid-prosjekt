obj-m := mymodule.o

KERNELDIR := /home/student/Downloads/Exercise10/buildroot/output/build/linux-2.6.35.4
CROSS := /home/student/Downloads/Exercise10/buildroot/output/staging/usr/bin/avr32-linux-

all:
	make ARCH=avr32 CROSS_COMPILE=$(CROSS) -C $(KERNELDIR) M=$(shell pwd) modules
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
