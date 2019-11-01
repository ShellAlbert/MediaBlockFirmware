/*
 * zsubtitle_handler.cpp
 *
 *  Created on: 2014年12月2日
 *      Author: shell.albert
 */
#include <zsubtitle_handler.h>
#include <zcmd_parse.h>
#include <zdevice_interface.h>
void
reverse_int32 (zuint32_t *pData)
{
  zuint32_t tmpData = *pData;
  zuint8_t *pChar8_1 = (zuint8_t*) pData;
  zuint8_t *pChar8_2 = (zuint8_t*) &tmpData;
  pChar8_1[0] = pChar8_2[3];
  pChar8_1[1] = pChar8_2[2];
  pChar8_1[2] = pChar8_2[1];
  pChar8_1[3] = pChar8_2[0];
  return;
}
zint32_t cmd_subtitle_file(ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
  {
    MMAP_SUBTITLE_FILE pktRecv;
    MMAP_SUBTITLE_FILE pktSend;
    zint32_t ret = ZRC_Success;
    zuint8_t *pData;
    zuint32_t dataSize;
    /**
     * check valid of necessary parameters.
     */
    if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
      {
	return ZRC_NullPointer;
      }

    if ((ret = mmap_subtitle_file (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
      {
	return ZRC_MmapStructureFailed;
      }
    /**
     * network byte order to host byte order.
     */
    *pktRecv.pFrameType = ntohl (*pktRecv.pFrameType);
    *pktRecv.pFrameLength = ntohl (*pktRecv.pFrameLength);

    if ((ret = mmap_subtitle_file (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
      {
	return ZRC_MmapStructureFailed;
      }

    /**
     * transfer subtitle xml file to FPGA through DMA.
     */
//  printf ("FrameType:0x%x,FrameLength:0x%x(%d)\n", *pktRecv.pFrameType, *pktRecv.pFrameLength, *pktRecv.pFrameLength);
//  printf ("Encrypt flag:0x%x,KeyId:", *pktRecv.pEncryFlag);
//  for (int i = 0; i < 16; i++)
//    {
//      printf ("%02x ", pktRecv.pKeyId[i]);
//    }
//  printf ("\n");
    /**
     * check device file current status.
     */
    if (device_is_opened (&cbs->m_dev) < 0)
      {
	ret = ZRC_DeviceFileNotOpened;
      }
    else
      {
	pData = (zuint8_t*) pktRecv.pFrameType;
	dataSize = sizeof(*pktRecv.pFrameType) + ///<
	sizeof(*pktRecv.pFrameLength) + (*pktRecv.pFrameLength);
	/**
	 * aligned by 8 bytes for FPGA.
	 */
	if (dataSize % 8 != 0)
	  {
	    dataSize += 8 - dataSize % 8;
	  }
	/**
	 * FPGA only knows the Big Endian byte order.
	 * so here do convert.
	 */
	reverse_int32 (pktRecv.pFrameType);
	reverse_int32 (pktRecv.pFrameLength);
	ret = device_write_dma (&cbs->m_dev, pData, dataSize);
//      printf ("write to DMA:%d bytes\n", dataSize);
//      for (unsigned int j = 0; j < dataSize; j++)
//	{
//	  printf ("%02x,", pData[j]);
//	  if ((j + 1) % 16 == 0)
//	    {
//	      printf ("\n");
//	    }
//	}
//      printf ("\n");
      }
    /**
     * build an ACK packet.
     */
    /**
     * step1.
     * add 8 bytes fixed header
     */
    add_zpktnet_fixed_head (pktnet);

    /**
     * step2.
     * add 4 bytes frame type & 4 bytes frame length.
     */
    pktnet->pkt->type = htonl (PKT_SUBTITLE_FILE_ACK);
    /**
     * the real data we want to send out.
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
     * send out.
     */
    ret = send_zpknet (pktnet);
    return ret;
  }

zint32_t
cmd_subtitle_overlay_element (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SUBTITLE_FILE pktRecv;
  MMAP_SUBTITLE_FILE pktSend;
  zint32_t ret = ZRC_Success;
  zuint8_t *pData;
  zuint32_t dataSize;
  /**
   * check valid of necessary parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  if ((ret = mmap_subtitle_file (&pktRecv, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }
  /**
   * network byte order to host byte order.
   */
  *pktRecv.pFrameType = ntohl (*pktRecv.pFrameType);
  *pktRecv.pFrameLength = ntohl (*pktRecv.pFrameLength);

  if ((ret = mmap_subtitle_file (&pktSend, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK)) < 0)
    {
      return ZRC_MmapStructureFailed;
    }

  /**
   * transfer subtitle xml file to FPGA through DMA.
   */
//  printf ("FrameType:0x%x,FrameLength:0x%x(%d)\n", *pktRecv.pFrameType, *pktRecv.pFrameLength, *pktRecv.pFrameLength);
//  printf ("Encrypt flag:0x%x,KeyId:", *pktRecv.pEncryFlag);
//  for (int i = 0; i < 16; i++)
//    {
//      printf ("%02x ", pktRecv.pKeyId[i]);
//    }
//  printf ("\n");
  /**
   * check device file current status.
   */
  if (device_is_opened (&cbs->m_dev) < 0)
    {
      ret = ZRC_DeviceFileNotOpened;
    }
  else
    {
      pData = (zuint8_t*) pktRecv.pFrameType;
      dataSize = sizeof(*pktRecv.pFrameType) + ///<
	  sizeof(*pktRecv.pFrameLength) + (*pktRecv.pFrameLength);
      /**
       * aligned by 8 bytes for FPGA.
       */
      if (dataSize % 8 != 0)
	{
	  dataSize += 8 - dataSize % 8;
	}

      /**
       * FPGA only knows the Big Endian byte order.
       * so here do convert.
       */
      reverse_int32 (pktRecv.pFrameType);
      reverse_int32 (pktRecv.pFrameLength);
      ret = device_write_dma (&cbs->m_dev, pData, dataSize);
//      printf ("write to DMA:%d bytes\n", dataSize);
//      for (unsigned int j = 0; j < dataSize; j++)
//	{
//	  printf ("%02x,", pData[j]);
//	  if ((j + 1) % 16 == 0)
//	    {
//	      printf ("\n");
//	    }
//	}
//      printf ("\n");
    }
  /**
   * build an ACK packet.
   */
  /**
   * step1.
   * add 8 bytes fixed header
   */
  add_zpktnet_fixed_head (pktnet);

  /**
   * step2.
   * add 4 bytes frame type & 4 bytes frame length.
   */
  pktnet->pkt->type = htonl (PKT_SUBTITLE_OVERLAY_ELEMENT_ACK);
  /**
   * the real data we want to send out.
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
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * the end of file,tagged by zhangshaoyan.
 * shell.albert@gmail.com.
 */

