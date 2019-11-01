/*filename:zsy_vnic_drv.c
 *date:Feb 23,2014
 *ver:1.0
 *author zhangshaoyan.
 *shell.albert@gmail.com
 *function:The driver is used to simulate a virtual NIC (Network Interface)
 *under linux for CentOS communicate with IMX53 through FPGA core.
 */

#include "zvnic_drv.h"
#include "zpci_drv.h"

#define TIMER_500MS	(HZ/2)
#define TIMER_250MS	(HZ/4)
#define TIMER_125MS	(HZ/8)
#define TIMER_50MS	(HZ/20)
#define TIMER_10MS	(HZ/100)
#define TIMER_5MS	(HZ/100/2)

/**
 * default MAC address:19870902
 */
unsigned char zsy_mac[] =
  { 0x01, 0x09, 0x08, 0x07, 0x09, 0x02 };

///**
// * VNIC PCI ISR handler
// */
//irqreturn_t
//zimb_vnic_isr (int irq, void *dev_id)
//{
//  //  ZIMB_PCI_DEV *p = (ZIMB_PCI_DEV *) dev_id;
//  volatile unsigned long flags;
//  ZKDBG ("zimb_vnic_isr():irq=%d\n", irq);
//
//  if (zbrd == NULL)
//    {
//      return IRQ_NONE;
//    }
//
//  //  zbrd->irq_counter++;
//  //  ZKDBG ("irq_counter=%d\n", zbrd->irq_counter);
//
//  /*read ISR status register to
//   *find out which IRQ happened
//   */
//
//  flags = ioread32 (zbrd->mmio_addr + ZINT_STS);
//  ZKDBG ("vnic_isr():INT_STS=0x%lx\n", flags);
//
//  if (flags & (0x1 << 1))     //FIFO_INT_STS
//    {
//
//      /*added by zhangshaoyan at 2014/03/08 morning
//       * here maybe have some errors
//       * if do not judge,receive ok,but the recv data is not right
//       * if judge,may not can hw_read
//       */
//      zvnic_hw_read ();
//      return IRQ_HANDLED;
//    }
//  return IRQ_NONE;
//}

/**
 * poll register to check if vnic has data to be read.
 */
void
vnic_timer_handler (unsigned long arg)
{
  unsigned long flags;
  unsigned char rx_busy_flag;
  unsigned int reg_val;
  /**
   * status register will be checked in timer & ISR.
   */
  if (!spin_is_locked (&zbrd->vnic_lock))
    {
      spin_lock_irqsave (&zbrd->vnic_lock, flags);
      reg_val = ioread32 (zbrd->mmio_addr + ZINT_STS);
//      printk("vnic_timer:0x%x\n",flags);
      if (reg_val & (0x1 << 1))	//FIFO_INT_STS
	{
	zvnic_hw_read();
/*	  spin_lock_irqsave (&zbrd->rx_busy_lock, flags);
	  rx_busy_flag = zbrd->rx_busy;
	  spin_unlock_irqrestore (&zbrd->rx_busy_lock, flags);
	  if (!rx_busy_flag)
            {
	      printk("schedule rx function!,flags=0x%x\n",reg_val);
	      queue_work (zbrd->vnic_workqueue, &zbrd->work_vnic_rx);
	    }else{
                printk("in handling...,schedule next!,flags=0x%x\n",reg_val);
	    }
*/
	}
      spin_unlock_irqrestore (&zbrd->vnic_lock, flags);
    }
  /**
   * HZ is tick numbers of one second.
   * HZ/2=500ms.
   * HZ/4=250ms.
   */
  mod_timer (&zbrd->vnic_timer, jiffies + TIMER_5MS);
  //printk("timer is running!\n");
  return;
}

/**
 * interface:ifcofig zsy_vnic0 up will call this.
 */
