#ifndef _UDPFT_PACK_H_
#define _UDPFT_PACK_H_
//	udpft/pack.h
//	2010-09-10 by ShanLanshan
//	udp file transfer shared head file
//	define the transaction struct

#include <string.h>
#include "crypto/arithmatic.h"
#pragma pack(push)
#pragma pack(1)


#define TFCODE_START_TRANS	(10)
#define TFCODE_AGREE_TRANS	(20)
#define TFCODE_END_TRANS	(22)
#define TFCODE_SEND_DATA	(11)
#define TFCODE_REQUEST_BMP	(12)
#define TFCODE_REQUEST_DATA	(21)

struct TFPackHead {
	unsigned char flag[4];	// 4bytes Flag: UDPF
	unsigned char reserved;	// 0
	unsigned char code;	// function code
				// start trans	10
				// agree trans	20
				// end trans	22
				// send data	11
				// request data	21
	unsigned short len;	// body len
	unsigned long macb;	// CRC32 of body
	unsigned long mach;	// CRC32 of head
};

//extern unsigned long crc32(char* buf, unsigned long len);

struct TFPack 
{
	TFPackHead head;
	unsigned char body[1];
public:
	static TFPack* getTFPack(void *buf) 
	{
		return reinterpret_cast<TFPack*>(buf);
	};

	static TFPack* getTFPack(int bodylen) 
	{
		char *buf;
		buf = new char[bodylen + sizeof(TFPack)];
		return reinterpret_cast<TFPack*>(buf);
	};
public:
	void *getHead() {return this;};
	int getHeadLen() {return sizeof(head);};

	void *getBody() {return body;};
	int getBodyLen() {return head.len;};

	void *getAllBuf() {return this;};
	int getAllLen() const 
	{
		return head.len + sizeof(head);
	};

	//	Note:
	//	buf could be NULL, that means:
	//	you could make data on body directly, like this:
	//	char buf[2048];
	//	TFPack *p = TFPack::getTFPack(buf);
	//	int len = sprintf(p->getBody(), "hello, this is a message!");
	//	p->makePack(code, NULL, len);
	void makePack(int code, void *buf, int len) 
	{
		head.code = code;

		memcpy(head.flag, "UDPF", 4);
		head.reserved = 0;

		head.len = len;
		if (buf != NULL) 
		{
			memcpy(body, buf, len);
		}

		if (head.len)
		head.macb = CArithMatic::crc32((const char*)(body), head.len);
		head.mach = CArithMatic::crc32((const char*)(&head), sizeof(head) - sizeof(head.mach));
	};

	bool verifyHead() 
	{
		if (memcmp(head.flag, "UDPF", 4) != 0)
			return false;

		if (head.mach != CArithMatic::crc32((const char*)(&head), sizeof(head) - sizeof(head.mach)))
			return false;

		return true;
	};

	bool verifyPack() 
	{
		if (!verifyHead())
			return false;

		if (head.len && head.macb != CArithMatic::crc32((const char*)(body), head.len))
			return false;

		return true;
	};

};


struct StartTransBody 
{
	int filesize;
	unsigned long filecrc32;
	int type;
	char filename[1];
};

struct AgreeTransBody 
{
	int blocksize;
	char transferedEver;	//	'Y' for transfered
	char agree;		//	'Y' for agree
	char param[1];		//	if transferedEver is 'Y', there is a bittbl
				//	if agree is 'N', there is the reason
};

struct EndTransBody 
{
	char result;	//	'Y' for agree

	char desc[1];
};

struct SendDataBody 
{
	short blockID;
	char freshBittbl;	//	'Y': server send the bittbl again
	char data[1];
};

struct RequestDataBody 
{
	char allOver;	//	'Y' if all data transfered, there will be no bittbl
	char bittbl[1];
};

#pragma pack(pop)

#endif // !_UDPFT_PACK_H_
