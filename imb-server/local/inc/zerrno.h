/*
 * @file zerrno.h
 * @brief define error number
 * @date July 9,2014
 * @author shell.albert@gmail.com
 */
#ifndef _ZERRNO_H__
#define _ZERRNO_H__
enum
{

  /**
   * device file status code
   */
  RC_DEVFILE_OPEN_SUCCESS = 6000,
  RC_DEVFILE_OPEN_FAILED = -6001,

  /**
   * function return code
   */
  RC_SUCCESS = 0x0,
  RC_NULLPOINTER = -9000, ///<null pointer
  RC_UNKNOWN_ERR = -9001, ///<unknown error
  RC_SYSAPI = -9002, ///<call system API error.
};

/**
 * used to print error information.
 */
#define ZPrintError(fmt,args...) \
  do{ \
      fprintf(stderr,"File:%s,Line:%d\n",__FILE__,__LINE__); \
      fprintf(stderr,"Error:"); \
      fprintf(stderr,fmt,##args);\
  }while(0)

#endif //_ZERRNO_H__
/**
 * the end of file,tagged by zsy
 */
