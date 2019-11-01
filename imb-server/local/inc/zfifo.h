/**
 * @file zfifo.h
 * @date May 30,2014
 * @author zhangshaoyan@oristartech.com
 * @brief define FIFO related codes
 */
#ifndef _ZFIFO_H__
#define _ZFIFO_H__
#include <zdata_types.h>
#include <zprotocol.h>
/**
 * @brief FIFO structure
 */
typedef struct
{
  zuint8_t size; //total package in FIFO
  zuint8_t free; //free position in FIFO
  zuint8_t rd_pos; //read position
  zuint8_t wr_pos; //write position

  ZPKT *pkt; //point to ZPKT package structure
} ZFIFO;

/**
 * @brief FIFO status define
 */
#define FIFO_EMPTY	0x0
#define FIFO_HAS_DATA	0x1
#define FIFO_FULL	0x2

/**
 * @brief allocate a FIFO in memory,return its base address
 */
extern zint32_t
zfifo_allocate (ZFIFO **fifo, zuint32_t size);

/**
 * @brief destroy a FIFO,release its memory
 */
extern void
zfifo_destroy (ZFIFO**fifo);

/**
 * @brief put a packet to FIFO
 */
extern zint32_t
zfifo_put_element (ZFIFO *fifo, const ZPKT *pkt);

/**
 * @brief get free position
 */
extern ZPKT *
zfifo_get_free_position (ZFIFO *fifo);
extern zint32_t
zfifo_dec_free_number (ZFIFO *fifo);


/**
 * @brief get a packet from FIFO
 */
extern zint32_t
zfifo_get_element (ZFIFO *fifo, ZPKT *pkt);

/**
 * @brief get busy position
 */
extern ZPKT *
zfifo_get_busy_position(ZFIFO *fifo);
extern zint32_t
zfifo_inc_free_number(ZFIFO *fifo);


/**
 * @brief return the free number in FIFO
 */
extern zint32_t
zfifo_get_free (const ZFIFO*fifo);

/**
 * @brief return the total size in FIFO
 */
extern zint32_t
zfifo_get_size (const ZFIFO *fifo);

/**
 * @brief return the valid number in FIFO
 */
extern zint32_t
zfifo_get_total (const ZFIFO *fifo);

#endif //_ZFIFO_H__
/**
 * the end of file,tagged by ZSY
 */
