/*
 * zsubtitle_handler.h
 *
 *  Created on: 2014年12月2日
 *      Author: shell.albert
 */

#ifndef ZSUBTITLE_HANDLER_H_
#define ZSUBTITLE_HANDLER_H_
#include <zprotocol.h>
#include <zclient_affair.h>
extern zint32_t
cmd_subtitle_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
extern zint32_t
cmd_subtitle_overlay_element (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
#endif /* ZSUBTITLE_HANDLER_H_ */