int
zvnic_open (struct net_device *dev)
{

  /**
   * check valid of resource.
   */
  if (zbrd == NULL)
    {
      printk ("vnic:zvnic_open():null pointer\n");
      return -1;
    }

  /**
   * remeber device pointer here.
   */
  zbrd->zvnicdev = dev;

  /**
   * start transfer queue
   */
  netif_start_queue (dev);
  netif_carrier_on(dev);

  /**
   * use poll timer to check if vnic has data need to be read.
   */
  init_timer (&zbrd->vnic_timer);
  zbrd->vnic_timer.expires = jiffies + TIMER_250MS;	//250ms
  zbrd->vnic_timer.function = vnic_timer_handler;
  zbrd->vnic_timer.data = 0;
  add_timer (&zbrd->vnic_timer);

  /**
   * print debug message.
   */
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("vnic:zvnic_open() was called!\n");
#endif

  return 0;
}

/**
 * interface:ifconfig zsy_vnic0 down will call this.
 */
int
zvnic_stop (struct net_device *dev)
{
  /**
   * stop transfer queue
   */
  netif_carrier_off(dev);
  netif_stop_queue (dev);

  /**
   * delete poll timer.
   */
  del_timer_sync (&zbrd->vnic_timer);

  /**
   * print debug message.
   */
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("vnic:zvnic_stop() was called!\n");
#endif
  return 0;
}

/**
 *interface:low layer tx function
 *data package transmit function
 *when kernel send data,will call hard_start_transmit function
 *I've already pointed zsy_vnic_start_xmit address with hard_start_transmit
 *be called by the kernel!!!!
 */
int
zvnic_start_xmit (struct sk_buff *skb, struct net_device *dev)
{
  /**
   * stop network queue.
   */
  netif_stop_queue (dev);

  /**
   * save the timestamp.
   */
  zbrd->zvnicdev->trans_start = jiffies;
  /**
   * remember the skb to release memory after send finish.
   */
  zbrd->skb_tx = skb;
  // printk ("ow:%d,", skb->len);
  /**
   * schedule work queue for packets tx.
   */
  //schedule_work (&zbrd->work_vnic_tx);
  /**
   * schedule in myself work queue.
   */
  queue_work (zbrd->vnic_workqueue, &zbrd->work_vnic_tx);

  return NETDEV_TX_OK;
}

/**
 *transfer timeout handler
 */
void
zvnic_tx_timeout (struct net_device *dev)
{
  unsigned long flags;
  /**
   * check valid of parameters.
   */
  if (dev == NULL)
    {
      printk ("zvnic:zvnic_tx_timeout():null pointer!\n");
      return;
    }

  /**
   * warning message.
   */
  printk ("zvnic:transmit timeout at %ld, latency %ld\n", jiffies,
	  jiffies - dev->trans_start);

  /**
   * increase error,
   * we call see it from the result of ifconfig zsy_vnic0.
   */
  dev->stats.tx_errors++;

  /**
   * reset tx busy flag to restart.
   */
  iowrite32 (0, zbrd->mmio_addr + ZPXA2PCI_LEN);


  /**
   * reset rx busy flag to restart.
   */
  spin_lock_irqsave (&zbrd->rx_busy_lock, flags);
  zbrd->rx_busy = 0x0;
  spin_unlock_irqrestore (&zbrd->rx_busy_lock, flags);

  /**
   * wake up interface for next transmit.
   */
  netif_wake_queue (dev);

  return;
}

/**
 * work queue handler for vnic tx.
 * work queue mechanism can sleep when VNIC busy.
 * It has good performance to reduce CPU load.
 */
