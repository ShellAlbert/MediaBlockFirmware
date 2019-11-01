/**
 * @file zclient_affair.h
 * @date May 28,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief handle client affair
 */
#ifndef _ZCLIENT_AFFAIR_H__
#define _ZCLIENT_AFFAIR_H__

#include <zdata_types.h>
#include <zfifo.h>
#include <zfpga_para.h>
#include <zerrno.h>
#include <zdevice_interface.h>
/**
 * for SM client & SM server.
 */
#include <sm_sdk/inner_securitymanager.h>

/**
 * @brief thread & process shared data structure,
 * thread control blocks
 */
typedef struct
{
  ZFIFO *fifo; ///<FIFO
  pthread_mutex_t lock_fifo; ///<lock for FIFO
  pthread_cond_t cond_fifo_notfull; ///<condition for FIFO,not full,can write
  pthread_cond_t cond_fifo_notempty; ///<condition for FIFO,not empty,can read
  zuint32_t  fifoDMADataCounter;//counter the DMA data packets in fifo.

  zint32_t fd_socket; ///<network socket file descriptor


  pthread_cond_t cond_fd_device; ///<condition for device file

  pthread_t tid_async_recv;	///<async receive thread from socket
  pthread_t tid_parse_packet;	///<parse packet thread


  pthread_mutex_t lock_exit;	///<lock for exit flag
  zuint32_t flag_exit; ///<exit flag

  zuint32_t counter_rx; //counter for receive pkt

  zuint32_t rx_cnt_dma; //counter for DMA packet

  /**
   * for SM client & SM server.
   */
  Inner_SecurityManager *m_sm;

  /**
   * for FPGA device.
   */
  zfpga_dev m_dev;
} ZTHREAD_CBS;
extern ZTHREAD_CBS *cbs;

/**
 * @brief set exit flag when receive SIGTERM
 */
extern void
client_affair_handler_SIGTERM (zint32_t signo);
/**
 * @brief create a child process to handle new connection
 */
extern void
process_client_affair (zint32_t fd_socket);

/**
 * @brief receive buffer size for storing data read from socket
 */
#define BUFSIZE_2MB	(2*1024*1024)

/**
 * @brief receive buffer structure
 */
typedef struct
{
  zuint8_t *data; //data area
  zuint32_t size; //data area size
  zuint32_t total; //all received bytes
} ZRECVBUFFER;

#endif //_ZCLIENT_AFFAIR_H__
/**
 * the end of file,tagged by ZSY
 */
