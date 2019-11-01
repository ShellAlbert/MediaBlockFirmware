/**
 * @file zdevice_interface.cpp
 * @date May 28,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief interface wrapper function to operate device file
 */
#include <zdevice_interface.h>
#include <zerrno.h>
#include <zprotocol.h>
#include <zfpga_para.h>
#include <sys/time.h>
//do not use device
//#define Device_Bypass	1

/**
 * initial device structure.
 */
zint32_t
device_init (zfpga_dev *dev)
{
  if (dev == NULL)
    {
      return ZRC_NullPointer;
    }
#ifdef Device_Bypass
  dev->fd = 2;
  dev->opened = ZRC_Yes;
  pthread_mutex_init (&dev->lock, NULL);
  dev->reg.offset = 0;
  dev->reg.value = 0;
  return ZRC_Success;
#endif

  dev->fd = -1;
  dev->opened = ZRC_No;
  pthread_mutex_init (&dev->lock, NULL);
  dev->reg.offset = 0;
  dev->reg.value = 0;
  return ZRC_Success;
}
/**
 * @brief open device file
 */
zint32_t
device_open (const zint8_t *filename, zfpga_dev *dev)
{
  int flags;
#ifdef Device_Bypass
  dev->fd = 2;
  dev->opened = ZRC_Yes;
  return ZRC_Success;
#endif

  /**
   * check validation of parameters.
   */
  if (filename == NULL || dev == NULL)
    {
      return ZRC_NullPointer;
    }
  dev->fd = open (filename, O_RDWR);
  if (dev->fd < 0)
    {
      printf ("warning:device open failed:%s!\n", strerror (errno));
      dev->opened = ZRC_No;
      return ZRC_DeviceFileOpenFailed;
    }
  else
    {
      flags = fcntl (dev->fd, F_GETFD);
      flags |= FD_CLOEXEC;
      fcntl (dev->fd, F_SETFD, flags);
      dev->opened = ZRC_Yes;
      return ZRC_Success;
    }
}

/**
 * @brief read register
 */
