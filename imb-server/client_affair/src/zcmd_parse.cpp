/**
 * @file zcmd_parse.c
 * @date July 3,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief define network protocol parse module
 */
#include <zcmd_parse.h>
#include <zprotocol.h>
#include <zdevice_interface.h>
/**
 * added 8 bytes fixed frame head data.
 */
zint32_t
add_zpktnet_fixed_head (ZPKTNET *pktnet)
{
  if (pktnet == NULL)
    {
      return ZRC_InvalidParameters;;
    }
  pktnet->head[0] = ZHEAD1;
  pktnet->head[1] = ZHEAD2;
  pktnet->head[2] = ZHEAD3;
  pktnet->head[3] = ZHEAD4;
  pktnet->head[4] = ZHEAD5;
  pktnet->head[5] = ZHEAD6;
  pktnet->head[6] = ZHEAD7;
  pktnet->head[7] = ZHEAD8;
  return ZRC_Success;
}

zint32_t
send_lower_layer (zint32_t sockfd, zuint8_t *buffer, zuint32_t buflen)
{
  zint32_t total_bytes;
  zint32_t send_bytes;

  /**
   * check parameter valid
   */
  if (sockfd <= 0 || buffer == NULL || buflen <= 0)
    {
      return ZRC_InvalidParameters;
    }
//  printf ("sending:\n");
//  for (unsigned int i = 0; i < buflen; i++)
//    {
//      printf ("0x%x,", buffer[i]);
//    }
//  printf ("\n");
  total_bytes = buflen;
  send_bytes = 0;
  /**
   * loop to send data out.
   */
  while (total_bytes > 0)
    {
      send_bytes = send (sockfd, &buffer[send_bytes], total_bytes, 0);
      if (send_bytes > 0)
	{
	  total_bytes -= send_bytes;
	}
      else if (send_bytes < 0)
	{
	  printf ("send() error:%s\n", strerror (errno));
	  return ZRC_SocketSendFailed;
	}
    }

  /**
   * success here.
   */
  return ZRC_Success;
}

zint32_t
send_zpknet (ZPKTNET *pktnet)
{
  if (pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, ntohl (pktnet->pkt->len));
  return ZRC_Success;
}

/**
 * @brief query IMB Card information
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
zint32_t
cmd_query_card_info (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_QUERY_CARD_INFO pktRecv;
  MMAP_QUERY_CARD_INFO pktSend;
  zint32_t ret;
  ///check valid of parameters
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  if ((ret = mmap_query_card_info (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_query_card_info (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  //////////generate ACK packet////////////////
  ///add 8 bytes fixed header
  add_zpktnet_fixed_head (pktnet);

  ///add 4 bytes type & 4 bytes len
  pktnet->pkt->type = htonl (PKT_QUERY_CARD_INFO_ACK);

  /**
   * data field.
   */
  *pktSend.ptotal = 1;
  *pktSend.pcard = 0;  ///< /dev/imb.0
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + ///<
      sizeof(*pktSend.ptotal) + sizeof(*pktSend.pcard) + (*pktSend.pcard);

  /**
   * set packet length.
   */
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.ptotal = htonl (*pktSend.ptotal);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  ///step4:send data out
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  return ZRC_Success;
}

