/*@file mvc_pci_drv.h
 *@version 1.0
 *@date 2013/11/30
 *@author zhangshaoyan shell.albert@gmail.com
 *@copyright  oristartech.com
 *@brief IMB PCI Board driver for Linux 2.6
 *date,who,do what
 *2013/11/30,zhangshaoyan,create basic data read&write operation
 *2014/5/19,zhangshaoyan,re-write DMA transfer enabled condition-variable
 *2014/7/22,zhangshaoyan,re-arrange names of variables.
 */
#ifndef __ZSY_IMB_PCI_DRV_H__
#define __ZSY_IMB_PCI_DRV_H__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/dma.h>
#include <linux/timer.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/ioctl.h>

/**
 * define different value to output different level messages.
 */
#define ZDBG_INIT	(0x1<<0) ///<driver initial messages.
#define ZDBG_ISR	(0x1<<1) ///<ISR debug messages.
#define ZDBG_DMA	(0x1<<2) ///<DMA data transfer.
#define ZDBG_PCI	(0x1<<3) ///<PCI operation.
#define ZDBG_VNIC	(0x1<<4) ///<VNIC related.
/**
 * total switch.
 */
#define ZDBG_LEVEL	(0) ///<no debug messages.
//#define ZDBG_LEVEL	(ZDBG_VNIC) ///<no debug messages.
//#define ZDBG_LEVEL	(ZDBG_INIT|ZDBG_ISR|ZDBG_VNIC)

/**
 * PCI driver name.
 * fixed value
 */
#define ZIMB_PCI_DRV_NAME	"imb_pci_device"

/**
 *PCI char device major number.
 *fixed number.
 *for SDK to transfer DMA Video/Audio data.
 */
#define ZIMB_PCI_NUM_MAJOR	2014

/*lspci -k -xxx -vv -d 32ef:cd45*/
/**
 *PCI IDs macro define here,
 *according the VC code from wangbin.
 */
#define ZIMB_VENDOR_ID	0x32ef	//iz
#define ZIMB_DEVICE_ID	0xcd45	//sy

/*DMA buffer*/
#define DMA_TX_BUF_SIZE		(1024*4)
#define DMA_RX_BUF_SIZE		(1024*4)

/**
 * 2KB send & receive buffer size.
 * because FPGA's FIFOs are 2KB only.
 * a packet will be cutted into several parts
 * when its size greater than 2KB. 
 */
#define ZVNIC_TX_BUFSIZE	(1024*2)
#define ZVNIC_RX_BUFSIZE	(1024*2)

/**
 * @brief maximum temporaty buffer size,
 * for once DMA data transfer.
 * Attention here,if size is equal or greater than 2MB,
 * the kernel API dma_alloc_coherent() will failed.
 */
#define DMA_MAX_SIZE	(1024*1024*2-1024*10)	//2MB-0.4MB

/**
 * PCI board resource structure
 */
typedef struct
{
  struct pci_dev *pcidev; ///<pci device
  void *mmio_addr; ///<memory mapped I/O address
  unsigned long mmio_len; ///<memory mapped I/O length

  spinlock_t mmio_lock;
  unsigned char irq;

  /*interrupt counter,incremented by the ISR */
  unsigned int irq_counter;

  unsigned long tx_counter;
  unsigned long rx_counter;

  /*for char dev */
  struct cdev chardev;

  /*for dma tx */
  dma_addr_t dma_tx_physical_addr;
  void *dma_tx_virtual_addr;
  unsigned int dma_tx_channel;
  wait_queue_head_t dma_tx_wait;
  unsigned char dma_tx_busy; ///< busy flag

  spinlock_t ring_lock;
  struct timer_list dma_timer;

  /*for VNIC device */
  /*do not use IRQ,use query method to recv data */

  struct timer_list vnic_timer;
  spinlock_t vnic_lock;
  spinlock_t vnic_lock_rw;

  /**
   * counter for send
   */
  unsigned long vnic_cnt_tx;

  /**
   * for vnic device.
   */
  struct net_device *zvnicdev;
  unsigned char *vnic_rxbuffer;
  unsigned char *vnic_txbuffer;

  /**
   * used to buffer stand alone TCP/IP parts.
   */
  unsigned char *vnic_rxbuffer_big;
  unsigned int vnic_rxbuffer_big_len;

  /**
   * work queue for vnic tx.
   */
  struct work_struct work_vnic_tx;
  struct sk_buff *skb_tx;

  /**
   * wait queue for poll()/select()
   */
  struct fasync_struct *async_queue;

  wait_queue_head_t wq_wr;


  struct workqueue_struct *vnic_workqueue;

  struct work_struct work_vnic_rx;
  unsigned char rx_busy;
  spinlock_t rx_busy_lock;

  /**
   * tasklet for ISR.
   */
  struct tasklet_struct ts_isr;

  unsigned int wait_times;
} ZIMB_PCI_DEV;

