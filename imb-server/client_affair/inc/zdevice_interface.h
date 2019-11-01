/**
 * @file zdevice_interface.h
 * @date May 28,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief interface wrapper function to operate device file
 */
#ifndef _ZDEVICE_INTERFACE_H__
#define _ZDEVICE_INTERFACE_H__

#include <zdata_types.h>
#include <linux/ioctl.h>

/**
 * default device filename.
 */
#define DEVICE_FILE_NAME	"/dev/imb.0"

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

/*structure for ioctl()
 *basic pci register read&write
 */
typedef struct
{
  zuint32_t offset;
  zuint32_t value;
} PCIRegister;

/**
 * FPGA device structure.
 */
typedef struct
{
  zint32_t fd; ///<file descriptor.
  zint32_t opened; ///<device opened or not.
  pthread_mutex_t lock; ///<lock for device file
  PCIRegister reg; ///<pci register.
} zfpga_dev;

/**
 * initial device structure.
 */
extern zint32_t
device_init (zfpga_dev *dev);
/**
 * @brief open device file
 */
extern zint32_t
device_open (const zint8_t *filename, zfpga_dev *dev);

/**
 * @brief read register
 */
extern zint32_t
device_read_reg (zfpga_dev *dev, zuint32_t address, zuint32_t *value);

/**
 * @brief write register
 */
extern zint32_t
device_write_reg (zfpga_dev *dev, zuint32_t address, zuint32_t value);

/**
 * @brief write DMA data
 */
extern zint32_t
device_write_dma (zfpga_dev *dev, zuint8_t *buffer, zuint32_t len);

/**
 * @brief close device file
 */
extern void
device_close (zfpga_dev *dev);

/**
 * @brief device file is opened or not?
 */
extern zint32_t
device_is_opened (zfpga_dev *dev);

/**
 * @brief active FPGA decoder IP core
 */
extern zint32_t
device_active_ipcore (zfpga_dev *dev, zint32_t lic_key_lsb, zint32_t lic_key_msb);
#endif //_ZDEVICE_INTERFACE_H__
/**
 * the end of file,tagged by ZSY
 */
