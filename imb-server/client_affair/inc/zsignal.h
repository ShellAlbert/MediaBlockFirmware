/**
 *@filename zsignal.h
 *@date May 28,2014
 *@author :zsy
 *@version 1.0
 *@brief define signal handler for SIG_INT & SIG_PIPE
 */
#ifndef _ZSIGNAL_H__
#define _ZSIGNAL_H__

/**
 * @brief SIG_INT handler,when user type Ctrl+C to terminate server.
 * parent will send SIGINT signal to all children
 */
extern void
parent_signal_handler_int (int signo);


/**
 * @brief SIG_PIPE handler,when socket was disconnected by remote.
 * child process will recv SIGPIPE when remove clients close socket.
 */
extern void
child_signal_handler_int (int signo);

#endif //_ZSIGNAL_H__
/**
 *the end of file
 */
