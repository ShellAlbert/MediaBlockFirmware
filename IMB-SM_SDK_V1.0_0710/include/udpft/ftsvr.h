#ifndef _UDPFT_FTSVR_H_
#define _UDPFT_FTSVR_H_
//	udpft/ftsvr.h
//	2010-09-20 by ShanLanshan
//
#include <stdio.h>
#include <string.h>
#include "common/replant.h"
#include "udpft/iudpft.h"

//#define SIMPLE_TFTASKQUEUE

class TftaskQueue 
{
public:
	struct Entry 
	{
		char filename[256];
		int type;
		int *status;
		bool operator==(Entry &e) 
		{
			if (type != e.type)
				return false;

			if (strcmp(filename, e.filename) != 0)
				return false;

			return true;
		};
	};
public:
	TftaskQueue();
	bool addTask(const char *filename, int type, int *status);
	bool getTask(char *filename, int *type, int **status);
	bool hasTask(const char *filename, int type);
private:
#ifdef SIMPLE_TFTASKQUEUE
	Entry m_entry;
	bool m_hasData;
#else // SIMPLE_TFTASKQUEUE
	static const int M_MAX_ENTRY = 32;
	Entry m_entry[M_MAX_ENTRY];
	int m_entryCnt;
#endif // !SIMPLE_TFTASKQUEUE
};

class TftaskPool 
{
public:
	bool addTask(const char *filename, int type, int *status, int prioty) 
	{
		printf("TftaskPool::addTask(%d, {%s}, 0X%08x, %d)\n",
			type, filename, status, prioty);
		if (prioty < 0 || prioty >= QUEUE_COUNT) 
		{
			printf("Illegal prioty %d\n", prioty);
			return false;
		}
		return m_que[prioty].addTask(filename, type, status);
	};

	bool getTask(char *filename, int *type, int **status, int *prioty = NULL) 
	{
		for (int i=0; i<QUEUE_COUNT; ++i) 
		{
			if (m_que[i].getTask(filename, type, status)) 
			{
				if (prioty)
					*prioty = i;
				return true;
			}
		}
		return false;
	};

	bool hasTask(const char *filename, int type) 
	{
		for (int i=0; i<QUEUE_COUNT; ++i) 
		{
			if (m_que[i].hasTask(filename, type)) 
			{
				return true;
			}
		}
		return false;
	};
private:
	static const int QUEUE_COUNT = 2;
	TftaskQueue m_que[QUEUE_COUNT];
};

class FileTransServer: public event::rp::Thread, public IFileTransServer 
{
public:
	FileTransServer(): m_destport(0) 
	{
		m_destip[0] = '\0';
	};
public:
	bool start()
	{
		return event::rp::Thread::start();
	};
	void stop()
	{
		return event::rp::Thread::stop();
	};
	void setDest(const char *ip, int port) 
	{
		strcpy(m_destip, ip);
		m_destport = port;
	};
	bool addTask(const char *filename, int type, int *status = NULL, int prioty = 0) 
	{
		printf("FileTransServer::addTask(%d, {%s}, 0X%08x, %d)\n",
			type, filename, status, prioty);
		event::rp::Lock::Key key(&m_poolLock);
		key.open();
		if (status) 
		{
			*status = FTTASK_STATUS_WAIT;
		}
		return m_taskPool.addTask(filename, type, status, prioty);
	};
protected:
        virtual void *workFunc();
private:
	TftaskPool m_taskPool;
	event::rp::Lock m_poolLock;
	char m_destip[32];
	int m_destport;
};

#endif // !_UDPFT_FTSVR_H_
