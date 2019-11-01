#ifndef _UDPFT_IUDPFT_H_	
#define _UDPFT_IUDPFT_H_	

class IFileTransferSession 
{
public:
	static IFileTransferSession *getInterface();
public:
	virtual bool transFile(int type, const char *filename, const char *destip, int port, bool *stopsig = NULL) = 0;
	virtual const char *getErrdesc() const = 0;
public:
	virtual void setFiletype(int type) = 0;
	virtual void setFilename(const char *filename) = 0;
	virtual void setDestIP(const char *destip) = 0;
	virtual void setDestPort(int port) = 0;
	virtual bool startSession() = 0;
	virtual bool isBusy() const = 0;
	virtual bool isOK() const = 0;
	virtual bool setReTrans(bool flag) = 0;
};

#define FTTASK_STATUS_WAIT 	(0)
#define FTTASK_STATUS_WORKING	(1)
#define FTTASK_STATUS_SUCCESS	(2)
#define FTTASK_STATUS_FAIL	(3)

class IFileTransServer 
{
public:
	static IFileTransServer *getInterface();
public:
	virtual bool start() = 0;
	virtual void stop() = 0;
	virtual void setDest(const char *ip, int port) = 0;
	virtual bool addTask(const char *filename, int type, int *status = NULL, int prioty = 0) = 0;
	
};

#endif // !_UDPFT_IUDPFT_H_

