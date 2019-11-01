/**
 * @file zasync_recv_thread.h
 * @brief async socket receive thread,read data from socket,
 * re-array them into complete frames then copy frames into buffer.
 * @date July 10,2014
 * @author shell.albert@gmail.com
 */
#ifndef _ZTHREAD_ASYNC_RECV_H__
#define _ZTHREAD_ASYNC_RECV_H__
#include <zdata_types.h>
#include <zfifo.h>
#include <zfpga_para.h>
#include <zclient_affair.h>

/**
 * @brief async receive thread.
 * async receive data from socket.
 */
extern void*
thread_async_recveive (void* arg);

/**
 * @brief async receive thread receive data from socket,
 * and write it into temporary buffer.
 * this function runs in block mode
 */
extern int32_t
read_socket_write_buffer (ZTHREAD_CBS *cbs, ZRECVBUFFER *pbuffer);

/**
 * @brief parse temporary buffer,re-array data to a complete frame,
 * copy frames into FIFO
 * @param cbs
 * @param buffer
 * @param len
 * @param pkt
 */
extern int32_t
read_buffer_write_fifo (ZTHREAD_CBS *cbs, zuint8_t *buffer, zuint32_t len);

#endif //_ZTHREAD_ASYNC_RECV_H__
/**
 * the end of file,tagged by zsy
 */
