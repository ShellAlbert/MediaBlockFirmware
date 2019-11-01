/*filename:CGPIOModule.h
 *function:ds3650 test program 
 *ver:1.0
 *date:2013/2/4
 *author:zhangyinghua
 *mail:zhangyinghua@oristartech.com
*/

#ifndef _CGPIOMODULE_H_
#define _CGPIOMODULE_H_
#define IMX5_LED_NUM 6
int ds3650;
typedef struct
{
        char addr;/*register address for ds3234*/
        char val;/*value for register*/
}IMX5_DS3234_REG;

typedef struct
{
      unsigned char which;/*which ds3650 will be operated,0x01:ds3650-1(T1),0x2:ds3650-2(T2)*/
      char addr;/*register address for ds3650*/
      char val;/*value for register*/
}IMX5_DS3650_REG;

typedef enum
{
	IRQ_NO=0x0,
	IRQ_DS3650_1=0x1,
	IRQ_DS3650_2=0x2,
}IRQ_WHICH;


class CGPIOModule
{
public:
	CGPIOModule();
	~CGPIOModule();

	int set_led(int statusValue);
	int get_led(int *statusValue);
	/*ds3234*/
	int set_rtc(char year, char month, char date, char hour, char minute, char second);
	int get_rtc(char *year, char *month, char *date, char *hour, char *minute, char *second);
	/*ds3650,RegAddr:20h-Tamper Latch, 29h-VCCI,2Ah-VBAT,2Bh-VCCO*/
	int set_tamper(unsigned char Num,char RegAddr,char statusValue);
	int get_tamper(unsigned char Num,char RegAddr,char *RegValue);
	int get_Vol(unsigned char Num,char RegAddr,float *VolValue);
	/*ds3650 interrupt*/
        virtual	void get_intstatus();

private:
	int Open_Dev(char *devPath);
    	int Close_Dev(int fd);
	static  void ds3650_handler(int sig);
	void int_signal();
	int clear_irq_register(unsigned char Num);
	int led[IMX5_LED_NUM];
	int led_value;
	int ds3234;
	int flags;
};

#endif
