/**
 * @file zsdk_daemon.c
 * @date May 28,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief this daemon will run in IMB PCI x86 board
 * as a tcp/ip network server
 * it receives data from client(sdk) through network,buffer data in memory,
 * then download data to FPGA through driver
 */

#include <zdata_types.h>
#include <zsignal.h>
#include <zclient_affair.h>
#include <zip_server.h>
#include <zpid.h>
#include <signal.h>
#include <zconfig.h>
#include <sys/select.h>
#include <zerrno.h>

typedef struct
{
  zint32_t fd_server;
  zint32_t fd_client;

  struct sockaddr_in addr_server;
  struct sockaddr_in addr_client;

  zuint32_t listen_port; //listen on which port
  zuint32_t max_clients_num; //maximum connected clients
  zuint32_t cnt_clients; //counter connected clients

  zuint32_t flag_status; ///<parent process status flag
} ZNETRES;
/**
 * @brief global variable declare here
 */
ZNETRES znet;

/**
 * @brief Ctrl+C to terminate
 */
void
handler_SIGINT (int signo)
{
  /**
   *If  pid  is  0,  sig  shall be sent to all processes
   *(excluding an unspecified set of system processes)
   *whose process
   *group ID is equal to the process group ID of the sender,
   *and for which the process has permission to send a signal.
   */
  kill (0, SIGTERM);
  return;
}
/**
 * @brief set exit flag when receive SIGTERM
 */
void
handler_SIGTERM (int signo)
{
  pid_t pid_child;
  printf ("info:received SIGTERM signal.\n");
  znet.flag_status = Thread_Status_Exit;
  /**
   * wait for all child process to exit.
   */
  printf ("info:waiting for all processes to exit...");
  while ((pid_child = waitpid (-1, NULL, WNOHANG)) > 0)
    {
      /**
       * nothing to do here.
       */
    }
  printf ("done!\n");
  return;
}

