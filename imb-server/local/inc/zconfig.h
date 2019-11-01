/**
 * @file zconfig.h
 * @author shell.albert@gmail.com
 * @date July 10,2014
 */
#ifndef _ZCONFIG_H__
#define _ZCONFIG_H__
#include <zdata_types.h>

#define MAXKEYLEN	128

#define DEF_ZCONFIG_FILE	"imb-server.conf"

/**
 * @brief keyname define here
 */
#define KEYNAME_LISTEN_PORT		"LISTEN_PORT"
#define DEFAULT_LISTEN_PORT		1987

#define KEYNAME_MAX_CLIENTS_NUM		"MAX_CLIENTS_NUM"
#define DEFAULT_MAX_CLIENTS_NUM		1

#define KEYNAME_FIFO_DEPTH		"FIFO_DEPTH"
#define DEFAULT_FIFO_DEPTH		100

#define KEYNAME_FIFO_PKT_BUFSIZE	"FIFO_PKT_BUFSIZE"
#define DEFAULT_FIFO_PKT_BUFSIZE	(2*1024*1024) //2MB

#define KEYNAME_FPGA_LIC_KEY_MSB	"FPGA_LIC_KEY_MSB"
#define KEYNAME_FPGA_LIC_KEY_LSB	"FPGA_LIC_KEY_LSB"

/**
 * @brief trim left space of a string
 */
extern zint32_t
zconfig_trim_left (zint8_t *src, zint8_t *dest);

/**
 * @brief trim right space of a string
 */
extern zint32_t
zconfig_trim_right (zint8_t *src, zint8_t *dest);

/**
 * @brief get key value from the default configure file
 */
extern zint32_t
zconfig_get_key (const zint8_t *keyname, zint8_t *keyvalue);
#endif //_ZCONFIG_H__
/**
 * the end of file,tagged by zsy
 */
