/*filename:zsy_imb_pci_drv.c
 *version:1.0
 *date:2013/11/30
 *author:zhangshaoyan (shell.albert@gmail.com)
 *Copyright(C) oristartech.com
 *description:IMB PCI Board driver for Linux 2.6
 */

#include "zpci_drv.h"
#include "zvnic_drv.h"

#define DMA_BUF_SIZE	(2*1024*1024-512)

/**
 *PCI interrupt service routine.
 */
irqreturn_t
zimb_pci_isr (int irq, void *dev_id)
{
  /**
   * get global resource structure.
   */
/*
  ZIMB_PCI_DEV *pres = (ZIMB_PCI_DEV *) (dev_id);
  if (pres == NULL)
    {
      printk ("error:zimb_pci_isr_tasklet_handler():null pinter!\n");
      return IRQ_NONE;
    }
*/
#if (ZDBG_LEVEL&ZDBG_ISR)
  printk ("zimb_pci_isr(),irq=%d\n", irq);
#endif
  /**
   * disable irq now,
   * it will be enabled after process finish.
   */
  disable_irq_nosync (irq);

  /**
   * schedule ISR tasklet.
   * do not take up more time in ISR context.
   */
  //tasklet_schedule (&pres->ts_isr);
  /**
 * if schedule with pres the tasklet will not run.
 * so schedule it with zbrd global resource
 */
#if (ZDBG_LEVEL&ZDBG_ISR)
  printk("tasklet_schedule()...\n");
#endif
//  printk ("zimb_pci_isr(),irq=%d\n", irq);
  tasklet_schedule (&zbrd->ts_isr);
#if (ZDBG_LEVEL&ZDBG_ISR)
  printk("tasklet_schedule() ok!\n");
#endif

  return IRQ_HANDLED;
}

/**
 * when DMA transfer timeout will call this function.
 */
void
zimb_pci_timer_handler (unsigned long arg)
{
  unsigned long flags;
  /**
   * read INT status register to detect which IRQ source happened.
   */
  flags = ioread32 (zbrd->mmio_addr + ZINT_STS);
#if (ZDBG_LEVEL&ZDBG_ISR)
  printk ("INT_STS=0x%lx\n", flags);
#endif
  if (flags & (0x1)) /*DMA_INT_STS */
    {
      /**
       * write 1 to clear FPGA DMA IRQ
       * read-modify-write.
       */
      flags = ioread32 (zbrd->mmio_addr + ZDMA_INT);
      flags |= 0x1;
      iowrite32 (flags, zbrd->mmio_addr + ZDMA_INT);

#if (ZDBG_LEVEL&ZDBG_ISR)
      printk ("clear FPGA DMA IRQ\n");
      printk ("wake up\n");
#endif
      /*wakeup write() */
      zbrd->dma_tx_busy = 0x1;
      wake_up_interruptible (&zbrd->dma_tx_wait);
    }
  /**
   * print debug message.
   */
#if (ZDBG_LEVEL|ZDBG_DMA)
  printk ("dma:dma timeout fucntion called.\n");
#endif
  return;
}

/**
 * @brief open device file system call interface
 * here restrict only one process can be opened at one time
 * use spin_lock to protect
 */
static int
zimb_pci_open (struct inode *inode, struct file *file)
{
  unsigned long flags;
  /**
   * write 1 to clear FPGA DMA IRQ
   * read-modify-write.
   */
  flags = ioread32 (zbrd->mmio_addr + ZDMA_INT);
  flags |= 0x1;
  iowrite32 (flags, zbrd->mmio_addr + ZDMA_INT);
  /**
   * print debug message.
   */
#if (ZDBG_LEVEL&ZDBG_PCI)
  printk ("pci:zimb_pci_open() called.\n");
#endif
  return 0;
}

/**
 * read() interface
 * do not implement here
 * all read data transfer from device implemented in ioctl()
 */
static ssize_t
zimb_pci_read (struct file *file, char __user * buf, size_t count,
    loff_t * pos)
  {
    /**
     * do not need do any work here.
     * Just print a debug message.
     */
#if (ZDBG_LEVEL&ZDBG_PCI)
    printk ("pci:zimb_pci_read() ok.\n");
#endif
    return 0;
  }

