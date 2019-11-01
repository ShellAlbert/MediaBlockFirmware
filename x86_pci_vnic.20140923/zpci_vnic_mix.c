/*filename:zpci_vnic_mix.c
 *ver:1.0
 *date:March 2,2014
 *author zhangshaoyan
 *author shell.albert@gmail.com
 */
#include "zpci_drv.h"
#include "zvnic_drv.h"

/**
 * @brief global variable define here
 */
ZIMB_PCI_DEV *zbrd;

unsigned char isr_pci = 0x1;
unsigned char isr_vnic = 0x2;

/**
 * @brief pci&vnic driver initial section
 * must register pci device first
 * because the lower layer of vnic is pci interface
 */
int __init
zpci_vnic_mix_init (void)
{
  int rc;

  /**
   *allocate memory for common structure.
   *if each of steps failed,roll-back.
   */
  do
    {
      zbrd = kmalloc (sizeof(ZIMB_PCI_DEV), GFP_KERNEL);
      if (zbrd == NULL)
	{
	  printk ("zpci_vnic:kmalloc() faied.\n");
	  break;
	}

      zbrd->vnic_rxbuffer = kmalloc (ZVNIC_RX_BUFSIZE, GFP_KERNEL);
      if (zbrd->vnic_rxbuffer == NULL)
	{
	  printk ("zpci_vnic:kmalloc() failed for vnic rx buffer\n");
	  break;
	}

      zbrd->vnic_txbuffer = kmalloc (ZVNIC_TX_BUFSIZE, GFP_KERNEL);
      if (zbrd->vnic_txbuffer == NULL)
	{
	  printk ("zpci_vnic:kmalloc() failed for vnic tx buffer\n");
	  break;
	}

      /**
       * allocate 1MB big buffer for arrange un-complete TCP/IP packets.
       */
      zbrd->vnic_rxbuffer_big = kmalloc (2 * 1024 * 1024, GFP_KERNEL);
      if (zbrd->vnic_rxbuffer_big == NULL)
	{
	  printk ("zpci_vnic:kmalloc() failed for vnic rx buffer big!\n");
	  break;
	}
      zbrd->vnic_rxbuffer_big_len = 0;

      /**
       *init PCI device first
       */
      rc = zimb_pci_init ();
      if (rc < 0)
	{
	  printk ("zpci_vnic:zimb_pci_init() failed!\n");
	  break;
	}

      /**
       *init VNIC device second
       */
      rc = zvnic_init ();
      if (rc < 0)
	{
	  printk ("zpci_vnic:zvnic_init() failed!\n");
	  break;
	}

      //install IRQ isr
      /**
       * critical error here
       * IRQF_SHARED will cause system-down
       */

//  rc = request_irq (zbrd->irq, zimb_vnic_isr,
//		    IRQF_SHARED, "mvc_dma_isr", (void *) &isr_vnic);
//  if (rc)
//    {
//      ZKDBG ("error at request_irq()\n");
//      break;
//    }
      rc = request_irq (zbrd->irq, zimb_pci_isr, ///<
			IRQF_DISABLED, "mvc_pci_isr", ///<
			(void *) &isr_pci);
      if (rc)
	{
	  printk ("zpci_vnic:error at request_irq().\n");
	  break;
	}

      set_irq_type (zbrd->irq, IRQ_TYPE_LEVEL_LOW);

      /**
       * success here.
       */
      printk ("zpci_vnic:%s success\n", __FUNCTION__);
      printk ("zpci_vnic:HZ=%d\n", HZ);
      printk ("zpci_vnic:jiffies=%ld\n", jiffies);
      return 0;
    }
  while (0);
  /**
   * some error occur when it reaches here.
   */

  zimb_pci_exit ();
  zvnic_exit ();
  if (zbrd->vnic_txbuffer != NULL)
    {
      kfree (zbrd->vnic_txbuffer);
      zbrd->vnic_txbuffer = NULL;
    }
  if (zbrd->vnic_rxbuffer != NULL)
    {
      kfree (zbrd->vnic_rxbuffer);
      zbrd->vnic_rxbuffer = NULL;
    }
  if (zbrd != NULL)
    {
      kfree (zbrd);
      zbrd = NULL;
    }
  return -1;
}

void __exit
zpci_vnic_mix_exit (void)
{
  free_irq (zbrd->irq, (void *) &isr_pci);
  // free_irq (zbrd->irq, (void *) &isr_vnic);

  /**
   * do de-init work.
   */
  zvnic_exit ();
  zimb_pci_exit ();
  /**
   * release memory.
   */
  if (zbrd->vnic_txbuffer != NULL)
    {
      kfree (zbrd->vnic_txbuffer);
      zbrd->vnic_txbuffer = NULL;
    }
  if (zbrd->vnic_rxbuffer != NULL)
    {
      kfree (zbrd->vnic_rxbuffer);
      zbrd->vnic_rxbuffer = NULL;
    }
  if (zbrd != NULL)
    {
      kfree (zbrd);
      zbrd = NULL;
    }
  return;
}

module_init ( zpci_vnic_mix_init);
module_exit ( zpci_vnic_mix_exit);
MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("shell.albert@gmail.com");
/**
 *the end of file,for reading convenience
 *shell.albert@gmail.com
 */
