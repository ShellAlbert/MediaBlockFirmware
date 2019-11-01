/**
 * @file zcmd_parse.h
 * @date July 3,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief define network protocol parse module
 */
#ifndef _ZCMD_PARSE_H__
#define _ZCMD_PARSE_H__
#include <zdata_types.h>
#include <zclient_affair.h>
#include <zprotocol.h>
#include <zdevice_interface.h>

/**
 * added 8 bytes fixed frame head data.
 */
extern zint32_t
add_zpktnet_fixed_head (ZPKTNET *pktnet);

extern zint32_t
send_lower_layer (zint32_t sockfd, zuint8_t *buffer, zuint32_t buflen);

extern zint32_t
send_zpknet (ZPKTNET *pktnet);

/**
 * @brief query IMB Card information
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
extern zint32_t
cmd_query_card_info (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * @brief query CPU information
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
extern zint32_t
cmd_query_cpu_info (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * @brief query memory information
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
extern zint32_t
cmd_query_mem_info (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * @brief command parse for read/write fpga register
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
extern zint32_t
cmd_read_write_fpga_register (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo,
			      ZPKTNET *pktnet);

/**
 * @brief transfer DMA data
 * @param cbs
 * @param pkt
 * @param pktnet
 * @param buffer
 * @param buflen
 */
extern zint32_t
cmd_transfer_dma_data (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

extern zint32_t
cmd_open_device_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);


/**
 * Play mode control.
 * Modified by zhangshaoyan at November 21,2014.
 * Note:
 * Move Play mode control from SDK to IMB server.
 */
extern zint32_t
cmd_play_mode_start (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
extern zint32_t
cmd_play_mode_pause (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
extern zint32_t
cmd_play_mode_forward (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
extern zint32_t
cmd_play_mode_backward (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
extern zint32_t
cmd_play_mode_stop (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

#endif //_ZCMD_PARSE_H__
/**
 * the end of file,tagged by zsy
 */