/**
 * @brief execute DMA data transfer here
 */
static ssize_t
zimb_pci_write (struct file *file, const char __user * buf, size_t count,
    loff_t * pos)
  {
    int ret;
    /**
     * check valid of parameter.
     */
    if (count <= 0)
      {
	printk("dma:zero length DMA data!\n");
	return -1;
      }
    /**
     * call hardware DMA send data function.
     */
    ret= zpci_dma_data_send (buf, count);

#if 0
    /**
     * wake up any writer in wait queue.
     */
    wake_up_interruptible (&zbrd->wq_wr);
    /**
     * signal asynchronous writer.
     */
    if (zbrd->async_queue)
      {
	kill_fasync (&zbrd->async_queue, SIGIO, POLL_OUT);
      }
#endif
    return ret;
  }

/**
 * @brief character device interface.ioctl().
 */
static long
zimb_pci_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
  STRU_DRW drw;
  int rc;

#if (ZDBG_LEVEL&ZDBG_PCI)
  printk ("pci:zimb_pci_ioctl()\n");
#endif

  if (_IOC_TYPE (cmd) != ZIOCTL_DRW_MAGIC)
    {
      printk ("pci:not valid ioctl() command.\n");
      return -1;
    }

  switch (cmd)
    {
    case ZIOCTL_DR_REGS:
      /**
       * read PCI registers.
       */
      rc = copy_from_user (&drw, (STRU_DRW *) arg, sizeof(STRU_DRW));
#if (ZDBG_LEVEL&ZDBG_PCI)
      printk ("pci:copy_from_user(),rc:%d\n", rc);
      printk ("pci:read offset:0x%x\n", drw.offset);
#endif
      /**
       * check offset
       */
      if (drw.offset > zbrd->mmio_len)
	{
	  printk ("pci:error:register offset invalid.\n");
	  return -1;
	}
      /**
       * read register
       */
      drw.value = ioread32 (zbrd->mmio_addr + drw.offset);
      /**
       * copy to user space.
       */
      rc = copy_to_user ((STRU_DRW *) arg, &drw, sizeof(STRU_DRW));
#if (ZDBG_LEVEL&ZDBG_PCI)
      printk("copy_to_user(),rc:%d\n", rc);
#endif

      break;

    case ZIOCTL_DW_REGS:
      /**
       * write PCI registers.
       */
      rc = copy_from_user (&drw, (STRU_DRW *) arg, sizeof(STRU_DRW));
#if (ZDBG_LEVEL&ZDBG_PCI)
      printk ("pci:copy_from_user(),rc:%d\n", rc);
      printk ("pci:write offset:0x%x ", drw.offset);
      printk ("pci:with value:0x%x\n", drw.value);
      printk ("pci:mmio_len:%lx\n", zbrd->mmio_len);
#endif
      /**
       * check valid of offset.
       */
      if (drw.offset > zbrd->mmio_len)
	{
	  printk ("pci:error:register offset invalid.\n");
	  return -1;
	}
      /**
       * write register.
       */
      iowrite32 (drw.value, zbrd->mmio_addr + drw.offset);
      /**
       * copy to user space.
       */
      rc = copy_to_user ((STRU_DRW *) arg, &drw, sizeof(STRU_DRW));
#if (ZDBG_LEVEL&ZDBG_PCI)
      printk ("pci:copy_to_user(),rc:%d\n", rc);
#endif
      break;
    default:
      printk ("pci:unsupported ioctl() command!\n");
      return -1;
      break;
    }
#if 0
  /**
   * wake up any writer in wait queue.
   */
  wake_up_interruptible (&zbrd->wq_wr);
  /**
   * signal asynchronous writer.
   */
  if (zbrd->async_queue)
    {
      kill_fasync (&zbrd->async_queue, SIGIO, POLL_OUT);
    }
#endif
  return 0;
}

/**
 * @brief poll()/select() asynchonous interface.
 */
