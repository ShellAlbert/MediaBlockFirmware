/**
 * @file zthread_async_recv.h
 * @brief async socket receive thread,read data from socket,
 * re-array them into complete frames then copy frames into buffer.
 * @date July 10,2014
 * @author shell.albert@gmail.com
 */
#include <zthread_async_recv.h>
/**
 * @brief async receive thread.
 * async receive data from socket.
 */
void*
thread_async_recveive (void* arg)
{
  fd_set rd_set;
  struct timeval tv;
  zint32_t ret;
  ZTHREAD_CBS *pcbs = (ZTHREAD_CBS*) arg;
  ZRECVBUFFER *pbuffer;
  ZPKT *pkt;
  zint32_t tmp_flag_exit;

  do
    {
      ///check valid of thread structure resource
      if (pcbs == NULL)
	{
	  printf ("invalid thread control structure!\n");
	  break; //exit while(0)
	}

      ///allocate receive buffer structure
      pbuffer = (ZRECVBUFFER*) malloc (sizeof(ZRECVBUFFER));
      if (pbuffer == NULL)
	{
	  printf ("malloc() pbuffer failed:%s\n", strerror (errno));
	  break; //exit while(0)
	}

      /**
       * allocate memory for receive buffer structure.
       */
      pbuffer->data = (zuint8_t*) malloc (BUFSIZE_2MB);
      if (pbuffer->data == NULL)
	{
	  printf ("mallco() pbuffer->data failed:%s\n", strerror (errno));
	  break; //exit while(0)
	}
      pbuffer->size = BUFSIZE_2MB;

      /**
       * do not receive any bytes at initial period.
       */
      pbuffer->total = 0;

      /**
       * allocate ZPKT structure.
       */
      pkt = (ZPKT*) malloc (sizeof(ZPKT));
      if (pkt == NULL)
	{
	  printf ("malloc() pkt failed:%s\n", strerror (errno));
	  break; //exit while(0)
	}

      /**
       * allocate ZPKT->data structure for FIFO usage.
       */
      pkt->data = (zuint8_t*) malloc (ZPKT_BUF_SIZE);
      if (pkt->data == NULL)
	{
	  ZPrintError("malloc() pkt->data failed:%s\n", strerror (errno));
	  break; //exit while(0)
	}
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
      printf("async_recv:pkt=%p,pkt->data=%p\n", pkt, pkt->data);

      ///infinite loop for asynchonous socket receive work
      printf("async_recv:enter while(1)...\n");
#endif

      /**
       * detach myself.
       */
//      pthread_detach (pthread_self ());
      printf ("AsynSocketRecvThread:start\n");
      /**
       * infinite loop to asynchronous parse socket packets,
       * until exit flag was set or some critical error occurred.
       */
      while (1)
	{
	  usleep(1000);

	  ///check exit flag setting by other threads
	  pthread_mutex_lock (&pcbs->lock_exit);
	  tmp_flag_exit = pcbs->flag_exit;
	  pthread_mutex_unlock (&pcbs->lock_exit);
	  if (tmp_flag_exit == Thread_Status_Exit)
	    {
	      printf ("info:detected exit flag,exit!\n");
	      break;  //exit while(1)
	    }
	  /**
	   * check if parent id equals 1,
	   * it means parent process is dead,
	   * exit myself.
	   */
	  if (getppid () == 1)
	    {
	      break;
	    }

	  ///check if FIFO has valid data
	  if (pthread_mutex_trylock (&pcbs->lock_fifo) == 0)
	    {
	      if (zfifo_get_total (pcbs->fifo) > 0)
		{
		  ///FIFO has valid data,signal FIFO_NOT_EMPTY
		  pthread_cond_signal (&pcbs->cond_fifo_notempty);
		}
	      pthread_mutex_unlock (&pcbs->lock_fifo);
	    }

	  /**
	   * async select() to read data from socket.
	   */
	  FD_ZERO(&rd_set);
	  FD_SET(pcbs->fd_socket, &rd_set);
	  tv.tv_sec = 0;	  ///<0s
	  tv.tv_usec = 1000 * 10; //10ms
	  ret = select (pcbs->fd_socket + 1, &rd_set, NULL, NULL, &tv);
	  if (ret < 0)
	    {
	      printf ("select() error:%s!\n", strerror (errno));
	      break; //exit while(1) directly
	    }
	  else if (ret == 0)
	    {
	      /**
	       * select() timeout,continue.
	       */
	      continue;
	    }
	  else
	    {
	      ///select return >0
	      if (FD_ISSET(pcbs->fd_socket, &rd_set))
		{
		  ///read data from socket & write it into FIFO
		  if (read_socket_write_buffer (pcbs, pbuffer) < 0)
		    {
		      break; //exit while(1) directly
		    }
		} //if(FD_ISSET())
	    } //if(rc)
	}	  //while(1)
    }	  //while(0)
  while (0);
  /**
   * thread exit,do some clean below
   */
  /**
   * when error occurs,program will reach here.
   * send signal to process.
   */
  kill (getpid (), SIGTERM);
  /**
   * free pkt->data & pkt memory.
   */
  if (pkt != NULL)
    {
      if (pkt->data != NULL)
	{
	  free (pkt->data);
	  pkt->data = NULL;
	}
      free (pkt);
      pkt = NULL;
    }
  /**
   * free pbuffer->data & pbuffer memory.
   */
  if (pbuffer != NULL)
    {
      if (pbuffer->data != NULL)
	{
	  free (pbuffer->data);
	  pbuffer->data = NULL;
	}
      free (pbuffer);
      pbuffer = NULL;
    }
  printf ("AsyncSocketRecvThread:stop!\n");
  /**
   * exit this pthread.
   */
  pthread_exit (0);
  return 0;
}

