/**
 *@file zip_server.h
 *@date August 23,2014
 *@version 1.0
 *@author zhangshaoyan shell.albert@gmail.com
 *@brief
 *This is a UDP server routine,listen on specified UDP port,
 *waiting for UDP packets,it will search the map table to
 *find out the active key for FPGA serial number,and send
 *it back to UDP client.
 */
#ifndef ZIP_SERVER_H_
#define ZIP_SERVER_H_
#include <zdata_types.h>
/**
 * @brief default listen UDP port.
 */
#define ZIP_SERVER_PORT	1987

typedef struct
{
  zuint32_t type; ///<packet type field.
  zuint32_t data; ///<packet data field.
} ZPACKET_UDP;


/**
 * @brief read a UDP packet from socket buffer.
 * parse it and give response.
 * @param fd
 */
extern zint32_t
zip_read_packet_and_parse_it (zint32_t fd);

/**
 * @brief async receive thread.
 * async receive data from socket.
 */
extern void*
thread_zip_server (void* arg);
#endif /* ZIP_SERVER_H_ */