static unsigned int
zimb_pci_poll (struct file *filp, poll_table * wait)
{
  unsigned int mask = 0;
  poll_wait (filp, &zbrd->wq_wr, wait);
//mask |= POLLIN | POLLRDNORM; ///<readable
  mask |= POLLOUT | POLLWRNORM;	///<writable
  return mask;
}

static int
zimb_pci_fasync (int fd, struct file *filp, int mode)
{
  return fasync_helper (fd, filp, mode, &zbrd->async_queue);
}

/**
 * @brief character device interface.
 */
static int32_t
zimb_pci_close (struct inode *inode, struct file *file)
{
  /**
   * Do no need to do any jobs here.
   * Just print a debug message.
   */
#if (ZDBG_LEVEL&ZDBG_PCI)
  printk ("pci:zimb_pci_close() ok.\n");
#endif
  return 0;
}

/**
 * character device file operations
 */
static struct file_operations zimb_pci_fops =
  {	///<
    .owner = THIS_MODULE,		///<
	.open = zimb_pci_open,	///<
	.read = zimb_pci_read,	///<
	.write = zimb_pci_write,	///<
	.unlocked_ioctl = zimb_pci_ioctl,	///<
	.poll = zimb_pci_poll,	///<
	.fasync = zimb_pci_fasync,	///<
	.release = zimb_pci_close	///<
    };

/**
 * pci device table define here
 * (VendorID& DeviceID) for supported devices
 */
static const struct pci_device_id zimb_pci_id[] =
  {
  /**
   * manufacturer identifier&device identifier
   */
    { PCI_DEVICE (ZIMB_VENDOR_ID, ZIMB_DEVICE_ID), },
    { 0, }
  /**
   * list terminator,must be have!
   */
  };

/*export to kernel space*/
MODULE_DEVICE_TABLE ( pci, zimb_pci_id);

/**
 *@brief execute once dma data transfer
 *@param void
 *@return void
 */
int
zpci_dma_data_send (const char __user * buffer, unsigned long len)
  {
    volatile int rc = 0;
    volatile unsigned long dma_transfer_size;
    unsigned long flags;
    /**
     * check valid of parameters.
     */
    if (buffer == NULL || len <= 0 || len > DMA_MAX_SIZE - 1)
      {
	printk ("error:zpci_dma_data_send():invaid parameters!\n");
	return -1;
      }

    /**
     * reset busy flag
     */
    zbrd->dma_tx_busy = 0x0;

    /**
     * set DMA parameters.
     */
    set_dma_mode (zbrd->dma_tx_channel, DMA_MODE_WRITE);
    set_dma_addr (zbrd->dma_tx_channel, zbrd->dma_tx_physical_addr);
    set_dma_count (zbrd->dma_tx_channel, len);

    /**
     * copy data from user space to kernel space.
     */
    rc = copy_from_user (zbrd->dma_tx_virtual_addr, buffer, len);
    if (rc)
      {
	printk ("dma:warning length greater than 2KB,truncate it!\n");
	dma_transfer_size = len - rc;
      }
    else
      {
	dma_transfer_size = len;
      }

    /**
     * write DMA physical address.
     */
    iowrite32 (zbrd->dma_tx_physical_addr, zbrd->mmio_addr + ZDMA_ADDR);

    /**
     * write DMA data length.
     */
    iowrite32 (dma_transfer_size, zbrd->mmio_addr + ZDMA_LEN);

    /**
     * enable host DMA operation.
     */
    enable_dma (zbrd->dma_tx_channel);

    /**
     * enable FPGA DMA operation.
     */
    iowrite32 (0x1, zbrd->mmio_addr + ZDMA_CTL);

    /**
     * wait for DMA transfer interrupt occurs
     */
#if (ZDBG_LEVEL&ZDBG_DMA)
    printk ("dma:wait for DMA interrupt....\n");	///<
#endif
 //   printk ("dma:wait for DMA interrupt....\n");	///<

    /* do not use query method to detect DMA transfer finish
     * disabled by zhangshaoyan at January 15,2014
     */
#if 1
    /**
     * use IRQ to detect DMA operation finish.
     */
    rc=wait_event_interruptible (zbrd->dma_tx_wait, zbrd->dma_tx_busy == 0x1);
//    printk("dma finished! rc=%d\n",rc);
#else
    /**
     * use query method to detect DMA operation finish.
     */
    rc = 0x0;
    while (1)
      {
	/**
	 * do not query INT_STS here,it will cause system down!
	 */
	rc = ioread32 (zbrd->mmio_addr + ZINT_STS);
	if (rc & 0x1)
	  {
#if (ZDBG_LEVEL &ZDBG_DMA)
	    printk ("dma:DMA transfer finished!\n");
#endif
	    break;
	  }
	mdelay (10);
      }
    /**
     * read-modify-write.
     */
    rc = ioread32 (zbrd->mmio_addr + ZDMA_INT);
    rc |= 0x1;
    iowrite32 (rc, zbrd->mmio_addr + ZDMA_INT);
#endif

    disable_dma (zbrd->dma_tx_channel);
#if (ZDBG_LEVEL&ZDBG_DMA)
    printk ("dma:DMA transfer finish!\n");
#endif

    return 0;
  }

