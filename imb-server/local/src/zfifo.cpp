/**
 * @file zfifo.c
 * @date May 30,2014
 * @author zhangshaoyan@oristartech.com
 * @brief define FIFO related codes
 */

#include <zfifo.h>
#include <zconfig.h>

/**
 * @brief allocate a FIFO in memory,return its base address
 */
zint32_t
zfifo_allocate (ZFIFO **fifo, zuint32_t size)
{
  zuint32_t index;
  zuint32_t fifo_pkt_size;
  char buffer[128];

  /**
   * print function name for debug.
   */
#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("info:zfifo_allocate()\n");
#endif

  //check parameter
  if (size <= 0)
    {
      printf ("error:fifo:wrong parameter size\n");
      *fifo = NULL;
      return -1;
    }

  (*fifo) = (ZFIFO*) malloc (sizeof(ZFIFO));
  if ((*fifo) == NULL)
    {
      printf ("error:malloc ZFIFO failed:%s\n", strerror (errno));
      goto rollback;
    }

  //initial
  (*fifo)->size = size;
  (*fifo)->free = size;
  (*fifo)->rd_pos = 0;
  (*fifo)->wr_pos = 0;

#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("info:fifo=%p\n", (*fifo));
#endif

  //allocate ZPKT
  (*fifo)->pkt = (ZPKT*) malloc (sizeof(ZPKT) * size);
  if ((*fifo)->pkt == NULL)
    {
      printf ("error:malloc ZPKT failed:%s\n", strerror (errno));
      goto rollback;
    }
#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("info:fifo->pkt=%p\n", (*fifo)->pkt);
#endif

  //read configure file to get ZPKT_BUF_SIZE
  if (zconfig_get_key (KEYNAME_FIFO_PKT_BUFSIZE, buffer) == 0)
    {
      //success
      if ((fifo_pkt_size = strtoul (buffer, NULL, 10)) == 0)
	{
	  //failed
	  fifo_pkt_size = DEFAULT_FIFO_PKT_BUFSIZE;
	}
    }
  else
    {
      //failed
      fifo_pkt_size = DEFAULT_FIFO_PKT_BUFSIZE;

    }

#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("info:zconfig:FIFO_PKT_BUFSIZE:%d\n", fifo_pkt_size);
#endif

  //allocate each ZPKT
  for (index = 0; index < size; index++)
    {
#if (ZDBG_LEVEL &ZDBG_FIFO)
      printf("info:allocate %d ZPKT:", index);
#endif
      ((*fifo)->pkt + index)->type = 0;
      ((*fifo)->pkt + index)->len = 0;
      ((*fifo)->pkt + index)->data = (zuint8_t*) malloc (fifo_pkt_size);
      if (((*fifo)->pkt + index)->data == NULL)
	{
#if (ZDBG_LEVEL &ZDBG_FIFO)
	  printf("failed:%s\n", strerror(errno));
#endif
	  goto rollback;
	}
      else
	{
#if (ZDBG_LEVEL &ZDBG_FIFO)
	  printf("success=%p\n", ((*fifo)->pkt + index)->data);
#endif
	}
    }

  //success
  return 0;

  /**
   * failed rollback affairs.
   */
  rollback: ///<
  printf ("error:rollback...\n");

  /**
   * fifo failed.
   */
  if ((*fifo) == NULL)
    {
      return -1;
    }

  /**
   * fifo->pkt failed.
   */
  if ((*fifo)->pkt == NULL)
    {
      free (*fifo);
      *fifo = NULL;
      return -1;
    }

  /**
   * (fifo->pkt+index)->data failed.
   */
  for (index = 0; index < size; index++)
    {
      if (((*fifo)->pkt + index)->data != NULL)
	{
	  free (((*fifo)->pkt + index)->data);
	  ((*fifo)->pkt + index)->data = NULL;
	}
    }
  free ((*fifo)->pkt);
  (*fifo)->pkt = NULL;
  free (*fifo);
  *fifo = NULL;
  return -1;
}

/**
 * @brief destroy a FIFO,release its memory
 */
void
zfifo_destroy (ZFIFO**fifo)
{
  zuint32_t index;

  /**
   * check parameter.
   */
  if ((*fifo) == NULL)
    {
      //do not need free
      return;
    }

  if ((*fifo)->pkt == NULL)
    {
      free (*fifo);
      *fifo = NULL;
      return;
    }

  /**
   * release package in FIFO.
   */
  for (index = 0; index < (*fifo)->size; index++)
    {
      if (((*fifo)->pkt + index)->data != NULL)
	{
	  free (((*fifo)->pkt + index)->data);
	  ((*fifo)->pkt + index)->data = NULL;
	}
    }
  /**
   * release fifo->pkt.
   */
  free ((*fifo)->pkt);
  (*fifo)->pkt = NULL;
  free (*fifo);
  *fifo = NULL;
  return;
}

/**
 * @brief put a packet to FIFO
 */
zint32_t
zfifo_put_element (ZFIFO *fifo, const ZPKT *pkt)
{
  if (fifo == NULL || pkt == NULL)
    {
      printf ("error:null pointer\n");
      return -1;
    }

  if (fifo->free == 0)
    {
      printf ("error:no available space in ZFIFO\n");
      return -1;
    }

  /**
   * check length.
   */
  if (pkt->len > ZPKT_BUF_SIZE)
    {
      printf ("error:len is too bigger,abandon this package\n");
      return -1;
    }
  else if (pkt->len <= 0)
    {
      printf ("error:len is negative or zero\n");
      return -1;
    }

  //ZDBG("put element:fifo=%p,fifo->pkt=%p\n", fifo, fifo->pkt);
  /**
   * copy data.
   */
  (fifo->pkt[fifo->wr_pos]).type = pkt->type;
#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("put element:type=0x%02x,%d\n", (fifo->pkt[fifo->wr_pos]).type,
      pkt->type);