void
zvnic_tx_work_handler (struct work_struct *work)
{
  int rc;
  unsigned int i;
  unsigned int send_times;
  unsigned int send_step;
  unsigned int send_remain;
  unsigned char total_packets;
  unsigned char current_packet;
  unsigned long flags;
  ZIMB_PCI_DEV *pzbrd = container_of (work, ZIMB_PCI_DEV, work_vnic_tx);

  /**
   * debug information.
   */
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:skb:len=%d\n", pzbrd->skb_tx->len);
#endif

  /**
   * save the timestamp.
   */
  //pzbrd->zvnicdev->trans_start = jiffies;

  ///////////////////////////////////////////////
  /**
   * maximum FIFO size in FPGA is 2KB,
   * so here the data length can't
   * greater than 2KB.
   * if it does,must split data into
   * n parts to send out with n times.
   * here I use 2KB-500B as the upper threshold.
   */
  send_step = (2 * 1024 - 100);
  //send_step=1024;
  send_times = pzbrd->skb_tx->len / send_step;
  send_remain = pzbrd->skb_tx->len % send_step;

#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:send_step:%d\n", send_step);
  printk ("zvnic:send_times:%d\n", send_times);
  printk ("zvnic:send_remain:%d\n", send_remain);
#endif

  /**
   * if skb length is less than 2KB,
   * then send_times is zero
   */
  if (!send_times)
    {
      /**
       * only once send.
       * so here,total_packets=0x1,current_packet=0x1.
       */
      total_packets = 0x1;
      current_packet = 0x1;
      rc = zvnic_hw_write (pzbrd->skb_tx->data, pzbrd->skb_tx->len,
			   total_packets, current_packet);
      /**
       * update network status structure
       * so we can see informations from ifconfig zvnic0 command.
       */
      if (!rc)
	{
	  pzbrd->zvnicdev->stats.tx_packets++;
	  pzbrd->zvnicdev->stats.tx_bytes += pzbrd->skb_tx->len;
	}
      else
	{
	  pzbrd->zvnicdev->stats.tx_dropped++;
	}
      /**
       * release skb after send finish
       * whatever success or fail.
       */
      dev_kfree_skb (pzbrd->skb_tx);

      /**
       * wake up network queue for next transfer.
       */
      netif_wake_queue (pzbrd->zvnicdev);
      return;
    }

  /**
   * when reaches here,it represents more than 2KB data
   * need to be send.
   * Here I send n parts times first,
   * send last remain part second.
   */
  if (send_remain > 0)
    {
      total_packets = send_times + 1;
    }
  else
    {
      total_packets = send_times;
    }
  /**
   * only 8-bit space to hold packet number.
   * so if the number greater than 0xFF,abandon it.
   */
  if (total_packets > 0xFF)
    {
      printk ("zvnic:error:single TCP/IP packet is greater than 0xFF*2KB!\n");
      printk ("zvnic:debug:no ability to handle this big packet!\n");
      return;
    }

  for (i = 0; i < send_times; i++)
    {
      current_packet = i + 1;
      rc = zvnic_hw_write (pzbrd->skb_tx->data + i * send_step, send_step,
			   total_packets, current_packet);
      /**
       * update network status structure
       * so we can see informations from ifconfig zvnic0 command.
       */
      if (!rc)
	{
	  pzbrd->zvnicdev->stats.tx_bytes += send_step;
	}
      else
	{
	  pzbrd->zvnicdev->stats.tx_dropped++;
	}
    }
  /**
   * second:send the last remain data.
   */
  if (send_remain > 0)
    {
      rc = zvnic_hw_write (pzbrd->skb_tx->data + send_times * send_step,
			   send_remain, total_packets, total_packets);
      /**
       * update network status structure
       * so we can see informations from ifconfig zvnic0 command.
       */
      if (!rc)
	{
	  pzbrd->zvnicdev->stats.tx_bytes += send_remain;
	}
      else
	{
	  pzbrd->zvnicdev->stats.tx_dropped++;
	}
    }
  pzbrd->zvnicdev->stats.tx_packets++;
  /**
   * release skb after send finish
   * whatever success or fail.
   */
  dev_kfree_skb (pzbrd->skb_tx);
  /**
   * wake up network queue for next time transfer.
   */
  netif_wake_queue (pzbrd->zvnicdev);
  return;
}

