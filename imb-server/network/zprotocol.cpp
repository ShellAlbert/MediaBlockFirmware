/*
 * zprotocol.cpp
 *
 *  Created on: Oct 21, 2014
 *      Author: root
 */
#include <zprotocol.h>
#include <zerrno.h>
zint32_t
mmap_query_card_info (MMAP_QUERY_CARD_INFO *mm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (mm == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }
  /**
   * Assign pointer with address value.
   */
  offset = 0x0;
  mm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*mm->pvalid_len);

  switch (direction)
    {
    case DIRECTION_SDK_TO_IMBSERVER:
    case DIRECTION_IMBSERVER_TO_SDK:
      mm->ptotal = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->ptotal);

      mm->pcard = (zuint8_t*) (buffer + offset);
      break;
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
zint32_t
mmap_query_cpu_info (MMAP_QUERY_CPU_INFO *mm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (mm == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }
  /**
   * Assign pointer with address value.
   */
  offset = 0x0;
  mm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*mm->pvalid_len);
  switch (direction)
    {
    case DIRECTION_SDK_TO_IMBSERVER:
      break;
    case DIRECTION_IMBSERVER_TO_SDK:
      mm->pret_code = (zint32_t*) (buffer + offset);
      offset += sizeof(*mm->pret_code);

      mm->ptotal_cores = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->ptotal_cores);

      mm->pcores_freq = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pcores_freq);
      break;
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
zint32_t
mmap_mem_info (MMAP_MEM_INFO *mm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (mm == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }
  /**
   * Assign pointer with address value.
   */
  offset = 0x0;
  mm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*mm->pvalid_len);
  switch (direction)
    {
    case DIRECTION_SDK_TO_IMBSERVER:
      break;
    case DIRECTION_IMBSERVER_TO_SDK:
      mm->pret_code = (zint32_t*) (buffer + offset);
      offset += sizeof(*mm->pret_code);

      mm->pmem_total = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pmem_total);

      mm->pmem_free = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pmem_free);
      break;
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
zint32_t
mmap_fpga_rw_register (MMAP_FPGA_RW_REGISTER *mm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (mm == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  /**
   * Assign pointer with address value.
   */
  offset = 0x0;
  mm->pvalid_len = (zuint32_t*) (buffer + offset);
  /**
   * caution here.
   * we should use sizeof(*ptr) instread of sizeof(ptr).
   *
   * int 64-bit OS:
   * unsigned int a;
   * unsigned int *b=&a;
   * sizeof(a)=4;
   * sizeof(b)=8
   * sizeof(*b)=4.
   */
  offset += sizeof(*mm->pvalid_len);
  switch (direction)
    {
    /**
     * SDK --> IMB server.
     * read or write mode indicator.
     * register address for read&write operation.
     * register value for write operation.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      mm->prd_wr = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->prd_wr);

      mm->pregs_address = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pregs_address);

      mm->pregs_value = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pregs_value);

      mm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pret_code);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      mm->prd_wr = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->prd_wr);

      mm->pregs_address = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pregs_address);

      mm->pregs_value = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pregs_value);

      mm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pret_code);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
zint32_t
mmap_open_device_file (MMAP_OPEN_DEVICE_FILE *mm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (mm == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }
  /**
   * Assign pointer with address value.
   */
  offset = 0x0;
  mm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*mm->pvalid_len);

  switch (direction)
    {
    case DIRECTION_SDK_TO_IMBSERVER:
      mm->pfile_num = (zuint32_t*) (buffer + offset);
      break;
    case DIRECTION_IMBSERVER_TO_SDK:
      mm->pret_code = (zuint32_t*) (buffer + offset);
      break;
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * memory map plain buffer to MMAP_SM_LOAD_CERTIFICATE_FILE.
 * easy to operate.
 */
zint32_t
mmap_sm_load_certificate_file (MMAP_SM_LOAD_CERTIFICATE_FILE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  /**
   * caution here.
   * we should use sizeof(*ptr) instread of sizeof(ptr).
   *
   * int 64-bit OS:
   * unsigned int a;
   * unsigned int *b=&a;
   * sizeof(a)=4;
   * sizeof(b)=8
   * sizeof(*b)=4.
   */
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pfile_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pfile_len);
      sm->pfile_data = (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_LOAD_PRIVATEKEY_FILE.
 * easy to operate.
 */
zint32_t
mmap_sm_load_private_file (MMAP_SM_LOAD_PRIVATEKEY_FILE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pfile_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pfile_len);
      sm->pfile_data = (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_CONNECT.
 * easy to operate.
 */
zint32_t
mmap_sm_connect (MMAP_SM_CONNECT *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pconnect_timeout = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pconnect_timeout);
      sm->pconnect_retry_times = (zuint32_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_STARTSUITE.
 * easy to operate.
 */
zint32_t
mmap_sm_startsuite (MMAP_SM_STARTSUITE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_UPLOAD_CPL.
 * easy to operate.
 */
zint32_t
mmap_sm_uploadcpl (MMAP_SM_UPLOAD_CPL *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pfile_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pfile_len);
      sm->pfile_data = (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_UPLOAD_KDM.
 * easy to operate.
 */
zint32_t
mmap_sm_uploadkdm (MMAP_SM_UPLOAD_KDM *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pfile_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pfile_len);
      sm->pfile_data = (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_PLAYSHOW.
 * easy to operate.
 */
zint32_t
mmap_sm_playshow (MMAP_SM_PLAYSHOW *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pauthId = (buffer + offset);
      offset += sizeof(*sm->pauthId) * AUTHID_LEN;

      sm->pauthId_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pauthId_len);

      sm->puuidValue = (buffer + offset);
      offset += sizeof(*sm->puuidValue) * UUID_LEN;

      sm->parrayLen = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->parrayLen);

      sm->pkeyExpTime_high = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pkeyExpTime_high);

      sm->pkeyExpTime_low = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pkeyExpTime_low);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_STOPSHOW.
 * easy to operate.
 */
zint32_t
mmap_sm_stopshow (MMAP_SM_STOPSHOW *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pauthId = (buffer + offset);
      offset += sizeof(*sm->pauthId) * AUTHID_LEN;

      sm->pauthId_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pauthId_len);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_PURGECPL.
 * easy to operate.
 */
zint32_t
mmap_sm_purgecpl (MMAP_SM_PURGECPL *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->puuidValue = (buffer + offset);
      offset += sizeof(*sm->puuidValue) * AUTHID_LEN;
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_STOPSUITE.
 * easy to operate.
 */
zint32_t
mmap_sm_stopsuite (MMAP_SM_STOPSUITE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 *
 *
 *
 * added by zhangshaoyan at October 28,2014.
 * for support other features of SM.
 *
 *
 *
 */
/**
 * memory map plain buffer to MMAP_SM_UPLOADKDMBUFFER.
 * easy to operate.
 */
zint32_t
mmap_sm_uploadkdmbuffer (MMAP_SM_UPLOADKDMBUFFER *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pbuffersize = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pbuffersize);

      sm->pkdmbuffer = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_UPLOADCPLBUFFER.
 * easy to operate.
 */
zint32_t
mmap_sm_uploadcplbuffer (MMAP_SM_UPLOADCPLBUFFER *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:

      sm->passetExc = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->passetExc);

      sm->pbuffersize = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pbuffersize);

      sm->pcplbuffer = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_GETCPLLIST.
 * easy to operate.
 */
zint32_t
mmap_sm_getcpllist (MMAP_SM_GETCPLLIST *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:

      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);

      sm->parrayLen = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->parrayLen);

      sm->pcplUuidArray = (zuint8_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_GETKDMLIST.
 * easy to operate.
 */
extern zint32_t
mmap_sm_getkdmlist (MMAP_SM_GETKDMLIST *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pcpluuid_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pcpluuid_len);

      sm->pcpluuid = (zuint8_t*) (buffer + offset);

      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);

      sm->parrayLen = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->parrayLen);

      sm->pkdmUuidArray = (zuint8_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_CHECKSHOW.
 * easy to operate.
 */
zint32_t
mmap_sm_checkshow (MMAP_SM_CHECKSHOW *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pchecktime_high = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pchecktime_high);

      sm->pchecktime_low = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pchecktime_low);

      sm->parraylen = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->parraylen);

      sm->pcpluuidarray = (zuint8_t*) (buffer + offset);

      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);

      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_ADJUSTTIME.
 * easy to operate.
 */
zint32_t
mmap_sm_adjusttime (MMAP_SM_ADJUSTTIME *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pdiff = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pdiff);

      sm->pauthId_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pauthId_len);

      sm->pauthId = (zuint8_t*) (buffer + offset);

      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);

      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_GETCERTIFICATE.
 * easy to operate.
 */
zint32_t
mmap_sm_getcertificate (MMAP_SM_GETCERTIFICATE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pwhich = (zuint32_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);

      sm->pbuffersize = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pbuffersize);

      sm->pbuffer = (zuint8_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_QUERYSTATUS.
 * easy to operate.
 */
zint32_t
mmap_sm_querystatus (MMAP_SM_QUERYSTATUS *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:

      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);

      sm->psm_operation = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->psm_operation);

      sm->psuite_status = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->psuite_status);

      sm->psecureTime_high = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->psecureTime_high);

      sm->psecureTime_low = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->psecureTime_low);

      sm->ptime_adjust = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->ptime_adjust);

      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_GETLOGREPORT.
 * easy to operate.
 */
