/*
 * zip_server.cpp
 *
 *  Created on: 2014年11月27日
 *      Author: shell.albert
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <zip_server.h>
#include <zclient_affair.h>
/**
 * @brief read a UDP packet from socket buffer.
 * parse it and give response.
 * @param fd
 */
zint32_t
zip_read_packet_and_parse_it (zint32_t fd)
{
  zint32_t ret;
  ZPACKET_UDP packet;
  struct sockaddr_in addr_client;
  zint32_t addr_len = sizeof(struct sockaddr_in);

  /**
   * receive a packet.
   */
  ret = recvfrom (fd, &packet, sizeof(packet), 0, (struct sockaddr*) &addr_client, (socklen_t*) &addr_len);
  if (ret < 0)
    {
      printf ("error at recvfrom():%s\n", strerror (errno));
      return ZRC_SocketRecvFailed;
    }
  /**
   * print client info.
   */
  printf ("<IPServer>:Request from %s:%d.\n.", inet_ntoa (addr_client.sin_addr), ntohs (addr_client.sin_port));

  /**
   * build an ACK packet.
   */
  packet.type = htonl (PKT_UDP_QUERY_SERVER_IP_ACK);
  packet.data = 0;

  /**
   * send ack packet
   */
  ret = sendto (fd, &packet, sizeof(packet), 0, (struct sockaddr*) &addr_client, addr_len);
  if (ret < 0)
    {
      printf ("error at send():%s\n", strerror (errno));
      return ZRC_SocketSendFailed;
    }
  //printf ("send ACK UDP packet finish!\n.");
  return ZRC_Success;
}

/**
 * @brief async receive thread.
 * async receive data from socket.
 */
void*
thread_zip_server (void* arg)
{
  zint32_t ret;
  zint32_t opt;
  zint32_t fd_sock;
  struct sockaddr_in addr_server;
  fd_set fdset_read;
  struct timeval tv;

  /**
   * create UDP socket.
   */
  fd_sock = socket (AF_INET, SOCK_DGRAM, 0);
  if (fd_sock < 0)
    {
      printf ("error at socket():%s\n", strerror (errno));
      return NULL;
    }
  /**
   * enable REUSEADDR feature.
   */
  opt = 1;
  if (setsockopt (fd_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(socklen_t)) < 0)
    {
      ZPrintError("setsockopt() failed:%s\n", strerror (errno));
      close (fd_sock);
      return NULL;
    }
  /**
   * bind server address to a socket.
   */
  memset ((void*) &addr_server, 0, sizeof(struct sockaddr_in));
  addr_server.sin_family = AF_INET;
  addr_server.sin_addr.s_addr = htons (INADDR_ANY);
  addr_server.sin_port = htons (ZIP_SERVER_PORT);
  ret = bind (fd_sock, (struct sockaddr*) &addr_server, sizeof(addr_server));
  if (ret < 0)
    {
      printf ("error at bind():%s\n", strerror (errno));
      return NULL;
    }
  /**
   * detach myself.
   */
  pthread_detach (pthread_self ());
  printf ("<IPServer>:Listening on UDP[%d]...\n", ZIP_SERVER_PORT);

  do
    {
      ///exit self
      /**
       * check if parent id equals 1,
       * it means parent process is dead,
       * exit myself.
       */
      if (getppid () == 1)
	{
	  printf ("<IPServer>:Thread exit.\n");
	  break;
	}

      /**
       * async select().
       */
      FD_ZERO(&fdset_read);
      FD_SET(fd_sock, &fdset_read);
      tv.tv_sec = 0; ///< 1s
      tv.tv_usec = 1000 * 10; ////<10ms
      ret = select (fd_sock + 1, &fdset_read, NULL, NULL, &tv);
      if (ret < 0)
	{
	  printf ("error at select():%s\n", strerror (errno));
	  break;
	}
      else if (ret == 0)
	{
	  /**
	   * timeout.
	   */
	  continue;
	}
      else
	{
	  /**
	   * here ret>0.
	   */
	  if (FD_ISSET(fd_sock, &fdset_read))
	    {
	      /**
	       * receive a packet and parse it.
	       */
	      ret = zip_read_packet_and_parse_it (fd_sock);
	      if (ret < 0)
		{
		  break;
		}
	    }
	}
    }
  while (1);
  pthread_exit (0);
  return 0;
}