extern ZIMB_PCI_DEV *zbrd;

/**
 *@brief compare two value getted from mapped kernel virtual address & pci_read_config_xxx() functions
 *@param void
 *@return RC_OK:success,RC_FAILED:failure
 */
extern int
zpci_mapped_bars_test (void);

/**
 *@brief execute once dma data transfer
 *@param buffer pointer of userspace and its length
 *@return int
 */
extern int
zpci_dma_data_send (const char *buffer, unsigned long len);

/**
 * @brief pci interrupt service routine
 */
extern irqreturn_t
zimb_pci_isr (int irq, void *dev_id);

/**
 * @brief initial function.
 */
extern int
zimb_pci_init (void);
/**
 * @brief de-initial function.
 */
extern void
zimb_pci_exit (void);

extern void
zimb_pci_timer_handler (unsigned long arg);

/**
 * tasklet for ISR
 */
extern void
zimb_pci_isr_tasklet_handler (unsigned long data);

/*ioctl magic number define*/
#define ZIOCTL_MAGIC1           'Z'
#define ZIOCTL_MAGIC2           'S'

/*test for basic read&write*/
#define ZIOCTL_RW_REGS_8        _IOWR(ZIOCTL_MAGIC1,0,char)
#define ZIOCTL_RW_REGS_16       _IOWR(ZIOCTL_MAGIC1,1,short)
#define ZIOCTL_RW_REGS_32       _IOWR(ZIOCTL_MAGIC1,2,int)

/*DRW:direct read & write*/
#define ZIOCTL_DRW_MAGIC	'S'
#define ZIOCTL_DR_REGS		_IOR(ZIOCTL_DRW_MAGIC,0,char)
#define ZIOCTL_DW_REGS		_IOW(ZIOCTL_DRW_MAGIC,1,char)
#define ZIOCTL_DMA_START	_IOW(ZIOCTL_DRW_MAGIC,2,char)
#define ZIOCTL_DMA_STOP		_IOW(ZIOCTL_DRW_MAGIC,3,char)

/**
 *structure for ioctl()
 *basic pci register read&write
 */
typedef struct
{
  unsigned int offset;
  unsigned int value;
} STRU_DRW;

/**
 *under pci,each device has 256 bytes of configuration address space
 * the first 64 bytes are standardized
 */
#define ZPCI_VENDOR_ID			0x00	//16 bits
#define ZPCI_DEVICE_ID			0x02	//16 bits

#define ZPCI_BASE_ADDRESS_0      	0x10	//32 bits
#define ZPCI_BASE_ADDRESS_1      	0x14	//32 bits
#define ZPCI_BASE_ADDRESS_2      	0x18	//32 bits
#define ZPCI_BASE_ADDRESS_3      	0x1c	//32 bits
#define ZPCI_BASE_ADDRESS_4      	0x20	//32 bits
#define ZPCI_BASE_ADDRESS_5      	0x24	//32 bits

#define ZPCI_INTERRUPT_LINE      	0x3c	//8 bits
#define ZPCI_INTERRUPT_PIN       	0x3d	//8 bits
#define ZPCI_MIN_GNT             	0x3e	//8 bits
#define ZPCI_MAX_LAT             	0x3f	//8 bits

/**
 * IMB FPGA registers.
 */
/*DMA related registers*/
#define ZDMA_CTL		0x1000	//DMA control register
#define ZDMA_STS		0x1004	//DMA status register
#define ZDMA_ADDR		0x1008	//DMA data address
#define ZDMA_LEN		0x100C	//DMA data length register
#define ZDMA_INT		0x1010	//DMA interrupt control register
#define ZDMA_INT_DI		0x1014	//(tips:do not use in this version)