zint32_t
mmap_sm_getlogreport (MMAP_SM_GETLOGREPORT *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pstartTime_high = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pstartTime_high);
      sm->pstartTime_low = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pstartTime_low);

      sm->pendTime_high = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pendTime_high);
      sm->pendTime_low = (zuint32_t *) (buffer + offset);
      offset += sizeof(*sm->pendTime_low);

      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pret_code);

      sm->plastLogTime_high = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->plastLogTime_high);
      sm->plastLogTime_low = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->plastLogTime_low);

      sm->pbuffersize = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pbuffersize);

      sm->pbuffer = (zuint8_t*) (buffer + offset);

      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_INITIATEMARRIAGE.
 * easy to operate.
 */
zint32_t
mmap_sm_initiatemarriage (MMAP_SM_INITIATEMARRIAGE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pauthId_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pauthId_len);

      sm->pauthId = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_SERVICEDOORTAMPERTERMINATION.
 * easy to operate.
 */
zint32_t
mmap_sm_servicedoortampertermination (MMAP_SM_SERVICEDOORTAMPERTERMINATION *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pauthId_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pauthId_len);

      sm->pauthId = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_GETKEYMAP.
 * easy to operate.
 */
zint32_t
mmap_sm_getkeymap (MMAP_SM_GETKEYMAP *sm, zuint8_t *buffer, zuint32_t direction)
{
  return 0;
}

