/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName	:
FileName	:	mysendrecv.h
Author		:	tangquanfa@oristartech.com
Date		:	2012/03/29
Version		:	1.0
Description
History 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef MY_SEND_RECV_H
#define MY_SEND_RECV_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

//[IMBSM v1.0_DCEventLog] added by chenjingdong, 2014-05-30 start
#ifdef SM_LOG_DOWNLOAD_ON_TLS
#include "tls/tlstranslateserver.h"
#include "tls/tlstranslateclient.h"	
#endif
//[IMBSM v1.0_DCEventLog] end

int my_send( int fd, void *buffer, int len );
int my_recv( int fd, void *buffer, int len );

//[IMBSM v1.0_DCEventLog] added by chenjingdong, 2014-05-30 start
#ifdef SM_LOG_DOWNLOAD_ON_TLS
#define MAX_RETRY_NUM 3
#define MAX_INTERVAL_TIME 1  //
#define MAX_TIMEOUT 30  //
int tls_send( CTLS_Translate_Server *tls_server, SSL *connection, void *buffer, int len, int nTimeOut = MAX_TIMEOUT );
int tls_send( CTLS_Translate_Client *tls_client, void *buffer, int len, int nTimeOut = MAX_TIMEOUT );
int tls_recv( CTLS_Translate_Server *tls_server, SSL *connection, void *buffer, int len, int nTimeOut = MAX_TIMEOUT );
int tls_recv( CTLS_Translate_Client *tls_client, void *buffer, int len, int nTimeOut = MAX_TIMEOUT );
#endif
//[IMBSM v1.0_DCEventLog] end

#endif
