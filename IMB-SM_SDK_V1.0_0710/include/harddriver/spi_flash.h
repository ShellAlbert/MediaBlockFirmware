#ifndef _SPI_WRITE_FLASH_
#define _SPI_WRITE_FLASH_

#define  FIFO_STATUS   0x10
#define  FIFO_DATA     0x14

// use Bank15~Bank6
#define BLK_END_ADDR  0x500000					// Bank 5 Starting Address
#define CONFIG_END_ADDR 0x8CE040

struct IMX5_ECSPI1_REG{
	unsigned int addr;/*the register address*/
	unsigned int val;/*the value of register*/
		/*in read mode,the val will hold the value readed from register*/
		/*in write mode,the val will be written to register*/
}reg_flash;

int fd;

int open_device();
   //-----------------------------------------------------------------------------
   //		Set Flash to Asynchronous Read Mode
   //-----------------------------------------------------------------------------
void set_config();

   //------------------------------------------------------------------------------
   //		Read CFI Data
   //------------------------------------------------------------------------------
   //read_CFI();


   //-----------------------------------------------------------------------------
   // flash prepare:  unlock, erease, blank check
   //-----------------------------------------------------------------------------
void flash_prepare();


   //-----------------------------------------------------------------------------
   //  Program Configuration Data
   //  1) Read from Configuration Fifo, which data is received from PCIe Side
   //  2) Split one 32bit-word to two 16bit-word ,and Program them into Flash(low bits first)
   //-----------------------------------------------------------------------------

void prog_config_data(char *fileName);

   //-----------------------------------------------------------------------------
   //  Verify Configuration Data
   //  1) Read from Configuration FIFO, which data is received from PCIe SIDE
   //  2) Read Configuration Data from Flash Chip,
   //  3) Compare them,
   //-----------------------------------------------------------------------------

void verify_config_data(char *fileName);

void delay();

void bus_wr(unsigned int addr, unsigned int wdata);

unsigned int bus_rd(unsigned int addr);

void check_sts();

void read_CFI();

void read_sts_setup (unsigned int bank_addr);

unsigned int read_sts (unsigned int bank_addr);

void read_sig(unsigned int block_addr);

void blocks_unlock();

void blocks_erease();

void blocks_blankcheck();

void read_array(unsigned int BKA,unsigned int WA,unsigned int word_num);

void read_array_noswap_verify();

void PrgWord(unsigned int WA,unsigned int PD);

#endif