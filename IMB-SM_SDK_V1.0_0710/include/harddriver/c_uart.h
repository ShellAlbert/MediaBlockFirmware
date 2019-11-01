#ifndef _CLASS_UART_MODULE_H_
#define _CLASS_UART_MODULE_H_

#include <linux/ioctl.h>


#define RESET_DSP_SYSTEM         		0x76   //reset dsp systerm
#define WATER_MARKING_ENABLE    		0x61 	 //enable the water mark process
#define WATER_MARKING_DISABLE    		0x62       //disable the water mark process
#define SET_WM_SAMPLE_FREQ       		0x71           //set the water marking sample frequency (WM mean Water Marking)
#define SET_DSP_OUTPUT_CHANNEL   		0x72	//set the dsp output channel

#define GET_GLOBAL_ENABLE_STATUS   		0x68		  //get water marking global enable status
#define GET_CHANNEL_ACTIVE_STATUS  		0x6a       //get channels activation status
#define GET_SND_PATTERN_ACTIVE_STATUS	0x6b  //get sound pattern activation status
#define GET_SAMPLING_FREQ          		0x69       //get audio sampling frequency
#define GET_VERSION                     0x6d  //get the library version which used to add the watermark

/*ioctl command for dsp(hard reset)*/
#define DSP_IOCTL_MAGIC 's'
#define DSP_IOCTL_RESET_LOW	_IO(DSP_IOCTL_MAGIC,1)
#define DSP_IOCTL_RESET_HIGH	_IO(DSP_IOCTL_MAGIC,2)
#define DSP_IOCTL_MAXNR 2

class CUARTModule
{
	
public:
	CUARTModule();
	 ~CUARTModule();
private:
	int fd;	
public:
	int open_device(void);
	
	int reset_device(void);
	
	int hard_reset_device(void);
	
	int set_channel_num(unsigned int num);
	
	int set_sampling_frequency(unsigned int freq);
	
	int set_watermark_enable(void);
	
	int set_watermark_disable(void);
	
	int set_payload(unsigned char *pcmd, unsigned int cmd_len);
	
	int get_config_info(int *pchannel_num, int *pfreq, bool *penable_watermark, char *pdevice_version, int *pversion_len);
	
	int get_status(int *pstatus);
	
	int close_device(void);
	
	int write_uart(unsigned int byt1);
};

#endif