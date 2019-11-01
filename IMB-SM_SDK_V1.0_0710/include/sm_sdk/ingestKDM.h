/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º ingestKDM.h
Author     £º tangquanfa@oristartech.com
Date       £º 2013/06/04
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef INGEST_KDM_H
#define INGEST_KDM_H

#include "tls/tlstranslateclient.h"

class ingestKDM
{
public:
	ingestKDM( CTLS_Translate_Client* pTLS );
	~ingestKDM();

	int ingest(/* in*/unsigned char* 	puserID,
		/* in*/unsigned int		KDMContent_len,
		/* in*/unsigned char*	KDMContent );


private:
	CTLS_Translate_Client	*mytls;
};

#endif
