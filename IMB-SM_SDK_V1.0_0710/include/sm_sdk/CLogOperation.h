/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   �� CLogOperation.h
Author     �� fubo@oristartech.com
Date       �� 2013/03/20
Version    �� v1.0
Description��
History    �� 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef CLOGOPERATION_H
#define CLOGOPERATION_H

#include "tls/tlstranslateclient.h"

class CLogOperation
{
public:
	CLogOperation( CTLS_Translate_Client* pTLS, char* ip, int port );
	~CLogOperation();

	int GetLog(/* in*/unsigned char* 	puserID,
		/* in*/unsigned int		StartTime,
		/* in*/unsigned int		StopTime );


private:
	CTLS_Translate_Client	*mytls;
	int						myport;
	char					myip[30];
	unsigned char			myfilename[100];
};

#endif