/**
 * @brief async receive thread receive data from socket,
 * and write it into temporary buffer.
 * this function runs in block mode
 */
int32_t
read_socket_write_buffer (ZTHREAD_CBS *cbs, ZRECVBUFFER *pbuffer)
{
  zint32_t read_bytes;
  zuint32_t index;
  zuint8_t has_head;

  zuint32_t rest_pos;
  zuint32_t rest_length;
  zuint32_t packet_length;
  zuint32_t complete_length;

  /**
   * check valid of parameter.
   */
  if (cbs == NULL || cbs->fd_socket < 0 || pbuffer == NULL || pbuffer->data == NULL)
    {
      ZPrintError("error:read_socket_write_buffer():invalid parameters!");
      return ZRC_NullPointer;
    }

  /**
   * read maximum data from socket possible.
   */
  read_bytes = read (cbs->fd_socket, &pbuffer->data[pbuffer->total], pbuffer->size - pbuffer->total);

  if (read_bytes < 0) //-1 normal
    {
      printf ("read() error:%s!\n", strerror (errno));
      return ZRC_SocketRecvFailed; ///some serious errors occurs
    }
  else if (read_bytes == 0)
    {
      printf ("warning:socket was closed by client!\n");
      return ZRC_SocketClosed; ///some serious errors occurs
    }
  else if (read_bytes > 0)
    {

      /**
       * remember read bytes number.
       */
      pbuffer->total += read_bytes;
#ifdef ZLogAsyncRecvThread
      printf("<Recv>:read %d,total:%d\n", read_bytes,pbuffer->total);
#endif

      /**
       * loop to handle pbuffer's multiple frames.
       */
      rest_pos = 0; //from [0]
      rest_length = pbuffer->total;

      /**
       * if [0] != ZHEAD1,some errors occurs,reset
       */
      if ((rest_length > 0) && (pbuffer->data[0] != ZHEAD1))
	{
#ifdef ZLogAsyncRecvThread
	  ZPrintError("<Recv>:invalid sync frame head!\n");
	  for(unsigned int kk=0;kk<pbuffer->total;kk++)
	    {
	       printf("0x%02x ",pbuffer->data[kk]);
	    }
	  printf("\n");
	  printf("<Recv>:buffer total:%d\n",pbuffer->total);
#endif
	  return -1; ///error occurs
	}

      while (1)
	{
	  /**
	   * initial flags.
	   */
	  has_head = 0x0;

	  /**
	   *if length is less than 16,do not parse,shift data
	   *head:8 bytes + type:4 bytes + len: 4 bytes=16
	   */
	  if (rest_length < 16)
	    {
	      break; ///<exit while(1)
	    }

	  /**
	   *find header,from start to end
	   *here subtract 7 to avoid index overrun
	   */
	  for (index = 0; index < (rest_length - 8 - 1); index++)
	    {
	      if (pbuffer->data[index + rest_pos + 0] == ZHEAD1 && ///<
		  pbuffer->data[index + rest_pos + 1] == ZHEAD2 && ///<
		  pbuffer->data[index + rest_pos + 2] == ZHEAD3 && ///<
		  pbuffer->data[index + rest_pos + 3] == ZHEAD4 && ///<
		  pbuffer->data[index + rest_pos + 4] == ZHEAD5 && ///<
		  pbuffer->data[index + rest_pos + 5] == ZHEAD6 && ///<
		  pbuffer->data[index + rest_pos + 6] == ZHEAD7 && ///<
		  pbuffer->data[index + rest_pos + 7] == ZHEAD8)
		{
		  has_head = 0x1;
		  break; ///exit for()
		}
	    } ///for()

	  /**
	   * if not find head,abandon this frame data.
	   */
	  if (!has_head)
	    {
#ifdef ZLogAsyncRecvThread
	      ZPrintError("no sync frame header found,abandon this frame\n");
#endif
	      return -1; ///<error occurs
	    }

	  /**
	   *head(8),type(4),length(4)
	   *do not have enough length now,parse next time
	   */
	  if (rest_length < 16)
	    {
	      break;
	    }

	  /**
	   *parse data length field
	   *8 bytes fixed packet header
	   *4 bytes packet type
	   *4 bytes packet length
	   */
	  memcpy (&packet_length, &pbuffer->data[rest_pos + 12], 4);
	  packet_length = ntohl (packet_length);
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
	  printf("info:packet_length=%d\n", packet_length);
#endif
	  if (packet_length <= 0)
	    {
	      ZPrintError("zero packet length,reset!\n");
	      return -1;	  ///<error occurs
	    }

	  /**
	   * data area.
	   * head+type+len+data(len)
	   */
	  complete_length = 8 + 4 + 4 + packet_length;
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
	  printf("info:frame_length:%d,",frame_length);
	  printf("info:rest_length:%d\n",rest_length);
#endif
	  /**
	   * judge length.
	   */
	  if (rest_length < complete_length)
	    {
#ifdef ZLogAsyncRecvThread
	      printf("<Recv>:do not have a complete frame,");
	      printf("<Recv>:need %d bytes\n",complete_length - rest_length);
#endif
	      break;
	    }
	  else if (rest_length == complete_length)
	    {
#ifdef ZLogAsyncRecvThread
	      printf ("<Recv>:only a complete frame\n");
#endif
	      if (read_buffer_write_fifo (cbs, &pbuffer->data[rest_pos], complete_length) < 0)
		{
		  return -1;
		}
	      pbuffer->total = 0;
	      return 0;	  //success
	    }
	  else if (rest_length > complete_length)
	    {
#ifdef ZLogAsyncRecvThread
	      printf("<Recv>:more than 1 frame in buffer\n");
#endif
	      if (read_buffer_write_fifo (cbs, &pbuffer->data[rest_pos], complete_length) < 0)
		{
		  return -1;
		}

	      /**
	       * update rest pos & length for continuing parse.
	       */
#ifdef ZLogAsyncRecvThread
	      printf("<Recv>:update rest_pos %d --> ", rest_pos);
#endif
	      rest_pos = rest_pos + complete_length;
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
	      printf("%d,", rest_pos);
#endif

	      rest_length = rest_length - complete_length;
#ifdef ZLogAsyncRecvThread
	      printf("<Recv>:rest_len:%d,", rest_length);
	      printf("<Recv>:final index:%d\n", rest_pos + rest_length);
#endif
	      continue;
	    }
	}	  ///<while (1)
      /**
       * parse finish,shift rest data to base address
       * for next time parse.
       */
      if (rest_pos != 0 && rest_length > 0)
	{
#ifdef ZLogAsyncRecvThread
	  printf("<Recv>:begin shift rest data...\n");
#endif
	  for (index = 0; index < rest_length; index++)
	    {
	      pbuffer->data[index] = pbuffer->data[index + rest_pos];
	    }
#ifdef ZLogAsyncRecvThread
	  printf("<Recv>:shift rest data finish!\n");
#endif
	  pbuffer->total = rest_length;
#ifdef ZLogAsyncRecvThread
	  printf("update pbuffer->total=%d\n", pbuffer->total);
#endif
	}
    }	      ///<read_bytes > 0
  return 0;
}

