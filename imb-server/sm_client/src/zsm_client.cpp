/*
 * zsm_client.c
 *
 *  Created on: Oct 17, 2014
 *      Author: root
 */

/**
 * command parse for sm client & sm server.
 * added by zhangshaoyan October 17,2014.
 * To solve the problem of network crossing communicate with SM server.
 */
#include <zsm_client.h>
#include <zprotocol.h>

/**
 * use sm (libsmsdk.so)
 * or bypass it.
 */
#define  USE_SM_SERVER	1
/**
 * step2.
 * ret=sm->loadCertificateChainFile("certchain.data");
 */
zint32_t
cmd_sm_load_certificate_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  /**
   * data flow:
   * SDK client --> SDK Server (SM Client) --> SM Server
   * receive Certificate Chain file from socket,
   * and save in temporary file.
   * then call libsmsdk.so interface to send it to SM server.
   */

  FILE *fp;
  int file_len;
  zint32_t ret = ZRC_Success;
  MMAP_SM_LOAD_CERTIFICATE_FILE smobj;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  if (mmap_sm_load_certificate_file (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_load_certificate_file() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  do
    {
      /**
       * open certificate chain file.
       */
      fp = fopen (TMP_FILE_CERTIFICATE_CHAIN, "w");
      if (fp == NULL)
	{
	  printf ("sm:open %s failed:%s\n", TMP_FILE_CERTIFICATE_CHAIN, strerror (errno));
	  ret = ZRC_OpenLocalFileFailed;
	  break;
	}
      /**
       * write data to file.
       */
      file_len = ntohl (*smobj.pfile_len);
      if (fwrite (smobj.pfile_data, file_len, 1, fp) != 1)
	{
	  printf ("sm:fwrite() failed:%s\n", strerror (errno));
	  ret = ZRC_WriteLocalFileFailed;
	  break;
	}
      /**
       * close file.
       */
      fclose (fp);
      printf ("sm:write to temporary file %s success!\n", TMP_FILE_CERTIFICATE_CHAIN);
      /**
       * if no error occurs,call libsmsdk.so.
       */
#ifdef USE_SM_SERVER
      ret = cbs->m_sm->loadCertificateChainFile (TMP_FILE_CERTIFICATE_CHAIN);
      if (ret < 0)
	{
	  ret=ZRC_SMLoadCertChainFileFailed;
	}
      printf ("sm:m_sm->loadCertificateChainFile()-->return code:%d\n", ret);
#endif
    }
  while (0);

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
  pktnet->pkt->type = htonl (PKT_SM_LOAD_CERTCHAIN_FILE_ACK);
  if (mmap_sm_load_certificate_file (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_load_certificate_file() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step3.
 * ret=sm->loadPrivateKeyFile("SMStheLeafprikey.pem");
 */
zint32_t
cmd_sm_load_privatekey_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  FILE *fp;
  int file_len;
  zint32_t ret = ZRC_Success;
  MMAP_SM_LOAD_PRIVATEKEY_FILE smobj;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  /**
   * data flow:
   * SDK client --> SDK Server (SM Client) --> SM Server
   * receive private key file from socket,
   * and save in temporary file.
   * then call libsmsdk.so interface to send it to SM server.
   */
  if (mmap_sm_load_private_file (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_load_private_file() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  do
    {
      /**
       * open temporary private key file.
       */
      fp = fopen (TMP_FILE_PRIVATE_KEY, "w");
      if (fp == NULL)
	{
	  printf ("sm:open %s failed:%s\n", TMP_FILE_PRIVATE_KEY, strerror (errno));
	  ret = ZRC_OpenLocalFileFailed;
	  break;
	}
      /**
       * write data to file.
       */
      file_len = ntohl (*smobj.pfile_len);
      if (fwrite (smobj.pfile_data, file_len, 1, fp) != 1)
	{
	  printf ("sm:fwrite() failed:%s\n", strerror (errno));
	  ret = ZRC_WriteLocalFileFailed;
	  break;
	}
      /**
       * close file.
       */
      fclose (fp);
      printf ("sm:write to temporary file %s success!\n", TMP_FILE_PRIVATE_KEY);
      /**
       * if no error occurs,call libsmsdk.so.
       */
#ifdef USE_SM_SERVER
      ret = cbs->m_sm->loadPrivateKeyFile (TMP_FILE_PRIVATE_KEY);
      if (ret < 0)
	{
	  ret=ZRC_SMLoadPrivateKeyFileFailed;
	}
      printf ("m_sm->loadPrivateKeyFile()-->return code:%d\n", ret);
#endif
    }
  while (0);

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
  pktnet->pkt->type = htonl (PKT_SM_LOAD_PRIVATEKEY_FILE_ACK);
  if (mmap_sm_load_private_file (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_load_private_file() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step4.
 * ret=sm->connect();
 */
zint32_t
cmd_sm_connect (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_CONNECT smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  ret = cbs->m_sm->connect ();
  if(ret<0)
    {
      ret=ZRC_SMConnectFailed;
    }
  printf ("sm:m_sm->connect()-->return code:%d\n", ret);
#endif

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
  pktnet->pkt->type = htonl (PKT_SM_CONNECT_ACK);
  if (mmap_sm_connect (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_connect() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step5.
 * ret=sm->startSuite();
 */
zint32_t
cmd_sm_start_suite (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_STARTSUITE smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  ret = cbs->m_sm->startSuite ();
  if(ret<0)
    {
      ret=ZRC_SMStartSuiteFailed;
    }
  printf ("sm:m_sm->startSuite()-->return code:%d\n", ret);
#endif
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
  pktnet->pkt->type = htonl (PKT_SM_STARTSUITE_ACK);
  if (mmap_sm_startsuite (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_startsuite() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step6.
 * ret=sm->uploadCplFile();
 */
zint32_t
cmd_sm_upload_cpl_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{

  /**
   * data flow:
   * SDK client --> SDK Server (SM Client) --> SM Server
   * receive cpl file from socket,
   * and save in temporary file.
   * then call libsmsdk.so interface to send it to SM server.
   */

  FILE *fp;
  int file_len;
  zint32_t ret = ZRC_Success;
  MMAP_SM_UPLOAD_CPL smobj;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_uploadcpl (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_uploadcpl() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  do
    {
      /**
       * open temporary cpl file.
       */
      fp = fopen (TMP_FILE_CPL, "wb");
      if (fp == NULL)
	{
	  printf ("sm:open %s failed:%s\n", TMP_FILE_PRIVATE_KEY, strerror (errno));
	  ret = ZRC_OpenLocalFileFailed;
	  break;
	}
      /**
       * write data to file.
       */
      file_len = ntohl (*smobj.pfile_len);
      if (fwrite (smobj.pfile_data, file_len, 1, fp) != 1)
	{
	  printf ("sm:fwrite() failed:%s\n", strerror (errno));
	  ret = ZRC_WriteLocalFileFailed;
	  break;
	}
      /**
       * close file.
       */
      fclose (fp);
      printf ("sm:write to temporary file %s success!\n", TMP_FILE_CPL);
      /**
       * if no error occurs,call libsmsdk.so.
       */
#ifdef USE_SM_SERVER
      ret = cbs->m_sm->uploadCplFile (TMP_FILE_CPL, CplException_None);
      if (ret < 0)
	{
	  ret=ZRC_SMUploadCplFileFailed;
	}
      printf ("m_sm->uploadCplFile()-->return code:%d\n", ret);
#endif
    }
  while (0);

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
  pktnet->pkt->type = htonl (PKT_SM_UPLOAD_CPL_FILE_ACK);
  if (mmap_sm_uploadcpl (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_uploadcpl() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step7.
 * ret=sm->uploadKdmFile();
 */
zint32_t
cmd_sm_upload_kdm_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  /**
   * data flow:
   * SDK client --> SDK Server (SM Client) --> SM Server
   * receive kdm file from socket,
   * and save in temporary file.
   * then call libsmsdk.so interface to send it to SM server.
   */

  FILE *fp;
  int file_len;
  zint32_t ret = ZRC_Success;
  MMAP_SM_UPLOAD_KDM smobj;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_uploadkdm (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_uploadkdm() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  do
    {
      /**
       * open temporary kdm file.
       */
      fp = fopen (TMP_FILE_KDM, "wb");
      if (fp == NULL)
	{
	  printf ("sm:open %s failed:%s\n", TMP_FILE_PRIVATE_KEY, strerror (errno));
	  ret = ZRC_OpenLocalFileFailed;
	  break;
	}
      /**
       * write data to file.
       */
      /**
       * network byte order convert.
       */
      file_len = ntohl (*smobj.pfile_len);
      if (fwrite (smobj.pfile_data, file_len, 1, fp) != 1)
	{
	  printf ("sm:fwrite() failed:%s\n", strerror (errno));
	  ret = ZRC_WriteLocalFileFailed;
	  break;
	}
      /**
       * close file.
       */
      fclose (fp);
      printf ("sm:write to temporary file %s success!\n", TMP_FILE_KDM);
      /**
       * if no error occurs,call libsmsdk.so.
       */
#ifdef USE_SM_SERVER
      ret = cbs->m_sm->uploadKdmFile (TMP_FILE_KDM);
      if (ret < 0)
	{
	  ret=ZRC_SMUploadKdmFileFailed;
	}
      printf ("m_sm->uploadKdmFile()-->return code:%d\n", ret);
#endif
    }
  while (0);

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
  pktnet->pkt->type = htonl (PKT_SM_UPLOAD_KDM_FILE_ACK);
  if (mmap_sm_uploadkdm (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_uploadkdm() failed!\n");
      return -1;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step8.
 * ret=sm->playShow();
 */
zint32_t
cmd_sm_play_show (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_PLAYSHOW smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_playshow (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_playshow() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * check the parameters.
   */
  printf ("authId_len:%d\n", ntohl (*smobj.pauthId_len));
  printf ("authId:%s\n", smobj.pauthId);
  printf ("UuidValue:");
  for (int i = 0; i < 16; i++)
    {
      printf ("%x ", *(smobj.puuidValue + i));
    }
  printf ("\n");

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  inner_sm::UuidValue *cplUuidArray = new inner_sm::UuidValue (smobj.puuidValue);
  /**
   * in 32-bit platform,sizeof(long long)=8.
   * in 64-bit platform,sizeof(long)=8.
   */
  long long keyExpTime64, tmp64;
  tmp64 = ntohl (*smobj.pkeyExpTime_high);
  keyExpTime64 = tmp64 << 32;
  tmp64 = ntohl (*smobj.pkeyExpTime_low);
  keyExpTime64 |= tmp64 << 0;
  printf ("keyExpTime=%lld\n", keyExpTime64);
  /**
   * if no error occurs,call libsmsdk.so.
   */
  ret = cbs->m_sm->playShow ((const char*) smobj.pauthId, ///<
      cplUuidArray, *smobj.parrayLen, (uint64_t*) &keyExpTime64);
  if(ret<0)
    {
      ret=ZRC_SMPlayShowFailed;
    }
  delete cplUuidArray;

  printf ("m_sm->playShow()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_PLAYSHOW_ACK);
  if (mmap_sm_playshow (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_playshow() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step9.
 * ret=sm->stopShow();
 */
zint32_t
cmd_sm_stop_show (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_STOPSHOW smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_stopshow (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_stopshow() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * if no error occurs,call libsmsdk.so.
   */
  printf ("stopShow():authId=%s\n", smobj.pauthId);
#ifdef USE_SM_SERVER
  ret = cbs->m_sm->stopShow ((const char*) smobj.pauthId);
  if(ret<0)
    {
      ret=ZRC_SMStopShowFailed;
    }
  printf ("sm:m_sm->stopShow()-->return code:%d\n", ret);
#endif

  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_STOPSHOW_ACK);
  if (mmap_sm_stopshow (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_stopshow() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * real data want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step10.
 * ret=sm->purgeCpl();
 */
zint32_t
cmd_sm_purge_cpl (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_PURGECPL smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }

  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }
  if (mmap_sm_purgecpl (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_purgecpl() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
  printf ("purgeCpl:UuidValue:");
  for (int i = 0; i < 16; i++)
    {
      printf ("%x ", *(smobj.puuidValue + i));
    }
  printf ("\n");
#ifdef USE_SM_SERVER
  inner_sm::UuidValue cplUuid (smobj.puuidValue);
  ret = cbs->m_sm->purgeCpl (cplUuid);
  if(ret<0)
    {
      ret=ZRC_SMPurgeCplFailed;
    }
  printf ("sm:m_sm->purgeCpl()-->return code:%d\n", ret);
#endif

  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_PURGECPL_ACK);
  if (mmap_sm_purgecpl (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_purgecpl() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data we want to send out.
   */
  *smobj.pret_code = ret;

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * step11.
 * ret=sm->stopSuite();
 */
zint32_t
cmd_sm_stop_suite (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_STOPSUITE smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  ret = cbs->m_sm->stopSuite ();
  if(ret<0)
    {
      ret=ZRC_SMStopSuiteFailed;
    }
  printf ("sm:m_sm->stopSuite()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_STOPSUITE_ACK);
  if (mmap_sm_stopsuite (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_stopsuite() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
////////////////////////////////////////////////
/**
 * added by zhangshaoyan at November 3,2014.
 * for support SM.
 */
/**
 * TMmRc uploadKdmBuffer( const uint8_t *kdmBuffer, uint32_t bufferSize, AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0 );
 */
/**
 * TMmRc checkShow( const inner_sm::UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0 );
 */
zint32_t
cmd_sm_checkshow (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  return 0;
}
zint32_t
cmd_sm_uploadkdmbuffer (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  return 0;
}
/**
 * TMmRc uploadCplBuffer( const uint8_t *cplBuffer, uint32_t bufferSize, CPL_ASSET_EXCEPTION assetExc = CplException_None );
 */
zint32_t
cmd_sm_uploadcplbuffer (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_UPLOADCPLBUFFER smobj;
  zint32_t ret = ZRC_Success;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_uploadcplbuffer (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_uploadcplbuffer() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.passetExc = ntohl (*smobj.passetExc);
  *smobj.pbuffersize = ntohl (*smobj.pbuffersize);
  smobj.pcplbuffer[*smobj.pbuffersize] = '\0';
  ret = cbs->m_sm->uploadCplBuffer (smobj.pcplbuffer, *smobj.pbuffersize, (enum CPL_ASSET_EXCEPTION) (*smobj.passetExc));
  if(ret<0)
    {
      ret=ZRC_SMUploadCplBufferFailed;
    }
  printf ("sm:m_sm->uploadCplBuffer()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_UPLOADCPLBUFFER_ACK);
  if (mmap_sm_uploadcplbuffer (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_uploadcplbuffer() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * TMmRc getCplList( inner_sm::UuidValue *cplUuidArray, uint32_t *arrayLen );
 */
zint32_t
cmd_sm_getcpllist (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_GETCPLLIST smobj;
  zint32_t ret = ZRC_Success;
  inner_sm::UuidValue *uuid = NULL;
  uint32_t arraylen;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_getcpllist (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_getcpllist() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  ret = cbs->m_sm->getCplList (uuid, &arraylen);
  if(ret<0)
    {
      ret=ZRC_SMGetCplListFailed;
    }
  printf ("sm:m_sm->getCplList()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_GETCPLLIST_ACK);
  if (mmap_sm_getcpllist (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_getcpllist() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  *smobj.parrayLen = arraylen * UUID_LEN;
  for (unsigned int i = 0; i < arraylen; i++)
    {
      unsigned char buffer[16];
      (uuid + i)->toArray (buffer);
      memcpy (smobj.pcplUuidArray + i * UUID_LEN, buffer, UUID_LEN);
    }
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code) + ///<
      sizeof(*smobj.parrayLen) + (*smobj.parrayLen);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */

  *smobj.pret_code = htonl (*smobj.pret_code);
  *smobj.parrayLen = htonl (*smobj.parrayLen);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * TMmRc getKdmList( const inner_sm::UuidValue &cplUuid, inner_sm::UuidValue *kdmUuidArray, uint32_t *arrayLen );
 */
zint32_t
cmd_sm_getkdmlist (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_GETKDMLIST smobj;
  int ret = 0;
  inner_sm::UuidValue *cplUuid = NULL;
  inner_sm::UuidValue *kdmUuidArray = NULL;
  uint32_t arrayLen;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_getkdmlist (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_getkdmlist() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pcpluuid_len = ntohl (*smobj.pcpluuid_len);
  cplUuid = new inner_sm::UuidValue (smobj.pcpluuid);
  ret = cbs->m_sm->getKdmList (*cplUuid, kdmUuidArray, &arrayLen);
  if(ret<0)
    {
      ret=ZRC_SMGetKdmListFailed;
    }
  printf ("sm:m_sm->getKdmList()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_GETKDMLIST_ACK);
  if (mmap_sm_getkdmlist (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_getkdmlist() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  *smobj.parrayLen = arrayLen * UUID_LEN;
  for (unsigned int i = 0; i < arrayLen; i++)
    {
      unsigned char buffer[16];
      (kdmUuidArray + i)->toArray (buffer);
      memcpy (smobj.pkdmUuidArray + i * UUID_LEN, buffer, UUID_LEN);
    }
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code) + ///<
      sizeof(*smobj.parrayLen) + (*smobj.parrayLen);
  pktnet->pkt->len = *smobj.pvalid_len;

  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  *smobj.parrayLen = htonl (*smobj.parrayLen);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * TMmRc adjustTime( const char *authId, uint32_t diff );
 */
zint32_t
cmd_sm_adjusttime (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_ADJUSTTIME smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_adjusttime (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_adjusttime() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pdiff = ntohl (*smobj.pdiff);
  *smobj.pauthId_len = ntohl (*smobj.pauthId_len);
  /**
   * add terminator.
   */
  smobj.pauthId[*smobj.pauthId_len] = '\0';
  printf ("authId=%s\n", smobj.pauthId);
  printf ("diff=%d\n", *smobj.pdiff);
  ret = cbs->m_sm->adjustTime ((const char*) smobj.pauthId, *smobj.pdiff);
  if(ret<0)
    {
      ret=ZRC_SMAdjustTimeFailed;
    }
  printf ("sm:m_sm->adjustTime()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_ADJUSTTIME_ACK);
  if (mmap_sm_adjusttime (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_adjusttime() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * TMmRc getCertificate( uint32_t which, uint8_t *buffer, uint32_t *buffersize );
 */
zint32_t
cmd_sm_getcertificate (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_GETCERTIFICATE smobj;
  zint32_t ret = ZRC_Success;
  unsigned char *buffer;
  unsigned int buffersize;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_getcertificate (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_getcertificate() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pwhich = ntohl (*smobj.pwhich);
  buffer = (unsigned char*) malloc (1 * 1024 * 1024);
  if (buffer == NULL)
    {
      printf("failed to malloc():%s\n", strerror(errno));
      return -1;
    }
  buffersize = 1 * 1024 * 1024;
  ret = cbs->m_sm->getCertificate (*smobj.pwhich, buffer, &buffersize);
  if(ret<0)
    {
      ret=ZRC_SMGetCertificateFailed;
    }
  printf ("sm:m_sm->getCertificate()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_GETCERTIFICATE_ACK);
  if (mmap_sm_getcertificate (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_getcertificate() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  *smobj.pbuffersize = buffersize;
  memcpy (smobj.pbuffer, buffer, buffersize);

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code) + ///<
      sizeof(*smobj.pbuffersize) + (*smobj.pbuffersize);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  *smobj.pbuffersize = htonl (*smobj.pbuffersize);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  if (buffer != NULL)
    {
      free (buffer);
    }
  return ret;
}
/**
 * TMmRc queryStatus( SM_OPERATION *smOp, SUITE_STATUS *suiteStat, uint64_t *secureTime, int32_t *time_adjust );
 */
zint32_t
cmd_sm_querystatus (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_QUERYSTATUS smobj;
  zint32_t ret = ZRC_Success;
  enum SM_OPERATION smop;
  enum SUITE_STATUS suitestat;
  uint64_t securetime, tmp64;
  int32_t timeadjust;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_querystatus (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_querystatus() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  ret = cbs->m_sm->queryStatus (&smop, &suitestat, &securetime, &timeadjust);
  if(ret<0)
    {
      ret=ZRC_SMQueryStatusFailed;
    }
  printf ("sm:m_sm->queryStatus()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_QUERYSTATUS_ACK);
  if (mmap_sm_querystatus (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_querystatus() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  *smobj.psm_operation = smop;
  *smobj.psuite_status = suitestat;
  *smobj.ptime_adjust = timeadjust;
  tmp64 = securetime & 0xFFFFFFFF;
  *smobj.psecureTime_low = (int32_t) tmp64;
  tmp64 = (securetime & (~0xFFFFFFFF));
  tmp64 >>= 32;
  *smobj.psecureTime_high = (int32_t) tmp64;

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code) + ///<
      sizeof(*smobj.psm_operation) + sizeof(*smobj.psuite_status) + ///<
      sizeof(*smobj.psecureTime_high) + sizeof(*smobj.psecureTime_low) +  ///<
      sizeof(*smobj.ptime_adjust);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  *smobj.psm_operation = htonl (*smobj.psm_operation);
  *smobj.psuite_status = htonl (*smobj.psuite_status);
  *smobj.psecureTime_low = htonl (*smobj.psecureTime_low);
  *smobj.psecureTime_high = htonl (*smobj.psecureTime_high);
  *smobj.ptime_adjust = htonl (*smobj.ptime_adjust);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * TMmRc getLogReport( uint8_t *buffer, uint32_t *buffersize, uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime );
 */
zint32_t
cmd_sm_getlogreport (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_GETLOGREPORT smobj;
  zint32_t ret = ZRC_Success;
  unsigned char *buffer;
  unsigned int buffersize;
  uint64_t startTime64, endTime64;
  uint64_t lastLogTime, tmp64;

  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_getlogreport (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_getlogreport() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pstartTime_high = ntohl (*smobj.pstartTime_high);
  *smobj.pstartTime_low = ntohl (*smobj.pstartTime_low);
  *smobj.pendTime_high = ntohl (*smobj.pendTime_high);
  *smobj.pendTime_low = ntohl (*smobj.pendTime_low);

  buffer = (unsigned char*) malloc (1 * 1024 * 1024);
  if (buffer == NULL)
    {
      printf("failed to malloc():%s\n", strerror(errno));
      return -1;
    }
  buffersize = 1 * 1024 * 1024;
  startTime64 = ((uint64_t) (*smobj.pstartTime_high) << 32) | (*smobj.pstartTime_low);
  endTime64 = ((uint64_t) (*smobj.pendTime_high) << 32) | (*smobj.pendTime_low);
  ret = cbs->m_sm->getLogReport (buffer, &buffersize, startTime64, endTime64, &lastLogTime);
  if(ret<0)
    {
      ret=ZRC_SMGetLogReportFailed;
    }
  printf ("sm:m_sm->getLogReport()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_GETLOGREPORT_ACK);
  if (mmap_sm_getlogreport (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_getlogreport() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  tmp64 = (lastLogTime & 0xFFFFFFFF);
  *smobj.plastLogTime_low = (int32_t) tmp64;
  tmp64 = (lastLogTime & (~0xFFFFFFFF)) >> 32;
  *smobj.plastLogTime_high = (int32_t) tmp64;

  *smobj.pbuffersize = buffersize;
  memcpy (smobj.pbuffer, buffer, buffersize);

  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code) + ///<
      sizeof(*smobj.plastLogTime_high) + sizeof(*smobj.plastLogTime_low) + ///<
      sizeof(*smobj.pbuffersize) + (*smobj.pbuffersize);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * packet length.
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  *smobj.plastLogTime_high = htonl (*smobj.plastLogTime_high);
  *smobj.plastLogTime_low = htonl (*smobj.plastLogTime_low);
  *smobj.pbuffersize = htonl (*smobj.pbuffersize);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  if (buffer != NULL)
    {
      free (buffer);
    }
  return ret;
}
/**
 * TMmRc initiateMarriage( const char *authId );
 */
zint32_t
cmd_sm_initiatemarriage (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_INITIATEMARRIAGE smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_initiatemarriage (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_initiatemarriage() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pauthId_len = ntohl (*smobj.pauthId_len);
  /**
   * add terminator.
   */
  smobj.pauthId[*smobj.pauthId_len] = '\0';
  printf ("authId=%s\n", smobj.pauthId);
  ret = cbs->m_sm->initiateMarriage ((const char*) smobj.pauthId);
  if(ret<0)
    {
      ret=ZRC_SMInitiateMarriageFailed;
    }
  printf ("sm:m_sm->initiateMarriage()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_INITIATEMARRIAGE_ACK);
  if (mmap_sm_initiatemarriage (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_initiatemarriage() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * TMmRc serviceDoorTamperTermination( const char *authId );
 */
zint32_t
cmd_sm_servicedoortampertermination (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_SERVICEDOORTAMPERTERMINATION smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_servicedoortampertermination (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_servicedoortampertermination() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pauthId_len = ntohl (*smobj.pauthId_len);
  /**
   * add terminator.
   */
  smobj.pauthId[*smobj.pauthId_len] = '\0';
  printf ("authId=%s\n", smobj.pauthId);
  ret = cbs->m_sm->serviceDoorTamperTermination ((const char*) smobj.pauthId);
  if(ret<0)
    {
      ret=ZRC_SMServiceDoorTamperTerminationFailed;
    }
  printf ("m_sm->serviceDoorTamperTermination()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_SERVICEDOORTAMPERTERMINATION_ACK);
  if (mmap_sm_servicedoortampertermination (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_servicedoortampertermination() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}
/**
 * TMmRc getKeyMap( KeyMap *keymapArray, uint32_t *numberOfEntries );
 */
zint32_t
cmd_sm_getkeymap (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  return 0;
}
/**
 * TMmRc addCertificate( void *cert );
 */
zint32_t
cmd_sm_addcertificate (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_ADDCERTIFICATE smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_addcertificate (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_useprivatekey() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pcert_len = ntohl (*smobj.pcert_len);
  /**
   * add terminator.
   */
  smobj.pcert[*smobj.pcert_len] = '\0';
  printf ("pcert=%s\n", smobj.pcert);
  ret = cbs->m_sm->addCertificate (smobj.pcert);
  if(ret<0)
    {
      ret=ZRC_SMAddCertificateFailed;
    }
  printf ("m_sm->addCertificate()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_ADDCERTIFICATE_ACK);
  if (mmap_sm_addcertificate (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_addcertificate() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * TMmRc usePrivateKey( void *pkey );
 */
zint32_t
cmd_sm_useprivatekey (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_USEPRIVATEKEY smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }
  if (mmap_sm_useprivatekey (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_useprivatekey() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pkey_len = ntohl (*smobj.pkey_len);
  /**
   * add terminator.
   */
  smobj.pkey[*smobj.pkey_len] = '\0';
  printf ("pkey=%s\n", smobj.pkey);
  ret = cbs->m_sm->usePrivateKey (smobj.pkey);
  if(ret<0)
    {
      ret=ZRC_SMUsePrivateKeyFailed;
    }
  printf ("m_sm->usePrivateKey()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_USEPRIVATEKEY_ACK);
  if (mmap_sm_useprivatekey (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_useprivatekey() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);
  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * TMmRc zeroize( const char *authId );
 */
zint32_t
cmd_sm_zeroize (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet)
{
  MMAP_SM_ZEROIZE smobj;
  zint32_t ret = ZRC_Success;
  /**
   * check validation of parameters.
   */
  if (cbs == NULL || pkt_fifo == NULL || pktnet == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check security manager.
   */
  if (cbs->m_sm == NULL)
    {
      printf ("sm:invalid SM object!\n");
      return ZRC_NullPointer;
    }

  if (mmap_sm_zeroize (&smobj, pkt_fifo->data, DIRECTION_SDK_TO_IMBSERVER) < 0)
    {
      printf ("sm:mmap_sm_purgecpl() failed!\n");
      return ZRC_MmapStructureFailed;
    }

  /**
   * if no error occurs,call libsmsdk.so.
   */
#ifdef USE_SM_SERVER
  /**
   * network byte order to host byte order.
   */
  *smobj.pauthId_len = ntohl (*smobj.pauthId_len);

  /**
   * add terminator.
   */
  smobj.pauthId[*smobj.pauthId_len] = '\0';
  printf ("authId=%s\n", smobj.pauthId);
  ret = cbs->m_sm->zeroize ((const char*) smobj.pauthId);
  if(ret<0)
    {
      ret=ZRC_SMZeroizeFailed;
    }
  printf ("m_sm->zeroize()-->return code:%d\n", ret);
#endif
  /**
   * build an ACK packet and send back to client.
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
  pktnet->pkt->type = htonl (PKT_SM_ZEROIZE_ACK);
  if (mmap_sm_zeroize (&smobj, pktnet->pkt->data, DIRECTION_IMBSERVER_TO_SDK) < 0)
    {
      printf ("sm:mmap_sm_zeroize() failed!\n");
      return ZRC_MmapStructureFailed;
    }
  /**
   * the real data that we want to send out.
   */
  *smobj.pret_code = ret;
  /**
   * set packet length.
   */
  *smobj.pvalid_len = sizeof(*smobj.pvalid_len) + sizeof(*smobj.pret_code);
  pktnet->pkt->len = *smobj.pvalid_len;
  /**
   * host byte order to network byte order.
   */
  *smobj.pret_code = htonl (*smobj.pret_code);
  pktnet->pkt->len = htonl (pktnet->pkt->len);

  /**
   * send out.
   */
  ret = send_zpknet (pktnet);
  return ret;
}

/**
 * the end of file,tagged by zhangshaoyan.
 * at October 20,2014.
 */