/**
 * when device&driver matched,
 * this function will be called by kernel automatically.
 * do memory map  here.
 */
static int
zimb_pci_probe (struct pci_dev *dev, const struct pci_device_id *id)
{
  unsigned short value16;
  unsigned int value32;
  int rc;
  unsigned long start, end, length;
  /**
   * check valid of parameters.
   */
  if (dev == NULL)
    {
      printk ("zpci_drv:error at zimb_pci_probe().\n");
      return -EINVAL;
    }

#if (ZDBG_LEVEL&ZDBG_INIT)
  printk ("init:step:probe(),dev=0x%p,id=0x%p,irq=%d\n", dev, id, dev->irq);
#endif

  /**
   * enable PCI device.
   */
  rc = pci_enable_device (dev);
  if (rc)
    {
      printk ("init:can't enable pci device\n");
    }
  pci_set_master (dev);
  pci_set_dma_mask (dev, DMA_BIT_MASK (32));

  /**
   * must enable msi feature.
   */
  pci_enable_msi (dev);

  /**
   * remember the PCI device pointer.
   */
  zbrd->pcidev = dev;

  /**
   * This IRQ is the real IRQ.
   * it is changed by PCI subsystem.
   * remember this IRQ number.
   */
  printk ("init:irq after pci_enable_device():%d\n", dev->irq);
  zbrd->irq = dev->irq;

  /**
   * get start & end resource.
   */
  start = pci_resource_start (dev, 0);
  end = pci_resource_end (dev, 0);
  length = end - start + 1;

  /**
   * request I/O region
   */
  request_region (start, length, ZIMB_PCI_DRV_NAME);

  /**
   * map the device memory or I/O region
   * into kernel virtual address space,
   * from PCI bar0
   */
  zbrd->mmio_addr = ioremap (start, length);
  if (!zbrd->mmio_addr)
    {
      printk ("error:ioremap() failed\n");
      return -1;
    }

  /**
   * remember mapped length.
   */
  zbrd->mmio_len = length;

  /**
   * interrupt_line.
   */
  pci_read_config_byte (zbrd->pcidev, PCI_INTERRUPT_LINE, (char *) &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:INTERRUPT_LINE:%d\n", value32);
#endif

  /**
   * interrupt_pin.
   */
  pci_read_config_byte (zbrd->pcidev, PCI_INTERRUPT_PIN, (char *) &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:INTERRUPT_PIN:%d\n", value32);
#endif

  /*vendor id */
  pci_read_config_word (zbrd->pcidev, ZPCI_VENDOR_ID, &value16);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Vendor ID:%x\n", value16);
#endif

  /*device id */
  pci_read_config_word (zbrd->pcidev, ZPCI_DEVICE_ID, &value16);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Device ID:%x\n", value16);
#endif

  /*bar0 base address */
  pci_read_config_dword (zbrd->pcidev, ZPCI_BASE_ADDRESS_0, &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Bar0 Address:%x\n", value32);
#endif

  /*bar1 base address */
  pci_read_config_dword (zbrd->pcidev, ZPCI_BASE_ADDRESS_1, &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Bar1 Address:%x\n", value32);
#endif

  /*bar2 base address */
  pci_read_config_dword (zbrd->pcidev, ZPCI_BASE_ADDRESS_2, &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Bar2 Address:%x\n", value32);
#endif

  /*bar3 base address */
  pci_read_config_dword (zbrd->pcidev, ZPCI_BASE_ADDRESS_3, &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Bar3 Address:%x\n", value32);
#endif

  /*bar4 base address */
  pci_read_config_dword (zbrd->pcidev, ZPCI_BASE_ADDRESS_4, &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Bar4 Address:%x\n", value32);
#endif

  /*bar5 base address */
  pci_read_config_dword (zbrd->pcidev, ZPCI_BASE_ADDRESS_5, &value32);
#if (ZDBG_LEVEL & ZDBG_INIT)
  printk ("init:Bar5 Address:%x\n", value32);
#endif

  spin_lock_init (&zbrd->mmio_lock);
  init_waitqueue_head (&zbrd->wq_wr);
  /**
   * wait queue for DMA tx.
   */
  init_waitqueue_head (&zbrd->dma_tx_wait);
  zbrd->dma_tx_busy = 0x0;

  /**
   * assume DMA channel number to 0.
   */
  zbrd->dma_tx_channel = 0;

  /**
   * request DMA channel
   */
  if (request_dma (zbrd->dma_tx_channel, ZIMB_PCI_DRV_NAME))
    {
      printk ("zpci_drv:error at request_dma():%d\n", zbrd->dma_tx_channel);
      return -1;
    }
    /**
     * allocate a DMA buffer for transfer.
     */
    zbrd->dma_tx_virtual_addr = dma_alloc_coherent (	///<
	NULL,///<
	DMA_BUF_SIZE,///<
	&zbrd->dma_tx_physical_addr,///<
	GFP_KERNEL);
    if (zbrd->dma_tx_virtual_addr == NULL)
      {
	printk ("zpci_drv:error at dma_alloc_coherent()\n");
	return -1;
      }
  /**
   * tasklet for ISR.
   */
  tasklet_init (&zbrd->ts_isr, zimb_pci_isr_tasklet_handler,
		(unsigned long) zbrd);

  /**
   *success here.
   */
  printk ("zpci:zimb_pci_probe() was called!\n");
  return 0;
}

/**
 * when driver removed,call this function to release resources.
 * usually it will not be called until the OS shutdown.
 */
static void
zimb_pci_remove (struct pci_dev *dev)
{
  /**
   * in fact,I do not need to do any work here.
   */
  /*release irq */
  if (zbrd != NULL)
    {
      free_dma (zbrd->dma_tx_channel);
    /**
     * DMA transfer finished.
     * free memory.
     */
    dma_free_coherent (		///<
	NULL,///<
	DMA_BUF_SIZE,///<
	zbrd->dma_tx_virtual_addr,///<
	zbrd->dma_tx_physical_addr);
    }
  printk ("zpci:zimb_pci_remove() was called!\n");
  return;
}

/**
 * pci_driver struct define here
 */
static struct pci_driver zimb_pci_drv =
  {	///<
    .name = ZIMB_PCI_DRV_NAME,	///<
	.id_table = zimb_pci_id,	///<
	.probe = zimb_pci_probe,	///<
	.remove = zimb_pci_remove,	///<
    /**
     * resume,suspend are not supported this version.
     * manybe added in the future.
     */
    };

/**
 * module initialization,register device
 */
int
zimb_pci_init (void)
{
  int ret;
  dev_t devno;

  /**
   * check device structure
   */
  if (zbrd == NULL)
    {
      printk ("errro:zimb_pci_init():null pointer:zbrd\n");
      return -1;
    }

  do
    {
      /**
       *register char device
       */
      devno = MKDEV (ZIMB_PCI_NUM_MAJOR, 0);
      ret = register_chrdev_region (devno, 1, ZIMB_PCI_DRV_NAME);
      if (ret < 0)
	{
	  printk ("zpci_drv:error at register_chrdev_region()\n");
	  break;
	}

      /**
       * initialize & add device's character device table entry.
       */
      cdev_init (&zbrd->chardev, &zimb_pci_fops);
      zbrd->chardev.owner = THIS_MODULE;
      zbrd->chardev.ops = &zimb_pci_fops;
      ret = cdev_add (&zbrd->chardev, devno, 1);
      if (ret)
	{
	  printk ("zpci_drv:error at cdev_add()\n");
	  break;
	}

      /**
       * register driver with pci bus driver
       */
      ret = pci_register_driver (&zimb_pci_drv);
      if (ret < 0)
	{
	  printk ("zpci_drv:error at pci_register_driver()\n");
	  break;
	}
      /**
       * success here.
       */
      printk ("zpci:zsy_imb_pci_init() was called!\n");
      return 0;
    }
  while (0);
  /**
   * error occured when it reaches here.
   * do some roll-back work.
   */
  unregister_chrdev_region (MKDEV (ZIMB_PCI_NUM_MAJOR, 0), 1);
  pci_unregister_driver (&zimb_pci_drv);
  return -1;
}

/**
 *module cleanup,unregister device
 */
void
zimb_pci_exit (void)
{
  /**
   * disable PCI.
   */
  pci_disable_msi (zbrd->pcidev);
  pci_disable_device (zbrd->pcidev);

  /**
   * unmap I/O resource.
   */
  iounmap (zbrd->mmio_addr);
  zbrd->mmio_len = 0;

  /**
   * unregister character device.
   * unregister pci device.
   */
  cdev_del (&zbrd->chardev);
  unregister_chrdev_region (MKDEV (ZIMB_PCI_NUM_MAJOR, 0), 1);
  pci_unregister_driver (&zimb_pci_drv);

  printk ("zpci:zimb_pci_exit() was called!\n");
  return;
}

/**
 * tasklet for ISR.
 * ISR will be triggered when the following conditions happend:
 * 1.DMA data transfer finish.
 * 2.VNIC has data need to be read out.
 */
void
zimb_pci_isr_tasklet_handler (unsigned long data)
{
  unsigned long flags;
  /**
   * get global resource structure.
   */
  ZIMB_PCI_DEV *pres = (ZIMB_PCI_DEV *) (data);
  if (pres == NULL)
    {
      printk ("error:zimb_pci_isr_tasklet_handler():null pinter!\n");
      return;
    }

#if (ZDBG_LEVEL&ZDBG_ISR)
  printk ("info:zimb_pci_isr_tasklet_handler() was called!\n");
#endif

  /**
   * read ISR status register to detect which IRQ source happened.
   */
  flags = ioread32 (pres->mmio_addr + ZINT_STS);
#if (ZDBG_LEVEL&ZDBG_ISR)
  printk ("INT_STS=0x%lx\n", flags);
#endif

  /**
   * DMA_INT_STS
   * DMA data transfer finish.
   */
  if (flags & (0x1 << 0))
    {
      /**
       * write 1 to clear FPGA DMA IRQ
       * read-modify-write.
       */
      flags = ioread32 (pres->mmio_addr + ZDMA_INT);
      flags |= 0x1;
      iowrite32 (flags, pres->mmio_addr + ZDMA_INT);

#if (ZDBG_LEVEL&ZDBG_ISR)
      printk ("clear FPGA DMA IRQ\n");
      printk ("wake up\n");
#endif

      /**
       * wakeup dma write().
       */
      pres->dma_tx_busy = 0x1;
      wake_up_interruptible (&pres->dma_tx_wait);
    }

  /**
   * VNIC has data need to be read out.
   * FIFO_INT_STS
   * default read vnic data at 250ms timer.
   * for reducing response time,check it in ISR.
   */
  if (flags & (0x1 << 1))
    {
      /**
       * do not use spin_lock_irqsave() here,
       * it will close local interrupt.
       */
      if (!spin_is_locked (&pres->vnic_lock))
	{
	  spin_lock (&pres->vnic_lock);
	  zvnic_hw_read ();
	  spin_unlock (&pres->vnic_lock);
	}
    }
  /**
   * enable irq for next time.
   */
  enable_irq (pres->irq);
  return;
}

/*the end of file,for reading convenience 
 *shell.albert@gmail.com
 */
