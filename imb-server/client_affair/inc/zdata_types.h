/**
 * @file zdata_types.h
 * @date May 28,2014
 * @version 1.0
 * @author zhangshaoyan shell.albert@gmail.com
 * @brief redefine data types for easy cross-platform planting work
 */

#ifndef _ZDATA_TYPES_H__
#define _ZDATA_TYPES_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <sys/select.h>
#include <sys/wait.h>

typedef char zint8_t;
typedef unsigned char zuint8_t;

typedef int zint32_t;
typedef unsigned int zuint32_t;

typedef long long zint64_t;
typedef unsigned long long zuint64_t;

typedef float zreal32_t;
typedef double zreal64_t;

#if 1
#define ZDBG(fmt,args...) printf(fmt,##args)
#else
#define ZDBG(fmt,args...) 
#endif

/**
 * define different level to show different debug messages.
 * 0:no debug message output.
 * bit0==1,0x1<<0: thread asynchronous receive.
 * bit1==1,0x1<<1: thread parse packet.
 * bit2==1,0x1<<2: call function flow info.
 *
 */
#define ZDBG_THREAD_ASYNC_RECV		(0x1<<0)
#define ZDBG_MSG_THREAD_PARSE_PACKET	(0x1<<1)
#define ZDBG_MSG_CALL_FUNCTION_FLOW	(0x1<<2)
#define ZDBG_SIGNAL		(0x1<<3)  ///<signal message
#define ZDBG_INIT		(0x1<<4) ///<process initial messages.
#define ZDBG_DEV_INTERFACE	(0x1<<5) ///<device file interface.
#define ZDBG_CMD_PARSE		(0x1<<6) ///<command parse messages.
#define ZDBG_PACKET_PARSE	(0x1<<7) ///<packet parse.
#define ZDBG_ACTIVE_FPGA	(0x1<<8) ///<active FPGA Intopix core.
#define ZDBG_FIFO		(0x1<<9) ///<FIFO messages.
#define ZDBG_PID		(0x1<<10) ///<PID lock.

//#define ZDBG_LEVEL  	(0) ///<no debug message.
#define ZDBG_LEVEL  ZDBG_MSG_THREAD_ASYNC_RECV ///<only thread asynchronous receive.
//#define ZDBG_LEVEL  ZDBG_MSG_THREAD_PARSE_PACKET ///<only thread parse packet.
//#define ZDBG_LEVEL	ZDBG_MSG_CALL_FUNCTION_FLOW///<work flow info.
//#define ZDBG_LEVEL (0x1<<0)|(0x1<<1) ///<thread async_recv & parse packet.



//log macro control.
#define ZLogAsyncRecvThread	1


#endif //_ZDATA_TYPES_H__
/**
 * the end of file,tagged by ZSY
 */