zint32_t
device_read_reg (zfpga_dev *dev, zuint32_t address, zuint32_t *value)
{
  zint32_t ret;
  PCIRegister reg;
  /**
   * bypass device.
   */
#ifdef Device_Bypass
  return ZRC_Success;
#endif
  /**
   * check validation of parameters.
   */
  if (dev == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * check valid of fd.
   */
  if (dev->fd < 0)
    {
      printf ("warning:device is not opened!\n");
      return ZRC_DeviceFileNotOpened;
    }

  /**
   * ioctl() read register.
   */
  pthread_mutex_lock (&dev->lock);
  reg.offset = address;
  reg.value = 0;
  ret = ioctl (dev->fd, ZIOCTL_DR_REGS, &reg);
  pthread_mutex_unlock (&dev->lock);
  if (ret < 0)
    {
      return ZRC_ReadFPGARegisterFailed;
    }
  else
    {
      *value = reg.value;
      return ZRC_Success;
    }
}

/**
 * @brief write register
 */
zint32_t
device_write_reg (zfpga_dev *dev, zuint32_t address, zuint32_t value)
{
  zint32_t ret;
  PCIRegister reg;
#if 0
  FILE*fp;
  char buffer[1024];
  fp = fopen ("regs_set.data", "a+");
  if (fp != NULL)
    {
      memset (buffer, 0, sizeof(buffer));
      sprintf (buffer, "offset=0x%x,value=0x%x\n", address, value);
      fwrite (buffer, strlen (buffer), 1, fp);
      fclose (fp);
    }
#endif

  /**
   * check validation of parameters.
   */
  if (dev == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * bypass device.
   */
#ifdef Device_Bypass
  return ZRC_Success;
#endif

  /**
   * check valid of fd.
   */
  if (dev->fd < 0)
    {
      printf ("warning:device is not opened!\n");
      return ZRC_DeviceFileNotOpened;
    }

  /**
   * ioctl() write register.
   */
  pthread_mutex_lock (&dev->lock);
  reg.offset = address;
  reg.value = value;
  ret = ioctl (dev->fd, ZIOCTL_DW_REGS, &reg);
  pthread_mutex_unlock (&dev->lock);
  if (ret < 0)
    {
      return ZRC_WriteFPGARegisterFailed;
    }
  else
    {
      return ZRC_Success;
    }
}

/**
 * @brief write DMA data
 */
zint32_t tindex = 0;
zint32_t
device_write_dma (zfpga_dev *dev, zuint8_t *buffer, zuint32_t len)
{
  zint32_t ret;
  struct timeval startTime, endTime;
  zuint32_t cost_time;
  /**
   * save data into local hard disk file to check.
   */
#if 0
  FILE*fp;
  char filename[256];
  memset (filename, 0, sizeof(filename));
  sprintf (filename, "dma.frame.%d", tindex++);
  fp = fopen (filename, "wb");
  if (fp != NULL)
    {
      fwrite (buffer, len, 1, fp);
      fclose (fp);
      printf ("write dma data to local file finish!\n");
    }
  if (tindex >= 10)
    {
      printf ("generated 10 frames,wait getchar()...\n");
      getchar ();
    }
#endif
  /**
   * check validation of parameters.
   */
  if (dev == NULL)
    {
      return ZRC_NullPointer;
    }
  /**
   * bypass device.
   */
#ifdef Device_Bypass
  return ZRC_Success;
#endif

  /**
   * check valid of fd.
   */
  if (dev->fd < 0)
    {
      printf ("warning:device is not opened!\n");
      return ZRC_DeviceFileNotOpened;
    }
  /**
   * write().
   */
  pthread_mutex_lock (&dev->lock);
  gettimeofday (&startTime, NULL);
  ret = write (dev->fd, buffer, len);
  gettimeofday (&endTime, NULL);
  cost_time = 1000000 * (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
  printf ("cost time:%.2f ms\n", cost_time / 1000.0);
  pthread_mutex_unlock (&dev->lock);
  if (ret < 0)
    {
      return ZRC_TransferDMADataFailed;
    }
  else
    {
      return ZRC_Success;
    }
}

/**
 * @brief close device file
 */
void
device_close (zfpga_dev *dev)
{
#ifdef Device_Bypass
  return;
#endif
  /**
   * check validation of parameters.
   */
  if (dev == NULL)
    {
      return;
    }
  pthread_mutex_lock (&dev->lock);
  close (dev->fd);
  dev->opened = ZRC_No;
  pthread_mutex_unlock (&dev->lock);
  return;
}
/**
 * @brief device file is opened or not?
 */
zint32_t
device_is_opened (zfpga_dev *dev)
{
  zint32_t ret;
  /**
   * check validation of parameters.
   */
  if (dev == NULL)
    {
      return ZRC_NullPointer;
    }
#ifdef Device_Bypass
  return ZRC_Success;
#endif
  pthread_mutex_lock (&dev->lock);
  if (dev->fd > 0 && dev->opened == ZRC_Yes)
    {
      ret = ZRC_Success;
    }
  else
    {
      ret = ZRC_DeviceFileNotOpened;
    }
  pthread_mutex_unlock (&dev->lock);
  return ret;
}

/**
 * @brief active FPGA decoder IP core
 */
#if 0
zint32_t
device_active_ipcore (zfpga_dev *dev, zint32_t lic_key_lsb, zint32_t lic_key_msb)
  {
    zint32_t ret;
    int32_t rdata;
    int32_t tmp_trial;

    /*timeout 5 seconds to exit*/
    int32_t timeout = 0;
    int32_t timeout_seconds = 5;

    //read PRP_KEY_CSR register
    dev->reg.offset = OPB_ADDR;
    dev->reg.value = 0x0045;
    ret = device_write_reg (dev);//write adr
    if (ret < 0)
      {
	return ret;
      }

    dev->reg.offset = OPB_ANC_RDATA;
    ret = device_read_reg (dev); //read ancillary data
    rdata = dev->reg.value;
    if (ret < 0)
      {
	return ret;
      }

    dev->reg.offset = OPB_STS;
    ret = device_read_reg (dev); //read sts
    rdata = dev->reg.value;
    if (ret < 0)
      {
	return ret;
      }
    while (rdata == 0) //read sts until the end
      {
	dev->reg.offset = OPB_STS;
	ret = device_read_reg (dev); //read sts
	rdata = dev->reg.value;
	if (ret < 0)
	  {
	    return ret;
	  }
	/*timeout 5 seconds to exit*/
	if (timeout++ >= timeout_seconds)
	  {
	    printf ("error:timeout 300ms to exit\n");
	    return ZRC_OperationTimeout;
	  }
	usleep (1000 * 300); //300ms
      }

    //read data.
    dev->reg.offset = OPB_RDATA;
    ret = device_read_reg (dev);
    rdata = dev->reg.value;
    if (ret < 0)
      {
	return ret;
      }
    printf ("info:Read opb PRP_KEY_CSR=%x.....\n", rdata);

    //judge ACT,if ACT==1,then IP core is full_mode,
    //if ACT==0,go to next step of flow-chart
    if (rdata & 0x100)
      {
#if (ZDBG_LEVEL &ZDBG_ACTIVE_FPGA)
	printf("info:IP CORE IS FULL_MODE.\n");
#endif
      }

    while (!(rdata & 0x100))
      {
	//judge KEY_ACT_TRIAL
	//if KEY_ACT_TRIAL<4,then go to next step of flow-chart
	//else IP CORE is blocked_mode
	if (rdata & 0x100)
	  {
	    printf ("info:IP CORE IS FULL_MODE.\n");
	    break;
	  }

	if ((rdata & 0xF) >= 0x4)
	  {
	    printf ("info:IP CORE IS BLOCK_MODE.\n");
	    break;
	  }

	//IP CORE IS LIMITED_MODE
	printf ("IP CORE IS LIMITED_MODE.\n");
	tmp_trial = (rdata & 0x0F);
	ZDBG("TMP_TRIAL=%x.....\n", tmp_trial);
	ZDBG("Check CORE KEY LOGIC IS READY ???\n");

	//read PRP_KEY_CSR register to judge CORE KEY LOGIC is READY or NOT
	//write adr
	dev->reg.offset = OPB_ADDR;
	dev->reg.value = 0x0045;
	ret = device_write_reg (dev);
	if (ret < 0)
	  {
	    return ret;
	  }

	//read ancillary data
	dev->reg.offset = OPB_ANC_RDATA;
	device_read_reg (dev);
	rdata = dev->reg.value;
	//read status data
	dev->reg.offset = OPB_STS;
	device_read_reg (dev);
	rdata = dev->reg.value;
	while (rdata == 0)
	  {
	    /*read status data*/
	    dev->reg.offset = OPB_STS;
	    device_read_reg (dev);
	    rdata = dev->reg.value;
	    /*timeout 5 seconds to exit*/
	    if (timeout++ >= timeout_seconds)
	      {
		printf ("error:timeout 300ms to exit\n");
		return -1;
	      }
	    usleep (1000 * 300);		//300ms
	  }

	//read PRP_KEY_CSR data
	dev->reg.offset = OPB_RDATA;
	device_read_reg (dev);
	rdata = dev->reg.value;
	printf ("info:Read PRP_KEY_CSR= %x......\n", rdata);

	//judge RDY
	//if RDY==1,then go to the next step of flow-chart
	//if RDY==0,then re-read PRP_KEY_CSR,until it equals 1
	while (!(rdata & 0x10))
	  {
	    printf ("Core Key Logic is not ready....\n");

	    dev->reg.offset = OPB_ADDR;
	    dev->reg.value = 0x0045;
	    device_write_reg (dev); //write adr
	    dev->reg.offset = OPB_ANC_RDATA;
	    device_read_reg (dev);//read ancillary data
	    rdata = dev->reg.value;
	    dev->reg.offset = OPB_STS;
	    device_read_reg (dev);
	    rdata = dev->reg.value;
	    while (rdata == 0)
	      {
		dev->reg.offset = OPB_STS;
		device_read_reg (dev);
		rdata = dev->reg.value;
		/*timeout 5 seconds to exit*/
		if (timeout++ >= timeout_seconds)
		  {
		    printf ("error:timeout 300ms to exit\n");
		    return -1;
		  }
		usleep (1000 * 300); //300ms
	      }

	    dev->reg.offset = OPB_RDATA;
	    device_read_reg (dev);
	    rdata = dev->reg.value;
	    printf ("Read PRP_KEY_CSR= %x.....\n", rdata);
	  }

	//download key
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");
	//write adr
	dev->reg.offset = OPB_ADDR;
	dev->reg.value = 0x0042;
	device_write_reg (dev);
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");
	//write adr LIC_KEY_LSB
	dev->reg.offset = OPB_WDATA;
	dev->reg.value = lic_key_lsb;
	device_write_reg (dev);
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");
	//write adr
	dev->reg.offset = OPB_ADDR;
	dev->reg.value = 0x0043;
	device_write_reg (dev);
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");
	//write adr LIC_KEY_MSB
	dev->reg.offset = OPB_WDATA;
	dev->reg.value = lic_key_msb;
	device_write_reg (dev);
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");
	//write adr
	dev->reg.offset = OPB_ADDR;
	dev->reg.value = 0x0044;
	device_write_reg (dev);
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");
	//write adr PRP_KEY_ACTIVE
	dev->reg.offset = OPB_WDATA;
	dev->reg.value = 0x0;
	device_write_reg (dev);
	printf ("CORE KEY LOGIC IS READY,DOWNLOAD KEY\n");

	printf ("Check KEY_ACT_TRIAL number\n");
	//write adr
	dev->reg.offset = OPB_ADDR;
	dev->reg.value = 0x0045;
	device_write_reg (dev);
	//read ancillary data
	dev->reg.offset = OPB_ANC_RDATA;
	device_read_reg (dev);
	rdata = dev->reg.value;
	dev->reg.offset = OPB_STS;
	device_read_reg (dev);
	rdata = dev->reg.value;
	while (rdata == 0)
	  {
	    dev->reg.offset = OPB_STS;
	    device_read_reg (dev);
	    rdata = dev->reg.value;
	    /*timeout 5 seconds to exit*/
	    if (timeout++ >= timeout_seconds)
	      {
		printf ("error:timeout 300ms to exit\n");
		return -1;
	      }
	    usleep (1000 * 300); //300ms
	  }
	dev->reg.offset = OPB_RDATA;
	device_read_reg (dev);
	rdata = dev->reg.value;
	printf ("Read PRP_KEY_CSR= %x......\n", rdata);

	//KEY_ACT_TRIAL=1 or KEY_ACT_TRIAL!=TMP_TRIAL
	while (!(((rdata & 0xF) == 0x0) || ((rdata & 0xF) != tmp_trial)))
	  {
	    dev->reg.offset = OPB_ADDR;
	    dev->reg.value = 0x0045;
	    device_write_reg (dev);

	    dev->reg.offset = OPB_ANC_RDATA;
	    device_read_reg (dev);
	    rdata = dev->reg.value;

	    dev->reg.offset = OPB_STS;
	    device_read_reg (dev);
	    rdata = dev->reg.value;
	    while (rdata == 0)
	      {
		dev->reg.offset = OPB_STS;
		device_read_reg (dev);
		rdata = dev->reg.value;
		/*timeout 5 seconds to exit*/
		if (timeout++ >= timeout_seconds)
		  {
		    printf ("error:timeout 300ms to exit\n");
		    return -1;
		  }
		usleep (1000 * 300); //300ms
	      }

	    dev->reg.offset = OPB_RDATA;
	    device_read_reg (dev);
	    rdata = dev->reg.value;
	    printf ("Read PRP_KEY_CSR= %x....\n", rdata);
	  }

	printf ("Return to check ACT \n");
	if (rdata & 0x100)
	  {
	    printf ("IP CORE IS FULL_MODE\n");
	    printf ("IP CORE IS FULL_MODE\n");
	  }
      }
    return 0;
  }
#endif
/**
 * the end of file,tagged by ZSY
 */
