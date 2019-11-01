#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main(void)
{
	int fd;
	FILE *fp;
	int length;
	int ret;
	char *buffer;
	fd=open("/dev/imb.0",O_RDWR);
	if(fd<0)
	{
		printf("open device file failed\n");
		return -1;
	}
	fp=fopen("dma.frame.0","r");
	if(fp==NULL)
	{
		printf("open dma.frame.0 failed\n");
		return -1;
	}
	fseek(fp,0,SEEK_SET);
	fseek(fp,0,SEEK_END);
	length=ftell(fp);
	if(length<=0)
	{
		printf("wrong length,exit\n");
		return -1;
	}
	printf("file length:%d bytes\n",length);
	fseek(fp,0,SEEK_SET);
	buffer=(char*)malloc(length);
	if(buffer==NULL)
	{
		printf("malloc() failed\n");
		return -1;
	}
	if(fread(buffer,length,1,fp)!=1)
	{
		printf("fread() failed\n");
		return -1;
	}
	ret=write(fd,buffer,length);
	printf("write DMA,ret=%d\n",ret);
	free(buffer);
	close(fp);
	close(fd);
	return 0;
}