/**
 * memory map plain buffer to MMAP_SM_ADDCERTIFICATE.
 * easy to operate.
 */
zint32_t
mmap_sm_addcertificate (MMAP_SM_ADDCERTIFICATE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pcert_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pcert_len);

      sm->pcert = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_ADDCERTIFICATE.
 * easy to operate.
 */
zint32_t
mmap_sm_useprivatekey (MMAP_SM_USEPRIVATEKEY *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pkey_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pkey_len);

      sm->pkey = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * memory map plain buffer to MMAP_SM_ZEROIZE.
 * easy to operate.
 */
zint32_t
mmap_sm_zeroize (MMAP_SM_ZEROIZE *sm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (sm == NULL || buffer == NULL)
    {
      ZPrintError("invalid parameters!\n");
      return -1;
    }

  offset = 0x0;
  sm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*sm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      sm->pauthId_len = (zuint32_t*) (buffer + offset);
      offset += sizeof(*sm->pauthId_len);

      sm->pauthId = (zuint8_t*) (buffer + offset);
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      sm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      ZPrintError("invalid direction setting!\n");
      return -1;
    }
  return 0;
}
/**
 * Play control.
 * Modified by zhangshaoyan at November 21,2014.
 * Note:
 * Move Play mode control from SDK to IMB server.
 */
