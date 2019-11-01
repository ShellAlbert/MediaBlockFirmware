ftp -v << EOF
open 192.168.10.53
user test test
binary
get tcpserver
bye
EOF
