#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
int main(void)
{
  char buffer[256];
  struct hostent *phostent;
    /**
   * get local ip address.
   */
  memset (buffer, 0, sizeof(buffer));
  if (gethostname (buffer, 256) < 0)
    {
		printf("gethostname() failed\n");
      return -1;
    }
  printf("hostname=%s\n",buffer);
  phostent = gethostbyname (buffer);
  if (phostent == NULL)
    {
		herror("gethostbyname");
      return -1;
    }

  switch (phostent->h_addrtype)
    {
    case AF_INET:
      printf("ipv4\n");
      break;
    case AF_INET6:
      printf("ipv6\n");
      break;
    default:
      return -1;
    }
    return 0;
}
