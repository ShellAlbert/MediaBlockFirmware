/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º CLogOperation.h
Author     £º fubo@oristartech.com
Date       £º 2013/03/20
Version    £º v1.0
Description£º
History    £º 
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
