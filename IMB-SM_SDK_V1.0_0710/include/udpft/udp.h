#ifndef _UDPFT_UDP_H_
#define _UDPFT_UDP_H_
//	udpft/udp.h
//	2010-09-13 by ShanLanshan

int udp_create(const char *localip, int localport);

int udp_sendto(int nSockID, const char *pData, int nDataLen, const char *ip, int port);

int udp_syn_recvfrom(int nSocket, char *pData, int nDataLen, int nTimeOut, char *ip, int *port);

#define udp_close(fd)	close(fd)

#endif //!_UDPFT_UDP_H_
