#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <string.h>
#include <sys/times.h>

const char *filename = "/dev/mvc_card/card0";
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
typedef struct
{
  unsigned int offset;
  unsigned int value;
} STRU_DRW;

int
main (void)
{
  int fd;
  STRU_DRW reg;
  int i;
  struct timeval pstart,pend;
  float timeuse;


  gettimeofday(&pstart,NULL);
  for (i = 0; i < 10000; i++)
    {
      fd = open (filename, O_RDWR);
      if (fd < 0)
	{
	  printf ("open %s failed:%s\n", filename, strerror (errno));
	  return -1;
	}
      reg.offset = 0x1008;
      reg.value = 0x2222;
      if (ioctl (fd, ZIOCTL_DW_REGS, &reg) != 0)
	{
	  printf ("ioctl() read register failed!\n");
	  return -1;
	}

      memset (&reg, 0, sizeof (reg));
      reg.offset = 0x1008;
      if (ioctl (fd, ZIOCTL_DR_REGS, &reg) != 0)
	{
	  printf ("ioctl() read register failed!\n");
	  return -1;
	}
      printf ("read value:0x%x\n", reg.value);
      close (fd);
    }
  gettimeofday(&pend,NULL);
  timeuse=1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);
  timeuse/=1000000;
  printf("timeuse=%f\n",timeuse);
  return 0;
}
