/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º CAuthentication.h
Author     £º tangquanfa@oristartech.com
Date       £º 2013/03/20
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef CAUTHENTICATION_H
#define CAUTHENTICATION_H

#include "tls/tlstranslateclient.h"

class CAuthentication
{
public:
	CAuthentication( CTLS_Translate_Client* pTLS );
	~CAuthentication();

	int LogIn( unsigned char* puserID,
			unsigned char* pusername,
			unsigned char* password,
			unsigned char* prole,
			unsigned char* prikeyfilename );

	int LogOut( unsigned char* puserID,
			unsigned char* prole,
			unsigned char* prikeyfilename );

private:
	CTLS_Translate_Client* mytls;
};

#endif
