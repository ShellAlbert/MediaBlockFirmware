#ifndef _UDPFT_UDPFT_H_	
#define _UDPFT_UDPFT_H_	

#include <stdio.h>
#include "common/replant.h"
#include "udpft/iudpft.h"

class Bittbl;
class FileTransferSession: public IFileTransferSession, public event::rp::Thread {
public:
	static FileTransferSession *getInstance();
	FileTransferSession();
public:
	virtual bool transFile(int type, const char *filename, const char *destip, int port, bool *stopsig = NULL);
	virtual const char *getErrdesc() const;
public:
	virtual void setFiletype(int type);
	virtual void setFilename(const char *filename);
	virtual void setDestIP(const char *destip);
	virtual void setDestPort(int port);
	virtual bool startSession();
	virtual bool isBusy() const;
	virtual bool isOK() const;
	virtual bool setReTrans(bool flag);
protected:
	virtual void *workFunc();
private:
	bool ftCtrl();
private:
	friend class DataThread;
	char m_destip[64];
	int  m_destport;
	int  m_filetype;
	char m_filename[256];
	char m_errdesc[256];
	bool m_inSession;
	bool m_result;
	volatile bool m_reqbmp;

	int m_sockfd;
	FILE *m_fp;
	int m_filesize;
	int m_blocksize;
	int m_blockcount;
	
	Bittbl *m_bittbl;
};

#endif // !_UDPFT_UDPFT_H_	