/**
 * character device interface:ioctl
 */
int
zvnic_ioctl (struct net_device *dev, struct ifreq *rq, int cmd)
{
  /*do not support MII physical address */
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:zvnic_ioctl() was called!\n");
#endif
  return 0;
}

/**
 * net interface function
 */
struct net_device_ops zvnic_dev_ops =
  {	///<
    .ndo_open = zvnic_open,	///<
	.ndo_stop = zvnic_stop,	///<
	.ndo_start_xmit = zvnic_start_xmit,	///<
	//      .ndo_set_multicast_list=zvnic_set_rx_mode, ///<
	.ndo_do_ioctl = zvnic_ioctl,	///<
	.ndo_tx_timeout = zvnic_tx_timeout,	///<
	/*do not redefine,call default here */
	.ndo_change_mtu = eth_change_mtu,	///<
	/*do not redefine,call default here */
	.ndo_validate_addr = eth_validate_addr,	///<
	/*do not redefine,call default here */
	.ndo_set_mac_address = eth_mac_addr,	///<
    };

/**
 *device initial function,must be called before register_netdev
 *this will be invoked by register_netdev()
 */
void
zvnic_pre_init (struct net_device *dev)
{
  struct zsy_vnic_priv *priv;

  ether_setup (dev);

  /**
   * operate interface
   */
  dev->netdev_ops = &zvnic_dev_ops;

  /**
   * timeout handler
   */
  dev->watchdog_timeo = HZ * 100;

  //      dev->irq=?;

  /*disable ARP */
  /*enable ARP,if disable,the TCP/IP protocol stack
   *check will failed
   *bug fixed at 22:54 2014/3/9
   *fuck ARP static table
   */
  //dev->flags |= IFF_NOARP;
  //dev->features |= NETIF_F_NO_CSUM;
  /*initial the priv field
   *this encloses the statistics and a few private fields
   */
  priv = netdev_priv (dev);
  memset (priv, 0, sizeof(struct zsy_vnic_priv));

  /*initial spin lock */
  spin_lock_init (&priv->lock);
  spin_lock_init (&zbrd->vnic_lock_rw);

  /**
   * copy default MAC to dev->dev_addr
   */
  memcpy (dev->dev_addr, zsy_mac, sizeof(zsy_mac));

  return;
}

/**
 * @brief init zvnic0
 * default name is zvnic0
 */
int
zvnic_init (void)
{
  /**
   * allocate the net devices
   */
  zbrd->zvnicdev = alloc_netdev (	///<
      sizeof(struct zsy_vnic_priv),	///<
      "zvnic%d",	///<
      zvnic_pre_init);
  if (zbrd->zvnicdev == NULL)
    {
      printk ("zvnic:alloc_netdev() failed!\n");
      return -ENODEV;
    }

  /**
   * register netdevice
   */
  if (register_netdev (zbrd->zvnicdev))
    {
      printk ("zvnic:register_netdev() failed\n");
      return -1;
    }

  spin_lock_init (&zbrd->vnic_lock);
  zbrd->vnic_cnt_tx = 0;

  /**
   * initial work queue for vnic tx.
   */
  INIT_WORK (&zbrd->work_vnic_tx, zvnic_tx_work_handler);

  spin_lock_init (&zbrd->rx_busy_lock);
  zbrd->rx_busy = 0x0;
  INIT_WORK (&zbrd->work_vnic_rx, zvnic_rx_work_handler);

  /**
   * create myself work queue for vnic.
   */
  zbrd->vnic_workqueue = create_singlethread_workqueue ("zvnic_workqueue");
  if (zbrd->vnic_workqueue == NULL)
    {
      printk ("zvnic:create work queue failed!\n");
      return -1;
    }
  zbrd->wait_times=0;
  /*success */
  return 0;
}

