#!/bin/bash
times=0
while true
do 
echo -e "get MX53UG.pdf from arm,wait.... \c"
#./autoftp.sh
wget ftp://192.168.10.53:21/iMX53RM.pdf
if [ $? -ne  0 ];then
echo "error!!!!!!"
break
fi
echo "get done."
let times=$times+1
echo "times=$times"
done
