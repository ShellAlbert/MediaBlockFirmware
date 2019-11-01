#filename:Makefile
#ver:1.0
#author:zhangshaoyan
#shell.albert@gmail.com
#Copyright(C) oristartech.com
#description:compile makefile for driver & test program

obj-m := x86_pci_vnic.o

x86_pci_vnic-objs := zpci_vnic_mix.o zpci_drv.o zvnic_drv.o

MODULE_DIR := $(shell pwd)


#CentOS6.5-32bit
KERNEL_DIR=/usr/src/kernels/2.6.32-431.20.3.el6.i686/


CC=gcc

CXX=g++

EXTRA_CFLAGS+= -I ../sdk/libz/inc -I $(MODULE_DIR)

DEPS_KEYACT = ../sdk/libz/src/libz_pci.c 

all:
	make -C ${KERNEL_DIR} M=$(MODULE_DIR)  modules $(EXTRA_CFLAGS)
install:
	sudo insmod x86_pci_vnic.ko
remove:
	sudo rmmod x86_pci_vnic

#keyact test application
keyact:keyact.c 
	$(CC) keyact.c $(DEPS_KEYACT) $(EXTRA_CFLAGS) -DAV_ALL 	   -o keyact_avall -g
	$(CC) keyact.c $(DEPS_KEYACT) $(EXTRA_CFLAGS) -DVIDEO_ONLY -o keyact_videoonly -g
	$(CC) keyact.c $(DEPS_KEYACT) $(EXTRA_CFLAGS) -DAUDIO_ONLY -o keyact_audioonly -g

#common
clean:
	rm  -rf *.mod.* *.o *.ko modules.* Module.*  *.ko.*
	rm  -rf keyact_avall 
	rm -rf keyact_videoonly
	rm -rf keyact_audioonly
#the end of file,for reading convenience
#shell.albert@gmail.com