void
zvnic_exit (void)
{
  if (zbrd->zvnicdev != NULL)
    {
      unregister_netdev (zbrd->zvnicdev);
      free_netdev (zbrd->zvnicdev);
    }
#if (ZDBG_LEVEL &ZDBG_VNIC)
  printk ("zvnic:zvnic_exit() was called()!");
#endif
  return;
}

/**
 *virtual network interface
 *hardware media layer 
 *write function
 */
int
zvnic_hw_write (unsigned char *buffer, unsigned long len,
		unsigned char total_packets, unsigned char current_packet)
{
  unsigned long i;
  unsigned long flags;

  volatile unsigned int *pbuffer_int;
  volatile unsigned char added_bytes = 0;
  volatile unsigned int send_len;
  volatile unsigned int regval;
  /**
   * check valid of parameters.
   */
  if (zbrd == NULL || buffer == NULL || len <= 0)
    {
      printk ("zvnic:zvnic_hw_write():invalid parameters!\n");
      return -1;
    }

  /**
   * only one process can write hardware at once time.
   */

  /*step:1
   *query PCI2CPU data buffer empty flag in status register
   *if it 1,then can write data
   */
  /*20140306 night
   *must not query BIT2
   *this will cause system down when execute ifconfig zsy_vnic0 x86ip
   *remove this everything work ok
   */
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:waiting for register PCI2ARM [1]==1...[%ld]\n",
      zbrd->vnic_cnt_tx++);
#endif

//  printk("zvnic_write:wait for PCI2ARM[1]==1\n");
  zbrd->wait_times=0;
  while (1)
    {
      spin_lock_irqsave (&zbrd->vnic_lock_rw, flags);
      mb();
      regval = ioread32 (zbrd->mmio_addr + ZINT_STS);
//      printk("regvalue:0x%x,wait_times=%d\n",flags,zbrd->wait_times++);
      /**
       * wait PCI2ARM==1 empty.
       */
      if (regval& (0x1 << 2))
	{
#if (ZDBG_LEVEL & ZDBG_VNIC)
	  printk ("zvnic:PCI2ARM BIT==1,begin to write\n");
#endif
	  break;
	}
      /**
       * retry after 10ms.
       */
      spin_unlock_irqrestore (&zbrd->vnic_lock_rw, flags);
  //    schedule ();
      //mdelay(10);
    }

  /*step2:
   *write data to PCI2CPU_DATA
   */
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic_hw_write:original len:%ld\n", len);
#endif
  send_len = len;
  /**
   * aligned by 4 bytes.
   */
  if ((len % sizeof(int)) != 0)
    {
      added_bytes = sizeof(int) - (len % sizeof(int));
      send_len += added_bytes;
    }
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:added len:%d\n", added_bytes);
  printk ("zvnic:final len:%ld\n", send_len);
#endif
  /**
   * add one 32-bit data to remember how many zero bytes was added.
   */
  send_len += sizeof(int);
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:send total len:%ld\n", send_len);
#endif
//  printk ("nw:%d,", send_len);
  /**
   *check length
   *cannot great than 2K bytes
   */
  if (send_len > (ZVNIC_TX_BUFSIZE))
    {
      printk ("$$$$ ERROR:zvnic:send data greater than 2KB!\n");
      spin_unlock_irqrestore (&zbrd->vnic_lock_rw, flags);
      return -1;
    }

  /**
   * copy data.
   */
  memset (zbrd->vnic_txbuffer, 0, ZVNIC_TX_BUFSIZE);
  memcpy (zbrd->vnic_txbuffer, buffer, len);
  /**
   * use the last byte to remember how many zero bytes was added.
   */
  zbrd->vnic_txbuffer[send_len - 1] = added_bytes;
  zbrd->vnic_txbuffer[send_len - 2] = total_packets;
  zbrd->vnic_txbuffer[send_len - 3] = current_packet;
#if (ZDBG_LEVEL &ZDBG_VNIC)
  printk ("send:added_bytes=%d,total_packets=%d,current_packet=%d\n",
      added_bytes, total_packets, current_packet);
