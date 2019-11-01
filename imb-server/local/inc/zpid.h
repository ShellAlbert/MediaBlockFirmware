/**
 * @file zpid.h
 * @brief read/write pid to file
 * @author shell.albert@gmail.com
 */
#ifndef _ZPID_H__
#define _ZPID_H__
#include <zdata_types.h>

#define LOCK_PID_FILE_NAME	"imb-server.pid"

/**
 * @brief read parent pid
 */
extern pid_t
pid_read_from_file (void);

/**
 * @brief write parent pid to file
 */
extern zint32_t
pid_write_to_file (zint32_t fd, pid_t pid);

/**
 * @brief lock pid file
 * @return -1:error,fd:success
 */
extern zint32_t
pid_lock_file (void);

////////////////////////////
///	ATTENTION HERE !!!!!!!!!!!!!!!!!
/////   All data stored in MemoryBuffer must be split into char bytes ////////////

/**
 * @brief byte order convert
 */
extern void
int32_to_char8x4 (const uint32_t data_int32, uint8_t *data_char8);
extern void
char8x4_to_int32 (const uint8_t *data_char8, uint32_t *data_int32);
#endif //_ZPID_H__
/**
 * the end of file,tagged by ZSY
 */
