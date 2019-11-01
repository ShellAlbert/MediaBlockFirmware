/**
 * @file zclient_affair.c
 * @date May 28,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief handle client affair
 */
#include <zclient_affair.h>
#include <zthread_parse_packet.h>
#include <zthread_async_recv.h>
#include <zip_server.h>
#include <zfifo.h>
#include <zdevice_interface.h>
#include <zprotocol.h>
#include <zdata_types.h>
#include <zcmd_parse.h>
#include <zsignal.h>
#include <zconfig.h>
#include <pthread.h>
#include <zsm_client.h>
/**
 * @brief global variable declare here
 */
ZTHREAD_CBS *cbs;

/**
 * @brief set exit flag when receive SIGTERM
 */
void
client_affair_handler_SIGTERM (zint32_t signo)
{
  if (cbs != NULL)
    {
      /**
       * set thread exit flag.
       */
      pthread_mutex_lock (&cbs->lock_exit);
      cbs->flag_exit = Thread_Status_Exit;
      pthread_mutex_unlock (&cbs->lock_exit);

      /**
       * signal all conditions.
       */
      pthread_mutex_lock (&cbs->lock_fifo);
      pthread_cond_signal (&cbs->cond_fifo_notfull);
      pthread_cond_signal (&cbs->cond_fifo_notempty);
      pthread_mutex_unlock (&cbs->lock_fifo);
    }
  return;
}
/**
 * @brief create a child process to handle new connection
 */