/*IP communication registers*/
#define ZPCI2PXA_DATA		0x1200	//PCI to PXA CPU data channel buffer address
#define ZPXA2PCI_DATA		0x1204	//PXA CPU to PCI data channel buffer address
#define ZPCI2PXA_LEN		0x1208	//PCI to PXA data package length register
#define ZPXA2PCI_LEN		0x120C	//PXA to PCI data package length register

/*OPB bus operate registers*/
#define ZOPB_ADDR		0x1400	//OPB bus address
#define ZOPB_WDATA		0x1404	//OPB bus write data
#define ZOPB_ANC_RDATA		0x1408	//OPB bus auxiliary read data
#define ZOPB_RDATA		0x140C	//OPB bus read data
#define ZOPB_STS		0x1410	//OPB bus read status

/*global function registers*/
#define ZRST_CTL		0x1800	//software reset control register
#define ZINT_STS		0x1804	//interrupt status register

/*internal bus operate registers*/
#define ZLBUS_ADDR		0x1C00	//internal bus address
#define ZLBUS_WDATA		0x1C04	//internal bus write data
#define ZLBUS_ANC_RDATA		0x1C08	//internal bus auxiliary read data
#define ZLBUS_RDATA		0x1C0C	//internal bus read data
#define ZLBUS_STS		0x1C10	//internal bus read status

/*****************internal bus registers list***************************/
/*Audio & Video play control registers*/
#define ZPLAY_CTL		0x00	//start to play control
#define ZEND_CTL		0x04	//play end control
#define ZWM_HEADER		0x08	//INTOPIX watermark head parameter
#define ZSOS_HEADER		0x0C	//INTOPIX SOS head parameter (tips:deleted already)
#define ZVIDEO_PARA1		0x10	//Video Source Parameter1
#define ZVIDEO_PARA2		0x14	//Video Source Parameter2
#define ZAUDIO_PARA1		0x18	//Audio Source Parameter1
#define ZAUDIO_PARA2		0x1C	//Audio Source Parameter2
#define ZCONTENT_SEL		0x20	//play content selection
#define ZAV_DELAY_CTL		0x24	//audio video output delay control
#define ZMULTISYNC_CTL		0x28	//multi machine sync control

/*LVDS related registers*/
#define ZP_H_ACTIVE_CTL		0x30	//LVDS module control setting
#define ZP_H_BACK_PORCH_CTL	0x34	//LvDS module control setting
#define ZP_H_FRONT_PORCH_CTL	0x38	//LvDS module control setting
#define ZP_H_TOTAL_CTL		0x3C	//LvDS module control setting
#define ZP_V_ACTIVE_CTL		0x40	//LvDS module control setting
#define ZP_V_BACK_POR_CTL	0x44	//LvDS module control setting
#define ZP_V_FRONT_PORCH_CTL	0x48	//LvDS module control setting
#define ZP_V_TOTAL_CTL		0x4C	//LvDS module control setting

#define ZLVDS_CLK_SWITCH_CTL	0x50

#define ZMPEG_V_TOTAL_CTL	0x54	//MPEG V total size
#define ZMPEG_H_TOTAL_CTL	0x58	//MPEG H total size

#define ZCODESTREAM_KIND_CTL	0x60	//stream type
#define ZAUDIO_CHANNEL_NUM_CTL	0x64	//Audio channel number
#define ZAUDIO_FREQ_CTL		0x68	//Audio frequency

#define ZJPEG_VIDEO_DELAY_NUM_CTL	0x70	//JPEG Video output delay control
#define ZJPEG_AUDIO_DELAY_NUM_CTL	0x74	//JPEG Audio output delay control

#define ZMPEG_VIDEO_DELAY_NUM_CTL	0x78	//MPEG Video output delay control
#define ZMPEG_AUDIO_DELAY_NUM_CTL	0x7C	//MPEG Audio output delay control

#define ZFRAME_IN_DDR_CTL		0x80	//DDR buffer frames control
#define ZLEFT_EYS_WHITE_LINE		0x84	//3D left right eyes cross control
#define ZRIGHT_EYS_WHITE_LINE		0x88	//3D left right eyes cross control

#define ZSLAVE_SYNC_SEL_CTL		0x90	//slave board sync control
#define ZJPEG_OUTPUT0_CTL		0x94	//JPEG output disabled

#define ZDEBUG				0xF0	//test mode register

#endif // __ZSY_IMB_PCI_DRV_H__
/**
 *the end of file,for reading convenience
 *shell.albert@gmail.com
 */
