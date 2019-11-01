/*filename:zsy_vnic_drv.h
 *date:Feb 23,2014
 *ver:1.0
 *author zhangshaoyan.
 *function:The driver is used to simulate a virtual NIC (Network Interface)
 *under linux for CentOS communicate with IMX53 through FPGA core.
 */
#ifndef __ZSY_VNIC_H__
#define __ZSY_VNIC_H__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/skbuff.h>
#include <linux/interrupt.h>

/**
 * transmit timeout constant
 */
#define ZVNIC_TX_TIMEOUT		(HZ*5)

/**
 *structure is private for each device
 *used to pass packets in and out
 */
struct zsy_vnic_priv
{
  struct net_device_stats stats;
  int status;

  spinlock_t lock;
};

/**
 *structure for one packet
 */
struct zsy_vnic_packet
{
  unsigned long packet_len;
  unsigned char *packet_data;
};

/**
 *interface:ifcofig zsy_vnic0 up will call this.
 */
extern int
zvnic_open (struct net_device *dev);

/**
 * interface:stop nic
 */
extern int
zvnic_stop (struct net_device *dev);

/**
 *interface:low layer tx function
 *data package transmit function
 *when kernel send data,will call hard_start_transmit function
 *I've already pointed zsy_vnic_start_xmit address with hard_start_transmit
 *be called by the kernel!!!!
 */
extern int
zvnic_start_xmit (struct sk_buff *skb, struct net_device *dev);

/**
 *transfer timeout handler
 */
extern void
zvnic_tx_timeout (struct net_device *dev);

/**
 *interface:ioctl().
 */
extern int
zvnic_ioctl (struct net_device *dev, struct ifreq *rq, int cmd);

/**
 * net interface function
 */
extern struct net_device_ops zsy_vnic_dev_ops;

/**
 *device initial function,must be called before register_netdev
 *this will be invoked by register_netdev()
 */
extern void
zvnic_pre_init (struct net_device *dev);

/**
 * VNIC initial&de-init functions
 */
extern int
zvnic_init (void);
extern void
zvnic_exit (void);

/**
 *virtual network interface hardware media layer write function
 */
extern int
zvnic_hw_write (unsigned char *buffer, unsigned long len,
		unsigned char total_packets, unsigned char current_packet);

/**
 *virtual network interface hardware media layer read function
 *pass it to upper layer
 */
extern int
zvnic_hw_read (void);

//extern irqreturn_t zimb_vnic_isr (int irq, void *dev_id);

/**
 * use timer to poll
 * to check if FPGA has vnic data need to be read out.
 */
extern void
vnic_timer_handler (unsigned long arg);

/**
 * work queue handler for vnic tx.
 */
void
zvnic_tx_work_handler (struct work_struct *work);
void
zvnic_rx_work_handler (struct work_struct* work);
#endif //__ZSY_VNIC_H__
/*the end of file,for reading convenience
 *shell.albert@gmail.com
 */
