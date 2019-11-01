/**
 * @file zparse_packet_thread.cpp
 * @brief parse packet from clients
 * @date July 14,2014
 * @author shell.albert@gmail.com
 */
#include <zthread_parse_packet.h>
#include <zerrno.h>
#include <zsm_client.h>
#include <zsubtitle_handler.h>
/**
 * @brief parse packet
 * check if the FIFO has valid data,if has parse it,
 * else block
 */
void*
thread_parse_packet (void* arg)
{
  zint32_t tmp_flag_exit;
  ZPKTNET *pktnet;
  ZTHREAD_CBS *pcbs = (ZTHREAD_CBS*) arg;

  do
    {
      /**
       * check valid of thread structure resource
       */
      if (pcbs == NULL)
	{
	  printf ("error:invalid cbs structure,exit.\n");
	  break; //exit while(0)
	}

      /**
       * allocate packet network for response.
       */
      pktnet = (ZPKTNET*) malloc (sizeof(ZPKTNET));
      if (pktnet == NULL)
	{
	  printf ("error:malloc pktnet failed:%s\n", strerror (errno));
	  break; //exit while(0)
	}

      /**
       * allocate for packet for response.
       */
      pktnet->pkt = (ZPKT*) malloc (sizeof(ZPKT));
      if (pktnet->pkt == NULL)
	{
	  printf ("error:malloc pktnet->pkt failed:%s\n", strerror (errno));
	  break;
	}

      /**
       * allocate for packet data
       */
      pktnet->pkt->data = (zuint8_t*) malloc (ZPKT_BUF_SIZE);
      if (pktnet->pkt->data == NULL)
	{
	  printf ("malloc pktnet->pkt->data failed:%s\n", strerror (errno));
	  break;
	}

      /**
       * initial the counter for count DMA Data packets in fifo.
       * it should be 48 at least before download.
       */
      pcbs->fifoDMADataCounter=0;

      /**
       * detach myself.
       */
//      pthread_detach (pthread_self ());
      printf ("AsyncPacketParseThread:start!\n");
      /**
       * infinite loop to asynchronous socket send work,
       * until exit flag was set or some critical error occurred.
       */
      while (1)
	{
	  usleep(1000);
	  /**
	   * check exit flag
	   * maybe setting by other threads
	   */
	  pthread_mutex_lock (&pcbs->lock_exit);
	  tmp_flag_exit = pcbs->flag_exit;
	  pthread_mutex_unlock (&pcbs->lock_exit);
	  if (tmp_flag_exit == Thread_Status_Exit)
	    {
#if (ZDBG_LEVEL&ZDBG_PACKET_PARSE)
	      printf ("info:detected exit flag,exit.\n");
#endif
	      break;  ///<exit while(1)
	    }

	  /**
	   * check if parent id equals 1,
	   * it means parent process is dead,
	   * then exit myself
	   */
	  if (getppid () == 1)
	    {
	      break;
	    }

	  /**
	   * check if FIFO has free space
	   */
	  if (pthread_mutex_trylock (&pcbs->lock_fifo) == 0)
	    {
	      if (zfifo_get_free (pcbs->fifo) > 0)
		{
		  /**
		   * if FIFO has free space,signal FIFO_NOT_FULL,
		   * to wake up receive thread.
		   */
		  pthread_cond_signal (&pcbs->cond_fifo_notfull);
		}
	      pthread_mutex_unlock (&pcbs->lock_fifo);
	    }

	  /**
	   * read one frame from FIFO,
	   * parse it and write to device.
	   */
	  if (read_fifo_write_device (pcbs, pktnet) < 0)
	    {
	      break;	  ///exit while(1)
	    }
	  else
	    {
	      continue;
	    }
	}      ///<while(1)
    }
  while (0);
  /**
   * when error occurs,program will reach here.
   * send signal to process.
   */
  kill (getpid (), SIGTERM);
  /**
   * free resource & memory before exit.
   */
  if (pktnet != NULL)
    {
      if (pktnet->pkt != NULL)
	{
	  if (pktnet->pkt->data != NULL)
	    {
	      free (pktnet->pkt->data);
	      pktnet->pkt->data = NULL;
	    }
	  free (pktnet->pkt);
	  pktnet->pkt = NULL;
	}
      free (pktnet);
      pktnet = NULL;
    }

  printf ("AsyncPacketParseThread:stop!\n");
  /**
   * exit this thread.
   */
  pthread_exit (NULL);
  return 0;
}

/**
 * @brief asynchronous write data to driver.
 * read data from FIFO & write to driver
 */
