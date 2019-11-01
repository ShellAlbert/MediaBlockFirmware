#include <string.h>
int main(void)
{
	char buf[]="subtitle.xml";
	int i;
	printf("size:0x%x\n",strlen(buf));
	for(i=0;i<sizeof(buf);i++)
	{
		printf("0x%x,",buf[i]);
	}
	printf("\n");
	return 0;
}