#endif
  /**
   * operate in 32-bit unit.
   */
  pbuffer_int = (unsigned int *) zbrd->vnic_txbuffer;

  /**
   * write data to PCI register.
   */
  for (i = 0; i < (send_len / sizeof(int)); i++)
    {
      iowrite32 (*(pbuffer_int + i), zbrd->mmio_addr + ZPCI2PXA_DATA);
      mb();
      /**
       * print out for debug.
       */
#if (ZDBG_LEVEL & ZDBG_VNIC)
      /*      if (i >= 0 && i <= 10)
       {
       printk ("zvnic:%ldth := 0x%x\n", i, *(pbuffer_int + i));
       }
       */
#endif
    }

  pbuffer_int = NULL;

  /**
   *step3:
   *write length to PCI2CPU_LEN
   */
  iowrite32 (send_len, zbrd->mmio_addr + ZPCI2PXA_LEN);
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:write len(aligned by 4 bytes):%ld finish!\n", send_len);
#endif
  mb();
  /*step4:
   *FPGA generate INT to tell IMX53
   */
  spin_unlock_irqrestore (&zbrd->vnic_lock_rw, flags);
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:zvnic_hw_write() finish!\n");
#endif
  return 0;
}

/**
 *virtual network interface
 *hardware media layer
 *read function
 */
int
zvnic_hw_read (void)
{
  unsigned long flags, i;
  volatile unsigned int data_len;

  struct sk_buff *skb;

  volatile unsigned int *pbuffer_int;
  volatile unsigned char added_bytes;
  volatile unsigned int realdata_len;
  unsigned char total_packets;
  unsigned char current_packet;
  volatile unsigned int regval;
  int rc;
  spin_lock_irqsave (&zbrd->vnic_lock_rw, flags);

  /**
   *step:1
   *query CPU2PCI data buffer not empty flag
   */
  regval = ioread32 (zbrd->mmio_addr + ZINT_STS);
  mb();
  /**
   *step:2
   *read CPU2PCI_LEN to get data length
   */
  data_len = ioread32 (zbrd->mmio_addr + ZPXA2PCI_LEN);
  // printk ("r:%d,", data_len);
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:zvnic_hw_read()len:%ld bytes.\n", data_len);
#endif
  if (data_len <= 0)
    {
      printk ("zvnic:zero length,invalid data!\n");
      goto clear_irq;
    }
  /**
   * check length .
   */
  if (data_len > (ZVNIC_RX_BUFSIZE))
    {
      printk ("$$$$ ERROR:hw_read length greater than 2KB!\n");
      spin_unlock_irqrestore (&zbrd->vnic_lock_rw, flags);
      return -1;
    }

  /**
   *step:3
   *read data back
   */
  memset (zbrd->vnic_rxbuffer, 0, ZVNIC_RX_BUFSIZE);
  /**
   * data_len is in byte unit,
   * here it should be /4(/sizeof(int) to get in 32-bit unit.
   */
  pbuffer_int = (unsigned int *) zbrd->vnic_rxbuffer;
  for (i = 0; i < (data_len / sizeof(int)); i++)
    {
      *(pbuffer_int + i) = ioread32 (zbrd->mmio_addr + ZPXA2PCI_DATA);
      /**
       * print out for debug.
       */
#if (ZDBG_LEVEL & ZDBG_VNIC)
      /*
       if (i >= 0 && i <= 10)
       {
       printk ("zvnic_hw_read():%ldth : 0x%x\n", i, *(pbuffer_int + i));
       }
       */
#endif
    }

#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:last byte(how many zero bytes was added:%d\n",
      zbrd->vnic_rxbuffer[data_len - 1]);
#endif

  /*the packet has been retrieved form the transmission media
   *build an skb around it,so upper layers can handle it
   */
  added_bytes = (unsigned char) zbrd->vnic_rxbuffer[data_len - 1];
  realdata_len = data_len - sizeof(int) - added_bytes;
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:added_bytes:%d\n", added_bytes);
  printk ("zvnic:added bytes takes 4 bytes\n");
  printk ("zvnic:realdata_len:%ld\n", realdata_len);
