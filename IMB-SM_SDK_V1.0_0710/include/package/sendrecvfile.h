/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName	:
FileName	:	sendrecvfile.h
Author		:	tangquanfa@oristartech.com
Date		:	2012/03/29
Version		:	1.0
Description
History 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef SEND_RECV_FILE_H
#define SEND_RECV_FILE_H

//#define _LARGEFILE_SOURCE
//#define _LARGEFILE64_SOURCE
//#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

#include "package/mysendrecv.h"

int sendfile( int fd, int fp );
int recvfile( int fd, int fp,  unsigned long long filesize );

//[IMBSM v1.0_DCEventLog] added by chenjingdong, 2014-05-30 start
#ifdef SM_LOG_DOWNLOAD_ON_TLS
#define MAX_TRANS_DATA_LEN 32*1024  //
int getReportName(CTLS_Translate_Server *tls_server, SSL *connection, unsigned char* pName);
int sendLogReport(CTLS_Translate_Server *tls_server, SSL *connection, unsigned char* pName);
int sendfile( CTLS_Translate_Server *tls_server, SSL *connection, int fp, int nTimeOut = MAX_TIMEOUT );
int sendfile( CTLS_Translate_Client *tls_client, int fp, int nTimeOut = MAX_TIMEOUT );
int recvfile( CTLS_Translate_Server *tls_server, SSL *connection, int fp,  unsigned long long filesize, int nTimeOut = MAX_TIMEOUT );
int recvfile( CTLS_Translate_Client *tls_client, int fp,  unsigned long long filesize, int nTimeOut = MAX_TIMEOUT );
#endif
//[IMBSM v1.0_DCEventLog] end

#endif