int32_t
read_fifo_write_device (ZTHREAD_CBS *cbs, ZPKTNET *pktnet)
{
  ZPKT *pkt_fifo;
  zint32_t tmp_flag_exit = Thread_Status_Running;
  zint32_t index;
  zint32_t ret;

  /**
   * check valid of necessary parameters
   */
  if (cbs == NULL || pktnet == NULL || pktnet->pkt == NULL || pktnet->pkt->data == NULL)
    {
      printf ("error:invalid parameters,quit!\n");
      return ZRC_NullPointer;
    }

  /**
   * get data from FIFO
   */
  pthread_mutex_lock (&cbs->lock_fifo);
  do
    {
      /**
       * wait until FIFO has valid data
       */
      while (!zfifo_get_total (cbs->fifo))
	{

#if (ZDBG_LEVEL&ZDBG_PACKET_PARSE)
	  printf("info:wait FIFO to have data...\n");
#endif
	  pthread_cond_wait (&cbs->cond_fifo_notempty, &cbs->lock_fifo);
	  /**
	   * check exit flag when waken up after sleep code.
	   * maybe other threads request to exit.
	   * when detect exit flag has been set,
	   * exit automatically.
	   */
	  pthread_mutex_lock (&cbs->lock_exit);
	  tmp_flag_exit = cbs->flag_exit;
	  pthread_mutex_unlock (&cbs->lock_exit);
	  if (tmp_flag_exit == Thread_Status_Exit)
	    {
	      ret = ZRC_Success;
	      break;	      ///<exit while()
	    }
	}
      if (tmp_flag_exit == Thread_Status_Exit)
	{
	  ret = ZRC_Success;
	  break;	      ///<exit do{}while(0)
	}

      /**
       * get a resource pointer point to frame stored in FIFO.
       * this will reduce data copy operation.
       */
      pkt_fifo = zfifo_get_busy_position (cbs->fifo);
      if (pkt_fifo == NULL)
	{
	  ret = ZRC_NullPointer;
	  break;	      ///<error occurs
	}

      printf ("Fetch a packet from FIFO:type=0x%02x,len=%d\n", pkt_fifo->type, pkt_fifo->len);

#if 0
      for (index = 0; index < pkt_fifo->len; index++)
	{
	  printf("0x%02x ", pkt_fifo->data[index]);
	}
      printf("\n");
#endif

      /**
       * parse packet according to different types.
       *
       */
      switch (pkt_fifo->type)
	{
	case PKT_OPEN_DEVICE_FILE:
	  /**
	   * open device file operation.
	   * before read/write register or execute DMA data transfer,
	   * device file must be opened.
	   * pkt_fifo contains the frame data.
	   * pktnet is a global buffer for command response.
	   */
	  ret = cmd_open_device_file (cbs, pkt_fifo, pktnet);
	  break;	      ///<exit switch()

	case PKT_QUERY_CARD_INFO:
	  /**
	   * client requests IMB card info.
	   * do not need device file opened.
	   * do not use FIFO.
	   */
	  ret = cmd_query_card_info (cbs, pkt_fifo, pktnet);
	  break;	      ///exit switch()

	case PKT_QUERY_CPU_INFO:
	  /**
	   * client requests CPU information.
	   * do not need device file opened.
	   * do not use FIFO.
	   */
	  ret = cmd_query_cpu_info (cbs, pkt_fifo, pktnet);
	  break;	      ///exit switch()

	case PKT_QUERY_MEM_INFO:
	  /**
	   * client request memory information.
	   * do not need device file opened.
	   * do not use FIFO.
	   */
	  ret = cmd_query_mem_info (cbs, pkt_fifo, pktnet);
	  break;	      ///<exit switch()

	case PKT_RW_FPGA_REGISTER:
	  /**
	   * client request to read & write FPGA registers.
	   * device file must be opened before operating.
	   *
	   * need device file opened.
	   * do not use FIFO.
	   */
	  ret = cmd_read_write_fpga_register (cbs, pkt_fifo, pktnet);
	  break;	      ///<exit switch()

	case PKT_TRANSFER_DMA_DATA:

	  /**
	   * if we have enough data, then start normal flow.
	   * otherwise wait.
	   */
	  if(cbs->fifoDMADataCounter<48)
	    {
	      printf("buffer less than 48,waiting!\n");
		  cbs->fifoDMADataCounter++;
		  pthread_mutex_unlock (&cbs->lock_fifo);
		  return 0;
	    }

	  /**
	   * client request to transfer DMA data.
	   * device file must be opened before operating.
	   *
	   * need device file opened.
	   */
#if 0
	  ret = cmd_transfer_dma_data (cbs, pkt_fifo, pktnet);
#else
	  ret=0;
	  printf("bypass DMA AV Transfer!\n");
	  usleep(1000*20);
#endif

//	  cbs->rx_cnt_dma++;
//	  printf ("**handle pkt:PKT_TRANSFER_DMA_DATA=%d\n", cbs->rx_cnt_dma);
	  break;	      ///exit switch()

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
	  /**
	   * packet types for SM client & SM server.
	   * added by zhangshaoyan at October 27,2014.
	   */
	  /**
	   * step2.
	   * ret=sm->loadCertificateChainFile("certchain.data");
	   */
	case PKT_SM_LOAD_CERTCHAIN_FILE:
	  ret = cmd_sm_load_certificate_file (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step3.
	   * ret=sm->loadPrivateKeyFile("SMStheLeafprikey.pem");
	   */
	case PKT_SM_LOAD_PRIVATEKEY_FILE:
	  ret = cmd_sm_load_privatekey_file (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step4.
	   * ret=sm->connect();
	   */
	case PKT_SM_CONNECT:
	  ret = cmd_sm_connect (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step5.
	   * ret=sm->startSuite();
	   */
	case PKT_SM_STARTSUITE:
	  ret = cmd_sm_start_suite (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step6.
	   * ret=sm->uploadCplFile();
	   */
	case PKT_SM_UPLOAD_CPL_FILE:
	  ret = cmd_sm_upload_cpl_file (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step7.
	   * ret=sm->uploadKdmFile();
	   */
	case PKT_SM_UPLOAD_KDM_FILE:
	  ret = cmd_sm_upload_kdm_file (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step8.
	   * ret=sm->playShow();
	   */
	case PKT_SM_PLAYSHOW:
	  ret = cmd_sm_play_show (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step9.
	   * ret=sm->stopShow();
	   */
	case PKT_SM_STOPSHOW:
	  ret = cmd_sm_stop_show (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step10.
	   * ret=sm->purgeCpl();
	   */
	case PKT_SM_PURGECPL:
	  ret = cmd_sm_purge_cpl (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * step11.
	   * ret=sm->stopSuite();
	   */
	case PKT_SM_STOPSUITE:
	  ret = cmd_sm_stop_suite (cbs, pkt_fifo, pktnet);
	  break;

	  /**
	   * added by zhangshaoyan at November 3,2014.
	   * for support SM.
	   */
	case PKT_SM_GETCPLLIST:
	  ret = cmd_sm_getcpllist (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_GETKDMLIST:
	  ret = cmd_sm_getkdmlist (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_CHECKSHOW:
	  ret = cmd_sm_checkshow (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_ADJUSTTIME:
	  ret = cmd_sm_adjusttime (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_GETCERTIFICATE:
	  ret = cmd_sm_getcertificate (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_QUERYSTATUS:
	  ret = cmd_sm_querystatus (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_GETLOGREPORT:
	  ret = cmd_sm_getlogreport (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_INITIATEMARRIAGE:
	  ret = cmd_sm_initiatemarriage (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_SERVICEDOORTAMPERTERMINATION:
	  ret = cmd_sm_servicedoortampertermination (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_GETKEYMAP:
	  ret = cmd_sm_getkeymap (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_ADDCERTIFICATE:
	  ret = cmd_sm_addcertificate (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_USEPRIVATEKEY:
	  ret = cmd_sm_useprivatekey (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_ZEROIZE:
	  ret = cmd_sm_zeroize (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_UPLOADCPLBUFFER:
	  ret = cmd_sm_uploadcplbuffer (cbs, pkt_fifo, pktnet);
	  break;

	case PKT_SM_UPLOADKDMBUFFER:
	  ret = cmd_sm_uploadkdmbuffer (cbs, pkt_fifo, pktnet);
	  break;

	  /**
	   * Play mode control.
	   * Modified by zhangshaoyan at November 21,2014.
	   * Note:
	   * Move Play mode control from SDK to IMB server.
	   */
	case PKT_PLAY_MODE_START:
	  ret = cmd_play_mode_start (cbs, pkt_fifo, pktnet);
	  break;
	case PKT_PLAY_MODE_PAUSE:
	  ret = cmd_play_mode_pause (cbs, pkt_fifo, pktnet);
	  break;
	case PKT_PLAY_MODE_FORWARD:
	  ret = cmd_play_mode_forward (cbs, pkt_fifo, pktnet);
	  break;
	case PKT_PLAY_MODE_BACKWARD:
	  ret = cmd_play_mode_backward (cbs, pkt_fifo, pktnet);
	  break;
	case PKT_PLAY_MODE_STOP:
	  ret = cmd_play_mode_stop (cbs, pkt_fifo, pktnet);
	  break;

	  /**
	   * subtitle file transfer packets support.
	   * added by zhangshaoyan at December 2,2014.
	   */
	case PKT_SUBTITLE_FILE:
	  ret = cmd_subtitle_file (cbs, pkt_fifo, pktnet);
	  break;
	case PKT_SUBTITLE_OVERLAY_ELEMENT:
	  ret = cmd_subtitle_overlay_element (cbs, pkt_fifo, pktnet);
	  break;
	  /**
	   * do not supported packets.
	   */
	default:
	  ret = RC_UNKNOWN_ERR;
	  break;	      ///exit switch()
	}	  ///<switch()
      /**
       * already fetch a frame from FIFO.
       * so here should increase free numbers.
       */
      zfifo_inc_free_number (cbs->fifo);
    }
  while (0);
  pthread_mutex_unlock (&cbs->lock_fifo);
  return ret;
}

/**
 * the end of file,tagged by zsy
 */