/**
 * Start.
 */
zint32_t
mmap_play_mode_start (MMAP_PLAY_MODE_START *pms, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (pms == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  offset = 0x0;
  pms->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*pms->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      pms->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * Pause.
 */
zint32_t
mmap_play_mode_pause (MMAP_PLAY_MODE_PAUSE *pmp, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (pmp == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  offset = 0x0;
  pmp->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*pmp->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      pmp->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * Forward.
 */
zint32_t
mmap_play_mode_forward (MMAP_PLAY_MODE_FORWARD *pmf, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (pmf == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  offset = 0x0;
  pmf->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*pmf->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      pmf->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * Backward.
 */
zint32_t
mmap_play_mode_backward (MMAP_PLAY_MODE_BACKWARD *pmb, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (pmb == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  offset = 0x0;
  pmb->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*pmb->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      pmb->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * Stop.
 */
zint32_t
mmap_play_mode_stop (MMAP_PLAY_MODE_STOP *pms, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (pms == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  offset = 0x0;
  pms->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*pms->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      break;

      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      pms->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * subtitle related packet types.
 * added by zhangshaoyan at November 2,2014.
 */
zint32_t
mmap_subtitle_file (MMAP_SUBTITLE_FILE *mm, zuint8_t *buffer, zuint32_t direction)
{
  zuint32_t offset;
  if (mm == NULL || buffer == NULL)
    {
      return ZRC_InvalidParameters;
    }

  offset = 0x0;
  mm->pvalid_len = (zuint32_t*) (buffer + offset);
  offset += sizeof(*mm->pvalid_len);

  switch (direction)
    {
    /**
     * SDK --> IMB server.
     */
    case DIRECTION_SDK_TO_IMBSERVER:
      /**
       * Frame Header for DMA transfer.
       */
      /**
       * 4 bytes, must be 'MDSK'.
       */
      mm->pFrameType = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pFrameType);

      /**
       * 4 bytes,frame length.
       */
      mm->pFrameLength = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pFrameLength);

      /**
       * 1 bytes,encrypt or not flag
       */
      mm->pEncryFlag = (zuint8_t*) (buffer + offset);
      offset += sizeof(*mm->pEncryFlag);

      /**
       * 16 bytes,KeyId,all zeros.
       */
      mm->pKeyId = (zuint8_t*) (buffer + offset);
      offset += sizeof(*mm->pKeyId) * UUID_LEN;

      /**
       * Frame Data Section.
       */
      mm->pSyncHead1 = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pSyncHead1);
      mm->pSyncHead2 = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pSyncHead2);
      mm->pSyncHead3 = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pSyncHead3);
      mm->pSyncHead4 = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pSyncHead4);

      mm->pFileType = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pFileType);
      mm->pFileLength = (zuint32_t*) (buffer + offset);
      offset += sizeof(*mm->pFileLength);
      mm->pFileData = (zuint8_t*) (buffer + offset);
      break;
      /**
       * IMB server --> SDK.
       */
    case DIRECTION_IMBSERVER_TO_SDK:
      mm->pret_code = (zuint32_t*) (buffer + offset);
      break;

      /**
       * error direction parameter.
       */
    default:
      return ZRC_InvalidParameters;
    }
  return ZRC_Success;
}
/**
 * the end of file,tagged by zhangshaoyan.
 * at October 21,2014.
 */
