#ifndef _UDPFT_DATA_H_
#define _UDPFT_DATA_H_
//	udpft/data.h
//	2010-09-13 by ShanLanshan
//	thread to send data
#include "common/replant.h"

class FileTransferSession;
class DataThread: public event::rp::Thread 
{
public:
	DataThread(FileTransferSession *s);
protected:
        virtual void *workFunc();
private:
	FileTransferSession *m_ftSession;
};

#endif // !_UDPFT_DATA_H_