void
process_client_affair (zint32_t fd_socket)
{
  zuint32_t fifo_depth;
  zint8_t buffer[128];
  zuint32_t fpga_key_msb, fpga_key_lsb;

  do
    {
      /**
       * step1:check socket fd valid
       */
      if (fd_socket < 0)
	{
	  ZPrintError("invalid socket fd,exit\n");
	  break;
	}

      /**
       * step2:read configure file to get FPGA_LIC_KEY_LSB
       */
      if (zconfig_get_key (KEYNAME_FPGA_LIC_KEY_LSB, buffer) == 0)
	{
	  /**
	   * read success.
	   */
	  if ((fpga_key_lsb = strtoul (buffer, NULL, 16)) == 0)
	    {
	      /**
	       * convert failed.
	       */
	      ZPrintError("convert KEYNAME_FPGA_LIC_KEY_LSB failed!\n");
	      break;
	    }
	}
      else
	{
	  /**
	   * read failed.
	   */
	  ZPrintError("read KEYNAME_FPGA_LIC_KEY_LSB failed!\n");
	  break;
	}

      printf ("info:FPGA_LIC_KEY_LSB=%x\n", fpga_key_lsb);

      /**
       * step3:read configure file to get FPGA_LIC_KEY_MSB.
       */
      if (zconfig_get_key (KEYNAME_FPGA_LIC_KEY_MSB, buffer) == 0)
	{
	  /**
	   * read success.
	   */
	  if ((fpga_key_msb = strtoul (buffer, NULL, 16)) == 0)
	    {
	      /**
	       * convert failed.
	       */
	      ZPrintError("convert KEYNAME_FPGA_LIC_KEY_MSB failed!\n");
	      break;
	    }
	}
      else
	{
	  /**
	   * read failed.
	   */
	  ZPrintError("convert KEYNAME_FPGA_LIC_KEY_MSB failed!\n");
	  break;
	}

      printf ("info:FPGA_LIC_KEY_MSB=%x\n", fpga_key_msb);

      /**
       * step4:read configure file to get FIFO_DEPTH
       */
      if (zconfig_get_key (KEYNAME_FIFO_DEPTH, buffer) == 0)
	{
	  /**
	   * read success.
	   */
	  if ((fifo_depth = strtoul (buffer, NULL, 10)) == 0)
	    {
	      /**
	       * convert failed,use default value.
	       */
	      printf ("warning:convert KEYNAME_FIFO_DEPTH failed,use default value!\n");
	      fifo_depth = DEFAULT_FIFO_DEPTH;
	    }
	}
      else
	{
	  /**
	   * read failed,use default value.
	   */
	  printf ("warning:read KEYNAME_FIFO_DEPTH failed,use default value!\n");
	  fifo_depth = DEFAULT_FIFO_DEPTH;
	}

      printf ("info:FIFO_DEPTH:%d\n", fifo_depth);

      /**
       * step5:create thread control blocks.
       */
      cbs = (ZTHREAD_CBS*) malloc (sizeof(ZTHREAD_CBS));
      if (cbs == NULL)
	{
	  printf("allocate ZTHREAD_CBS failed:%s\n", strerror (errno));
	  break;
	}


      /**
       * initial thread constrol blocks.
       */
      cbs->fd_socket = fd_socket;
      cbs->counter_rx = 0;
      cbs->rx_cnt_dma = 0;

      /***************FIFO****************/
      /**
       * create fifo for store data from client(sdk).
       */
      if (zfifo_allocate (&cbs->fifo, fifo_depth) < 0)
	{
	  printf("zfifo_allocate() failed,child process exit\n");
	  break;
	}

      /**
       * initial pthread related.
       */
      pthread_mutex_init (&cbs->lock_fifo, NULL);
      pthread_cond_init (&cbs->cond_fifo_notfull, NULL);
      pthread_cond_init (&cbs->cond_fifo_notempty, NULL);

      /**
       * reset fd status.
       */
      device_init (&cbs->m_dev);
      pthread_cond_init (&cbs->cond_fd_device, NULL);

      /////////////exit flag///////////////////
      pthread_mutex_init (&cbs->lock_exit, NULL);
      cbs->flag_exit = Thread_Status_Running;      ///<reset flag

      /**
       * add support for sm client & sm server.
       * added by zhangshaoyan at October 17,2014.
       * to solve network crossing problem.
       */
      char sm_server_ip[] = "192.168.10.53";
      int sm_server_port = 6002;
      cbs->m_sm = new Inner_SecurityManager (sm_server_ip, sm_server_port);
      printf ("SM:ipaddress=%s,port=%d\n", sm_server_ip, sm_server_port);

      /**
       * create two work thread here
       * one for asynchronous read from socket
       * another for asynchronous packet parse
       */
      if (pthread_create (&cbs->tid_async_recv, NULL, thread_async_recveive, (void*) cbs))
	{
	  printf("pthread_create() failed:%s\n", strerror (errno));
	  break;
	}


      if (pthread_create (&cbs->tid_parse_packet, NULL, thread_parse_packet, (void*) cbs))
	{
	  printf("pthread_create() failed:%s\n", strerror (errno));
	  break;
	}

      /**
       * parent will send SIGTERM when it asks its children to exit
       */
      signal (SIGTERM, client_affair_handler_SIGTERM);

      /**
       * wait for all threads to terminated.
       */
      pthread_join (cbs->tid_parse_packet, NULL);
      pthread_join (cbs->tid_async_recv, NULL);
      printf ("info:two threads exit,child process exit\n");

      /**
       * close device file.
       */
      device_close (&cbs->m_dev);
      close (cbs->fd_socket);
      fflush (NULL);
    }
  while (0);

  /**
   * do some clean work here.
   */
  if (cbs->fifo != NULL)
    {
      zfifo_destroy (&cbs->fifo);
      cbs->fifo = NULL;
    }
  if (cbs->m_sm != NULL)
    {
      delete cbs->m_sm;
      cbs->m_sm = NULL;
    }
  if (cbs != NULL)
    {
      free (cbs);
      cbs = NULL;
    }
  printf ("info:process %d exit ok!\n", getpid ());

  /**
   * must do not use exit()!!!
   * it will cause all fd close
   * here,we should use _exit() to exit sub process
   */
  _exit (0);
  return;
}

/**
 * the end of file,tagged by ZSY
 */