/**
 * @brief parse temporary buffer,re-array data to a complete frame,
 * copy frames into FIFO
 * @param cbs
 * @param buffer
 * @param len
 * @param pkt
 */
int32_t
read_buffer_write_fifo (ZTHREAD_CBS *cbs, zuint8_t *buffer, zuint32_t len)
{
  zuint32_t tmp_flag_exit;
  ZPKT *pkt_fifo = NULL;
  zint32_t rc = 0;

  /**
   * check valid of parameters.
   */
  if (cbs == NULL || buffer == NULL || len <= 0)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  /**
   * put data into FIFO.
   */
  pthread_mutex_lock (&cbs->lock_fifo);
  do
    {
      /**
       * wait until FIFO has free space.
       */
      while (zfifo_get_free (cbs->fifo) <= 0)
	{
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
	  printf ("fifo no free space,wait...\n");
#endif
	  pthread_cond_wait (&cbs->cond_fifo_notfull, &cbs->lock_fifo);
	}

      /**
       * check exit flag when waken up after sleep code.
       * maybe need to exit.
       */
      pthread_mutex_lock (&cbs->lock_exit);
      tmp_flag_exit = cbs->flag_exit;
      pthread_mutex_unlock (&cbs->lock_exit);
      if (tmp_flag_exit == Thread_Status_Exit)
	{
	  rc = -1;
	  break;	      ///exit do{}while(0)
	}

      /**
       * get a free position from FIFO.
       */
      pkt_fifo = zfifo_get_free_position (cbs->fifo);
      if (pkt_fifo == NULL)
	{
	  rc = -1;
	  break;  ///error occurs
	}

      /**
       * skip 8 bytes packet head,copy 4 bytes packet type.
       */
      memcpy (&pkt_fifo->type, &buffer[8], 4);
      pkt_fifo->type = ntohl (pkt_fifo->type);
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
      printf("type:0x%x,", pkt_fifo->type);
#endif

      /**
       * copy 4 bytes packet length.
       */
      memcpy (&pkt_fifo->len, &buffer[8 + 4], 4);
      pkt_fifo->len = ntohl (pkt_fifo->len);
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
      printf("len:%d,", pkt_fifo->len);
#endif

      /**
       * copy data area,skip 16 bytes for head & type & len.
       */
      memcpy ((void*) pkt_fifo->data, (void*) &buffer[8 + 4 + 4], pkt_fifo->len);

      /**
       * add a new data info FIFO,
       * so free number is decrease,
       * signal FIFO_NOT_EMPTY.
       */
      zfifo_dec_free_number (cbs->fifo);
      pthread_cond_signal (&cbs->cond_fifo_notempty);

      /**
       * increase receive counter.
       */
#if (ZDBG_LEVEL&ZDBG_THREAD_ASYNC_RECV)
      cbs->counter_rx++;
      printf("\n******** counter_rx=%d\n", cbs->counter_rx);
      printf("fifo has %d pkt\n", zfifo_get_total (cbs->fifo));
#endif
    }
  while (0);
  pthread_mutex_unlock (&cbs->lock_fifo);
  return rc;
}
/**
 * the end of file,tagged by zhangshaoyan.
 * shell.albert@gmail.com
 */
