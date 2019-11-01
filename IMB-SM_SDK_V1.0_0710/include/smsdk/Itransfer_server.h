#ifndef __ITRANSFER_SERVER_H__
#define __ITRANSFER_SERVER_H__

class ITransferServer
{
public:
    ITransferServer(void){};
    ~ITransferServer(void){};
    virtual int Initialize(char* inLocalIP, unsigned int inLocalPort) = 0;
};

#endif