#endif

  /**
   * store it in big rx buffer,wait for next parts.
   */
  memcpy (zbrd->vnic_rxbuffer_big + zbrd->vnic_rxbuffer_big_len,
	  zbrd->vnic_rxbuffer, realdata_len);
  zbrd->vnic_rxbuffer_big_len += realdata_len;

  total_packets = (unsigned char) zbrd->vnic_rxbuffer[data_len - 2];
  current_packet = (unsigned char) zbrd->vnic_rxbuffer[data_len - 3];

#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("recv:added_bytes=%d,total_packets=%d,current_packet=%d\n",
      added_bytes, total_packets, current_packet);
#endif
  if (current_packet == total_packets)
    {
      /**
       * received a complete TCP/IP packet,pull it to TCP/IP protocol.
       */
      skb = dev_alloc_skb (zbrd->vnic_rxbuffer_big_len + 2);
      if (skb == NULL)
	{
	  printk ("zvnic:rx:low memory-package dropped\n");
	  zbrd->zvnicdev->stats.rx_dropped++;
	  goto clear_irq;
	}
      skb_reserve (skb, 2);

      memcpy (skb_put (skb, zbrd->vnic_rxbuffer_big_len),
	      zbrd->vnic_rxbuffer_big, zbrd->vnic_rxbuffer_big_len);
      /**
       * write metadata,and then pass to the receive level
       */
      skb->dev = zbrd->zvnicdev;
      skb->protocol = eth_type_trans (skb, zbrd->zvnicdev);
      //  ZKDBG ("protocol:0x%x\n", skb->protocol);
      skb->ip_summed = CHECKSUM_UNNECESSARY; /*do not check it */


      /*tell high level here!!!! */
      rc = netif_rx_ni(skb);	//old interface
#if (ZDBG_LEVEL & ZDBG_VNIC)
	  printk ("zvnic:netif_rx(),rc=%d\n", rc);
#endif
	zbrd->zvnicdev->last_rx=jiffies;

      /**
       * increase rx status fields.
       */
      zbrd->zvnicdev->stats.rx_packets++;
      zbrd->zvnicdev->stats.rx_bytes += zbrd->vnic_rxbuffer_big_len;

      /**
       * reset big buffer for next TCP/IP packet.
       */
      zbrd->vnic_rxbuffer_big_len = 0;
    }

  /**
   *step:4
   *write 0 to clear IRQ flag
   */
  clear_irq:			///< label
  iowrite32 (0, zbrd->mmio_addr + ZPXA2PCI_LEN);
#if (ZDBG_LEVEL & ZDBG_VNIC)
  printk ("zvnic:write 0 to CPU2PCI_LEN to clear INT\n");
#endif
  pbuffer_int = NULL;

  spin_unlock_irqrestore (&zbrd->vnic_lock_rw, flags);
  return 0;
}

void
zvnic_rx_work_handler (struct work_struct* work)
{
  unsigned long flags;
  ZIMB_PCI_DEV *pzbrd = container_of (work, ZIMB_PCI_DEV, work_vnic_tx);
  /**
   * set busy flag.
   */
  spin_lock_irqsave (&pzbrd->rx_busy_lock, flags);
  pzbrd->rx_busy = 0x1;
  spin_unlock_irqrestore (&pzbrd->rx_busy_lock, flags);

  /**
   * read
   */
  zvnic_hw_read ();

  /**
   * reset busy flag.
   */
  spin_lock_irqsave (&pzbrd->rx_busy_lock, flags);
  pzbrd->rx_busy = 0x0;
  spin_unlock_irqrestore (&pzbrd->rx_busy_lock, flags);
  return;
}
/*the end of file,for reading convenience
 *shell.albert@gmail.com
 */
