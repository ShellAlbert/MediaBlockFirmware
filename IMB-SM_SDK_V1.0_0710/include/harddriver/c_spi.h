#ifndef _CLASS_SPI_MODULE_H_
#define _CLASS_SPI_MODULE_H_

#include "harddriver/data_types.h"				//added by sunpeng at 20131213

#define KEY_CTL_REGADD          0x00
#define KEY_DATA_REGADD         0x01

#define PCI_TOARM_DATA          0x20
#define ARM_TOPCI_DATA          0x21
#define PCI_TOARM_LEN						0x22
#define ARM_TOPCI_LEN           0x23

#define IMB_WATERMARK_WM1				0x50
#define IMB_WATERMARK_WM0				0x51
#define IMB_WATERMARK_CTL				0x52
#define PROC_CTL                0x60
#define FPGA_STATUS             0x62
#define LED_CTL                 0x63

enum LED_INDEX{
	led1,led2,led3,led4
};

enum LED_COLOR{
	red,gre,yel,down
};

struct IMX5_ECSPI1_CON{
	int addr;/*the register address*/
	int val;/*the value of register*/
		/*in read mode,the val will hold the value readed from register*/
		/*in write mode,the val will be written to register*/
};
/// 内容密钥信息结构体

class CSPIModule
{
public:
	CSPIModule();
	~ CSPIModule ();


	
	
public:
	
	int write_to_spi(IMX5_ECSPI1_CON reg);
	
  int read_from_spi(IMX5_ECSPI1_CON reg);
	
	static void fpga_int1_signal(int sig);

	int open_device(void);

	int reset_device(void);

	int set_cek(struct content_key *pcek,int cek_num);

	int clear_cek(void);

	int set_forensicmarking_inf(struct forensic_data *pfod);

	int set_forensicmarking_key(struct forensic_data *pfod);
	
	int set_leap_year_enable(void);
	
	int set_leap_year_disable(void);
	
	int set_forensicmarking_enable(void);

	int set_forensicmarking_disable(void);
	
	int set_display_enable(void);

	int set_display_disable(void);

	int get_selftest_result(void);
	
	int get_status(int * pstatus);
	
	int key_readback(void);/////回读key函数
	
	int write_to_pci(unsigned char *data,unsigned int len);//写pci
	
	int import_firmware(const char *fileName);
	
	int led_control(int led_index , int color_flag);

	int close_device();
	
private:
	
	static int fd;
	
};

#endif