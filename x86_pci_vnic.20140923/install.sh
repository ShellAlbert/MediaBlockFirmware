#!/bin/bash
#brief compile driver & create device file
#May 20,2014
#zhangshaoyan@oristartech.com


echo "do clean work..."
#make clean
echo "done"

echo "execute compile module work..."
#make
echo "done"

echo "check directory exists or not ...?"
if [ -d "/dev/mvc_card" ];then
	echo "yes"
else
	echo "no,create it now"
	mkdir /dev/mvc_card
fi

echo "check device file exists or not ...?"
if [ -e "/dev/mvc_card/card0" ];then
	echo "yes"
else
	echo "no,create it now"
	mknod /dev/mvc_card/card0 c 2014 0
	chmod 777 /dev/mvc_card/card0
	ls -l /dev/mvc_card
fi

#echo "compile test file:keyact..."
#make keyact
#echo "done"

echo "insert module to kernel..."
insmod x86_pci_vnic.ko
echo "done"

echo "configure zvnic0..."
ifconfig zvnic0 hw ether 00:01:02:03:04:05
ifconfig zvnic0 192.168.10.86
ifconfig zvnic0
echo "done"

#make clean
#truncate /var/log/messages --size=0

#the end of file