/**
 * @brief query CPU information
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
#include <assert.h>
zint32_t
zfunc_get_cpu_info (int *cores, int *frequency)
{
  char *cmd_get_freq_MHz = "dmesg | grep -e 'Detected' | grep -e 'processor' | sed -e 's/.*\\s\\+\\([.0-9]\\+\\)\\s\\+MHz.*/\\1/'";
  char *cmd_get_num_cores = "cat /proc/cpuinfo | grep 'core id' | uniq |wc -l";
  FILE *pd = NULL;
  int num_cores;
  float cpu_frequency;
  int cpu_frequency_khz;

  //get num cores.
  assert((pd = popen( cmd_get_num_cores, "r")) != NULL);
  int nc = fscanf (pd, "%d", &num_cores);
  assert(nc == 1 && num_cores > 0);
  pclose (pd);
  printf ("num_cores=%d\n", num_cores);

  //get cpu frequency.
  assert((pd = popen( cmd_get_freq_MHz, "r")) != NULL);
  nc = fscanf (pd, "%f", &cpu_frequency);
  assert(nc == 1 && cpu_frequency > 0);
  pclose (pd);
  //convert MHz to kHz.
  cpu_frequency_khz = cpu_frequency * 1024;
  printf ("cpu_frequency=%f MHz,%d kHz\n", cpu_frequency, cpu_frequency_khz);

  //update.
  *cores = num_cores;
  *frequency = cpu_frequency_khz;
  return 0;
}
zint32_t
cmd_query_cpu_info (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_QUERY_CPU_INFO pktRecv;
  MMAP_QUERY_CPU_INFO pktSend;
  zint32_t ret;
  ///check valid of parameters
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_query_cpu_info (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_query_cpu_info (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  //get cpu information.
  if (zfunc_get_cpu_info ((zint32_t*) (pktSend.ptotal_cores), (zint32_t*) pktSend.pcores_freq) < 0)
    {
      //error.
      *pktSend.pret_code = -1;
    }
  else
    {
      //success.
      *pktSend.pret_code = 0;
    }

  /**
   * generate response ACK packet to client.
   */
  /**
   * add 8 bytes fixed packet header
   */
  add_zpktnet_fixed_head (pktnet);
  /**
   * add 4 bytes type & 4 bytes len
   */
  pktnet->pkt->type = htonl (PKT_QUERY_CPU_INFO_ACK);
  /**
   * add data field.
   */

  /**
   * set packet length.
   */
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + sizeof(*pktSend.pret_code) + //
      sizeof(*pktSend.ptotal_cores) + sizeof(*pktSend.pcores_freq);
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.pret_code = htonl (*pktSend.pret_code);
  *pktSend.ptotal_cores = htonl (*pktSend.ptotal_cores);
  *pktSend.pcores_freq = htonl (*pktSend.pcores_freq);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send response packet out.
   */
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  return ZRC_Success;
}

/**
 * @brief query memory information
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
zint32_t
zfunc_get_mem_info (int *memTotal, int *memFree)
{
  char *shell_get_memTotal = "cat /proc/meminfo | grep 'MemTotal' | awk '{print $2}'";
  char *shell_get_memFree = "cat /proc/meminfo | grep 'MemFree' | awk '{print $2}'";
  FILE *fp = NULL;
  int tmemTotal;
  int tmemFree;
  int nc;

  //get memory total.
  assert((fp = popen( shell_get_memTotal, "r")) != NULL);
  nc = fscanf (fp, "%d", &tmemTotal);
  assert(nc == 1 && tmemTotal > 0);
  pclose (fp);
  printf ("tmemTotal=%d\n", tmemTotal);

  //get memory free.
  assert((fp = popen( shell_get_memFree, "r")) != NULL);
  nc = fscanf (fp, "%d", &tmemFree);
  assert(nc == 1 && tmemFree > 0);
  pclose (fp);
  printf ("tmemFree=%d\n", tmemFree);

  //update.
  *memTotal = tmemTotal;
  *memFree = tmemFree;
  return 0;
}
zint32_t
cmd_query_mem_info (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_MEM_INFO pktRecv;
  MMAP_MEM_INFO pktSend;
  zint32_t ret;
  /**
   * check valid of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  if ((ret = mmap_mem_info (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_mem_info (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  //get memory information.
  if (zfunc_get_mem_info ((zint32_t*) (pktSend.pmem_total), (zint32_t*) pktSend.pmem_free) < 0)
    {
      //error.
      *pktSend.pret_code = -1;
    }
  else
    {
      //success.
      *pktSend.pret_code = 0;
    }

  /**
   * generate response ACK packet to client.
   */
  /**
   * add 8 bytes fixed packet header
   */
  add_zpktnet_fixed_head (pktnet);
  /**
   * add 4 bytes type & 4 bytes len
   */
  pktnet->pkt->type = htonl (PKT_QUERY_MEM_INFO_ACK);
  /**
   * add data field.
   */

  /**
   * set packet length.
   */
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + sizeof(*pktSend.pret_code) + //
      sizeof(*pktSend.pmem_total) + sizeof(*pktSend.pmem_free);
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.pret_code = htonl (*pktSend.pret_code);
  *pktSend.pmem_total = htonl (*pktSend.pmem_total);
  *pktSend.pmem_free = htonl (*pktSend.pmem_free);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send response packet out.
   */
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  return ZRC_Success;
}

/**
 * @brief command parse for read/write fpga register
 * @param cbs
 * @param pkt:received from socket
 * @param pktnet:a buffer for store data & send out use
 * @param buffer:a global buffer for use
 * @param buflen:the global buffer length
 */
zint32_t
cmd_read_write_fpga_register (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_FPGA_RW_REGISTER pktRecv;
  MMAP_FPGA_RW_REGISTER pktSend;
  zint32_t ret;
  fd_set wr_set;
  struct timeval tv;
  zuint32_t address;
  zuint32_t value;

  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_fpga_rw_register (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_fpga_rw_register (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  /**
   * check device file current status.
   */
  if (device_is_opened (&cbs->m_dev) < 0)
    {

      printf ("warning:device is not opened!\n");
      return ZRC_DeviceFileNotOpened;
    }

  /**
   * asynchronous select() to write data to driver.
   */
  while (1)
    {
      FD_ZERO(&wr_set);
      FD_SET(cbs->m_dev.fd, &wr_set);
      tv.tv_sec = 0;
      tv.tv_usec = 1000 * 1; //1000us=1ms
      ret = select (cbs->m_dev.fd + 1, NULL, &wr_set, NULL, &tv);
      if (ret < 0)
	{
	  printf ("select() error:%s\n", strerror (errno));
	  ret = ZRC_SystemCallFailed;
	  break; ///<exit while(1)
	}
      else if (ret == 0)
	{
	  /**
	   * select() timeout.
	   */
	  continue;
	}
      else
	{
	  ////select return >0
	  if (FD_ISSET(cbs->m_dev.fd, &wr_set))
	    {
	      /**
	       * network byte order to host byte order.
	       */
	      *pktRecv.prd_wr = ntohl (*pktRecv.prd_wr);
	      *pktRecv.pregs_address = ntohl (*pktRecv.pregs_address);
	      *pktRecv.pregs_value = ntohl (*pktRecv.pregs_value);
	      //printf ("RWRegister:%d,0x%x,0x%x\n", *pktRecv.prd_wr, *pktRecv.pregs_address, *pktRecv.pregs_value);
	      /**
	       * read or write.
	       */
	      switch (*pktRecv.prd_wr)
		{
		case REGISTER_READ:
		  address = *pktRecv.pregs_address;
		  ret = device_read_reg (&cbs->m_dev, address, &value);
		  if (ret < 0)
		    {
		      ret = ZRC_ReadFPGARegisterFailed;
		    }
		  else
		    {
		      ret = ZRC_Success;
		    }
		  break;
		case REGISTER_WRITE:
		  address = *pktRecv.pregs_address;
		  value = *pktRecv.pregs_value;
		  ret = device_write_reg (&cbs->m_dev, address, value);
		  if (ret < 0)
		    {
		      ret = ZRC_WriteFPGARegisterFailed;
		    }
		  else
		    {
		      ret = ZRC_Success;
		    }
		  break;
		default:
		  /**
		   * do not supported command.
		   */
		  printf ("warning:not read or write FPGA register request!\n");
		  ret = ZRC_SocketPacketDataError;
		  break;
		}

	      /////generate ACK packet///////////
	      ///add 8 bytes fixed header
	      add_zpktnet_fixed_head (pktnet);

	      ///add 4 bytes type & 4 bytes len
	      pktnet->pkt->type = htonl (PKT_RW_FPGA_REGISTER_ACK);

	      ///add data field
	      *pktSend.prd_wr = *pktRecv.prd_wr;
	      *pktSend.pregs_address = address;
	      *pktSend.pregs_value = value;
	      *pktSend.pret_code = ret;

	      /**
	       * set packet length.
	       */
	      *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + ///<
		  sizeof(*pktSend.prd_wr) + sizeof(*pktSend.pregs_address) + ///<
		  sizeof(*pktSend.pregs_value) + sizeof(*pktSend.pret_code);
	      pktnet->pkt->len = *pktSend.pvalid_len;

	      //printf ("send:0x%x,0x%x,0x%x,ret=%d\n", *pktSend.prd_wr, *pktSend.pregs_address, *pktSend.pregs_value, *pktSend.pret_code);
	      /**
	       * host byte order to network byte order.
	       */
	      *pktSend.prd_wr = htonl (*pktSend.prd_wr);
	      *pktSend.pregs_address = htonl (*pktSend.pregs_address);
	      *pktSend.pregs_value = htonl (*pktSend.pregs_value);
	      *pktSend.pret_code = htonl (*pktSend.pret_code);
	      //printf ("retcode:0x%x\n", *pktSend.pret_code);
	      pktnet->pkt->len = htonl (pktnet->pkt->len);

	      /**
	       * send data out.
	       */
	      send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
	      send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
	      send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
	      send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
	      ///finish one frame
	      ret = ZRC_Success;
	      break;		  //exit while(1)
	    }
	}		  //rc=select()
    }	  //while(1)
  return ret;
}

/**
 * @brief transfer DMA data
 * @param cbs
 * @param pkt
 * @param pktnet
 * @param buffer
 * @param buflen
 */
zint32_t
cmd_transfer_dma_data (ZTHREAD_CBS * cbs, ZPKT * pkt_fifo, ZPKTNET * pktnet)
{
  fd_set wr_set;
  struct timeval tv;
  zint32_t ret;
  zint32_t tmp_flag_exit;

  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_InvalidParameters;
    }

  if ((ret = device_is_opened (&cbs->m_dev)) < 0)
    {
      printf ("dma:device is not opened!\n");
      return ret;
    }

  /**
   * asynchronous select() to write data to driver.
   */
  while (1)
    {
      ///check exit flag in infinite loop
      pthread_mutex_lock (&cbs->lock_exit);
      tmp_flag_exit = cbs->flag_exit;
      pthread_mutex_unlock (&cbs->lock_exit);
      if (tmp_flag_exit == Thread_Status_Exit)
	{
	  ret = Thread_Status_Exit;
	  break;	      //exit while(1)
	}

      FD_ZERO(&wr_set);
      FD_SET(cbs->m_dev.fd, &wr_set);
      tv.tv_sec = 0;
      tv.tv_usec = 1000 * 10; //10ms
      ret = select (cbs->m_dev.fd + 1, NULL, &wr_set, NULL, &tv);
      if (ret < 0)
	{
	  ZPrintError("select() error:%s\n", strerror (errno));
	  ret = ZRC_SystemCallFailed;
	  break;      //exit while(1)
	}
      else if (ret == 0)
	{
	  /**
	   * select() timeout.
	   */
	  continue;
	}
      else
	{
	  if (FD_ISSET(cbs->m_dev.fd, &wr_set))
	    {

//////////////////////////////////////////////
//here export received data into local file system,
//to check if the data is same as the client send out.
//#if 0
//		  FILE *fp;
//		  fp = fopen ("server_recv.data", "wb");
//		  if (fp != NULL)
//		    {
//		      fwrite (pkt_fifo->data, pkt_fifo->len, 1, fp);
//		      printf ("save data finish!\n");
//		      fclose (fp);
//		      getchar ();
//		    }
//#endif

	      //printf ("write DMA %d bytes\n", pkt_fifo->len);
	      ret = device_write_dma (&cbs->m_dev, pkt_fifo->data, pkt_fifo->len);
	      //finish one frame
	      break;//exit while(1)
	    }
	}      //if()
    }      //while(1)
  return ret;
}

zint32_t
cmd_open_device_file (ZTHREAD_CBS * cbs, ZPKT * pkt_fifo, ZPKTNET * pktnet)
{
  MMAP_OPEN_DEVICE_FILE pktRecv;
  MMAP_OPEN_DEVICE_FILE pktSend;
  zint8_t file_name[128];
  zint32_t ret = ZRC_Success;

  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_open_device_file (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_open_device_file (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  /**
   * network byte order to host byte order.
   */
  *pktRecv.pfile_num = ntohl (*pktRecv.pfile_num);

  /**
   * if device file is not open then open it.
   * update status flag.
   */
  memset (file_name, 0, sizeof(file_name));
  sprintf (file_name, "/dev/imb.%d", *pktRecv.pfile_num);
  ret = device_open (file_name, &cbs->m_dev);

  /**
   * generate response ACK packet to client.
   */
  /**
   * add 8 bytes fixed packet header
   */
  add_zpktnet_fixed_head (pktnet);
  /**
   * add 4 bytes type & 4 bytes len
   */
  pktnet->pkt->type = htonl (PKT_OPEN_DEVICE_FILE_ACK);
  /**
   * add data field.
   */
  *pktSend.pret_code = ret;
  printf ("device=/dev/imb.%d,return code=%d\n", *pktRecv.pfile_num, ret);

  /**
   * set packet length.
   */
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + sizeof(*pktSend.pret_code);
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.pret_code = htonl (*pktSend.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send response packet out.
   */
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  return ret;
}

/**
 * Play mode control.
 * Modified by zhangshaoyan at November 21,2014.
 * Note:
 * Move Play mode control from SDK to IMB server.
 */
zint32_t
cmd_play_mode_start (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_PLAY_MODE_START pktRecv;
  MMAP_PLAY_MODE_START pktSend;
  zint32_t ret = ZRC_Success;
  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_play_mode_start (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_play_mode_start (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  /**
   * generate response ACK packet to client.
   */
  /**
   * add 8 bytes fixed packet header
   */
  add_zpktnet_fixed_head (pktnet);
  /**
   * add 4 bytes type & 4 bytes len
   */
  pktnet->pkt->type = htonl (PKT_PLAY_MODE_START_ACK);
  /**
   * add data field.
   */
  *pktSend.pret_code = ret;

  /**
   * set packet length.
   */
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + sizeof(*pktSend.pret_code);
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.pret_code = htonl (*pktSend.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send response packet out.
   */
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  printf ("received start play\n");
  return ret;
}
zint32_t
cmd_play_mode_pause (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_PLAY_MODE_PAUSE pktRecv;
  MMAP_PLAY_MODE_PAUSE pktSend;
  zint32_t ret = ZRC_Success;
  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_play_mode_pause (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_play_mode_pause (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  /**
   * generate response ACK packet to client.
   */
  /**
   * add 8 bytes fixed packet header
   */
  add_zpktnet_fixed_head (pktnet);
  /**
   * add 4 bytes type & 4 bytes len
   */
  pktnet->pkt->type = htonl (PKT_PLAY_MODE_PAUSE_ACK);
  /**
   * add data field.
   */
  *pktSend.pret_code = ret;

  /**
   * set packet length.
   */
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + sizeof(*pktSend.pret_code);
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.pret_code = htonl (*pktSend.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send response packet out.
   */
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  return ret;
}
zint32_t
cmd_play_mode_forward (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  return 0;
}
zint32_t
cmd_play_mode_backward (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  return 0;
}
zint32_t
cmd_play_mode_stop (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_PLAY_MODE_STOP pktRecv;
  MMAP_PLAY_MODE_STOP pktSend;
  zint32_t ret = ZRC_Success;
  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_play_mode_stop (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  if ((ret = mmap_play_mode_stop (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  /**
   * generate response ACK packet to client.
   */
  /**
   * add 8 bytes fixed packet header
   */
  add_zpktnet_fixed_head (pktnet);
  /**
   * add 4 bytes type & 4 bytes len
   */
  pktnet->pkt->type = htonl (PKT_PLAY_MODE_STOP_ACK);
  /**
   * add data field.
   */
  *pktSend.pret_code = ret;

  /**
   * set packet length.
   */
  *pktSend.pvalid_len = sizeof(*pktSend.pvalid_len) + sizeof(*pktSend.pret_code);
  pktnet->pkt->len = *pktSend.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *pktSend.pret_code = htonl (*pktSend.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send response packet out.
   */
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->head, 8);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->type, 4);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) &pktnet->pkt->len, 4);
  ret = send_lower_layer (cbs->fd_socket, (zuint8_t*) pktnet->pkt->data, *pktSend.pvalid_len);
  return ret;
}
////////////////////////////////////////////////
/**
 * the end of file,tagged by zsy
 */