int
main (int argc, char **argv)
{
  pid_t pid_child;
  socklen_t len_addr;
  zint32_t rc;
  zint32_t fd_lock;
  zint8_t buffer[128];

  struct timeval tv;
  fd_set rd_fds;
  pthread_t tid_ip_server;	///<UDP IP server thread.

  /**
   * initial exit flag.
   */
  znet.flag_status = Thread_Status_Running;

  /**
   * try to lock pid file.
   */
  if ((fd_lock = pid_lock_file ()) == -1)
    {
      ZPrintError("failed to lock PID file!\n");
      return -1;
    }
  if (pid_write_to_file (fd_lock, getpid ()) != 0)
    {
      ZPrintError("write PID to lock file failed:%s\n", strerror (errno));
      return -1;
    }
//  if ((pid = pid_read_from_file ()) == -1)
//    {
//      ZDBG("read pid failed\n");
//    }
//  else
//    {
//      ZDBG("pid=%d\n", pid);
//    }

  /**
   * read configure file to get listen port.
   */
  if (zconfig_get_key (KEYNAME_LISTEN_PORT, buffer) == 0)
    {
      /**
       * read success.
       */
      if ((znet.listen_port = strtoul (buffer, NULL, 10)) == 0)
	{
	  /**
	   * convert failed,use default listen port.
	   */
	  znet.listen_port = DEFAULT_LISTEN_PORT;
	}
    }
  else
    {
      /**
       * read failed,use default listen port.
       */
      znet.listen_port = DEFAULT_LISTEN_PORT;

    }

  /**
   * read configure file to get maximum connect clients.
   */
  if (zconfig_get_key (KEYNAME_MAX_CLIENTS_NUM, buffer) == 0)
    {
      /**
       * read success.
       */
      if ((znet.max_clients_num = strtoul (buffer, NULL, 10)) == 0)
	{
	  /**
	   * convert failed,use default value.
	   */
	  znet.max_clients_num = DEFAULT_MAX_CLIENTS_NUM;
	}
    }
  else
    {
      /**
       * read failed,use default value.
       */
      znet.max_clients_num = DEFAULT_MAX_CLIENTS_NUM;
    }
  printf ("info:maximum clients number limited to %d\n", znet.max_clients_num);
  znet.cnt_clients = 0;

  /**
   * create ip_server thread for UDP broadcast.
   */
  if (pthread_create (&tid_ip_server, NULL, thread_zip_server, (void*) cbs))
    {
      printf ("error:create ip server thread failed!\n");
      return -1;
    }

  /**
   * create tcp stream socket.
   */
  if ((znet.fd_server = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      ZPrintError("create socket failed:%s\n", strerror (errno));
      return -1;
    }

  /**
   * enable REUSEADDR feature.
   */
  rc = 1;
  if (setsockopt (znet.fd_server, SOL_SOCKET, SO_REUSEADDR, &rc, sizeof(len_addr)) == -1)
    {
      ZPrintError("setsockopt() failed:%s\n", strerror (errno));
      close (znet.fd_server);
      return -1;
    }

  /**
   * prepare the sockaddr_in structure.
   */
  bzero (&znet.addr_server, sizeof(znet.addr_server));
  znet.addr_server.sin_family = AF_INET;
  znet.addr_server.sin_addr.s_addr = INADDR_ANY;
  /**
   *caution:must be htons().
   *use htonl() will cause accept() failed!!!
   */
  znet.addr_server.sin_port = htons (znet.listen_port);

  /**
   * bind.
   */
  if (bind (znet.fd_server, (struct sockaddr *) &znet.addr_server, sizeof(znet.addr_server)) == -1)
    {
      ZPrintError("bind failed:%s\n", strerror (errno));
      close (znet.fd_server);
      return -1;
    }

  /**
   * listen.
   */
  if (listen (znet.fd_server, 5) == -1)
    {
      ZPrintError("listen failed:%s\n", strerror (errno));
      close (znet.fd_server);
      return -1;
    }

  /**
   * install signal handler.
   */
  signal (SIGINT, handler_SIGINT);
  signal (SIGTERM, handler_SIGTERM);

  printf ("<IMBServer> :Listening on TCP[%d]...\n", znet.listen_port);
  /**
   *main process accept new connection
   *and fork a new process to handle it
   */
  while (1)
    {
      ///timeout
      tv.tv_sec = 1;  ///<1s
      tv.tv_usec = 0;
      FD_ZERO(&rd_fds);
      FD_SET(znet.fd_server, &rd_fds);
      rc = select (znet.fd_server + 1, &rd_fds, NULL, NULL, &tv);
      if (rc < 0)
	{
	  ZPrintError("select():%s\n", strerror (errno));
	  break;  ///<exit while(1)
	}
      else if (rc == 0)
	{
	  //timeout,check exit flag
	  if (znet.flag_status == Thread_Status_Exit)
	    {
	      printf ("info:detected exit flag!\n");
	      break;  ///<exit while(1)
	    }
	}
      else if (rc > 0)
	{
	  if (FD_ISSET(znet.fd_server, &rd_fds))
	    {
	      len_addr = sizeof(struct sockaddr);

	      printf ("info:waiting for new connection...\n");

	      znet.fd_client = accept (znet.fd_server, (struct sockaddr *) &znet.addr_client, &len_addr);

	      if (znet.fd_client == -1)
		{
		  ZPrintError("accept failed,ignore this client:%s\n", strerror (errno));
		  continue;
		}
	      /**
	       * fork a new child process to handle connection.
	       */
	      printf ("info:fork a new process for client\n");
	      pid_child = fork ();
	      if (pid_child == -1)
		{
		  ZPrintError("fork() failed:%s\n", strerror (errno));
		  close (znet.fd_client);
		  continue;
		}
	      else if (pid_child == 0)
		{
		  //child process

		  /**
		   *child process will copy all data from parent process
		   *so here we close it
		   */
		  close (znet.fd_server);
		  process_client_affair (znet.fd_client);
		}
	      else
		{
		  /**
		   * parent process
		   */
		  close (znet.fd_client);
		  printf ("info:created %d process to handle.\n", pid_child);
		}
	    }
	}		  ///<select()
    }		  ///<while(1)

  pthread_join (tid_ip_server, NULL);
  printf ("<IPServer>:exit!\n");
  printf ("<IMBServer>:exit!\n");
  return 0;
}

/**
 * the end of file,tagged by ZSY
 */