#endif

  (fifo->pkt[fifo->wr_pos]).len = pkt->len;
#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("put element:len=%d,%d\n", (fifo->pkt[fifo->wr_pos]).len, pkt->len);
#endif

  memcpy ((fifo->pkt[fifo->wr_pos]).data, pkt->data, pkt->len);
  fifo->wr_pos++;

  /**
   * generate loop FIFO.
   */
  if (fifo->wr_pos == fifo->size)
    {
      fifo->wr_pos = 0;
    }

  /**
   * decrease available space.
   */
  if (fifo->free > 0)
    {
      fifo->free--;
    }

  return 0;
}

/**
 * @brief get free position
 */
ZPKT *
zfifo_get_free_position (ZFIFO *fifo)
{
  if (fifo == NULL)
    {
      return NULL;
    }
  if (fifo->free == 0)
    {
      printf ("no available space in ZFIFO\n");
      return NULL;
    }
  /**
   * check pkt pointer.
   */
  if (fifo->pkt == NULL)
    {
      return NULL;
    }
  return &fifo->pkt[fifo->wr_pos];
}

zint32_t
zfifo_dec_free_number (ZFIFO *fifo)
{
  if (fifo == NULL)
    {
      return -1;
    }

  fifo->wr_pos++;

  /**
   * generate loop FIFO.
   */
  if (fifo->wr_pos == fifo->size)
    {
      fifo->wr_pos = 0;
    }

  /**
   * decrease available space.
   */
  if (fifo->free > 0)
    {
      fifo->free--;
    }
  return 0;
}
/**
 * @brief get a packet from FIFO
 */
zint32_t
zfifo_get_element (ZFIFO *fifo, ZPKT *pkt)
{
  /**
   * check pointer.
   */
  if (fifo == NULL || pkt == NULL)
    {
      printf ("error:null pointer\n");
      return -1;
    }

  /**
   * no data in fifo.
   */
  if (fifo->free == fifo->size)
    {
      return -1;
    }

  /**
   * check buffer.
   */
  if (pkt->data == NULL)
    {
      printf ("error:no space to store element\n");
      return -1;
    }

//  ZDBG("get element:fifo=%p,fifo->pkt=%p\n", fifo, fifo->pkt);
  /**
   * copy data out.
   */
  pkt->type = (fifo->pkt[fifo->rd_pos]).type;
#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("get element:type=0x%02x,%d\n", (fifo->pkt + fifo->rd_pos)->type,
      pkt->type);
#endif

  pkt->len = (fifo->pkt[fifo->rd_pos]).len;
#if (ZDBG_LEVEL &ZDBG_FIFO)
  printf("get element:len=%d,%d\n", (fifo->pkt + fifo->rd_pos)->len, pkt->len);
#endif

  memcpy (pkt->data, (fifo->pkt[fifo->rd_pos]).data,
	  (fifo->pkt[fifo->rd_pos]).len);
  fifo->rd_pos++;

  /**
   * loop FIFO.
   */
  if (fifo->rd_pos == fifo->size)
    {
      fifo->rd_pos = 0;
    }

  /**
   * increase valid data.
   */
  fifo->free++;

  return 0;
}

/**
 * @brief get busy position
 */
ZPKT *
zfifo_get_busy_position (ZFIFO *fifo)
{
  /**
   * check parameter.
   */
  if (fifo == NULL)
    {
      return NULL;
    }
  /**
   * no data in fifo.
   */
  if (fifo->free == fifo->size)
    {
      return NULL;
    }
  /**
   * check pkt pointer.
   */
  if (fifo->pkt == NULL)
    {
      return NULL;
    }
  return &fifo->pkt[fifo->rd_pos];
}

zint32_t
zfifo_inc_free_number (ZFIFO *fifo)
{
  if (fifo == NULL)
    {
      printf ("error:null pointer!\n");
      return -1;
    }

  fifo->rd_pos++;

  /**
   * loop FIFO.
   */
  if (fifo->rd_pos == fifo->size)
    {
      fifo->rd_pos = 0;
    }

  /**
   * increase valid data.
   */
  fifo->free++;

  return 0;
}

/**
 * @brief return the free number in FIFO
 */
zint32_t
zfifo_get_free (const ZFIFO*fifo)
{
  if (fifo == NULL)
    {
      printf ("error:%s:null pointer\n", __FUNCTION__);
      return -1;
    }

//  //for debug
//  return 1;

  return fifo->free;
}

/**
 * @brief return the total size in FIFO
 */
zint32_t
zfifo_get_size (const ZFIFO *fifo)
{
  if (fifo == NULL)
    {
      printf ("error:%s:null pointer!\n", __FUNCTION__);
      return -1;
    }
  return fifo->size;
}

/**
 * @brief return the valid number in FIFO
 */
zint32_t
zfifo_get_total (const ZFIFO *fifo)
{
  if (fifo == NULL)
    {
      printf ("error:%s:null pointer\n", __FUNCTION__);
      return -1;
    }

  //for debug
//  return 1;

  return fifo->size - fifo->free;
}
/**
 * the end of file,tagged by ZSY
 */
