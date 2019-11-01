/**
 *@filename zsignal.c
 *@date May 28,2014
 *@author :zsy
 *@version 1.0
 *@brief define signal handler for SIG_INT & SIG_PIPE
 */
#include <zsignal.h>
#include <signal.h>
#include <zdata_types.h>
/**
 * @brief SIG_INT handler,when user type Ctrl+C to terminate server.
 * parent will send SIGINT signal to all children
 */
void
parent_signal_handler_int (int signo)
{
  /**
   * send SIG_INT to all child process.
   */
#if (ZDBG_LEVEL & ZDBG_SIGNAL)
  printf("signal:parent_signal_handler_int()\n");
#endif

  /**
   *
   If pid is 0, sig shall be sent to all  processes  (excluding  an
   unspecified  set  of system processes) whose process group ID is
   equal to the process group ID of the sender, and for  which  the
   process has permission to send a signal.
   */
  kill (0, SIGINT); //kill all sub process,very important!!!

#if (ZDBG_LEVEL & ZDBG_SIGNAL)
  printf("signal:zsdk_daemon exit\n");
#endif

  //wait for all child process to exit
  //waitpid(-1,NULL,WNOHANG);
  //ZDBG("wait finish\n");
  //exit(0);
  return;
}

/**
 * @brief SIG_PIPE handler,when socket was disconnected by remote.
 * child process will recv SIGPIPE when remove clients close socket.
 */
void
child_signal_handler_int (int signo)
{
#if (ZDBG_LEVEL & ZDBG_SIGNAL)
  printf("signal:client exit with signal %d\n",signo);
#endif
  //do some clean here
  //zfifo_destroy(&cbs->fifo);
  //exit(0);
}

/**
 *the end of file
 */
