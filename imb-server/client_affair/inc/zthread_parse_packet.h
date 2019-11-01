/**
 * @file zparse_packet_thread.h
 * @brief parse packet from clients
 * @date July 14,2014
 * @author shell.albert@gmail.com
 */
#ifndef _ZTHREAD_PARSE_PACKET_H__
#define _ZTHREAD_PARSE_PACKET_H__
#include <zdata_types.h>
#include <zfifo.h>
#include <zfpga_para.h>
#include <zclient_affair.h>
#include <zdevice_interface.h>
#include <zcmd_parse.h>
/**
 * @brief parse packet
 * check if the FIFO has valid data,if has parse it,
 * else block
 */
extern void*
thread_parse_packet (void* arg);

/**
 * @brief async write data to driver.
 * read data from FIFO & write to driver
 */
extern int32_t
read_fifo_write_device (ZTHREAD_CBS *cbs, ZPKTNET *pktnet);

#endif //_ZTHREAD_PARSE_PACKET_H__
/**
 * the end of file,tagged by zsy
 */
