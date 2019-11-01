/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName	:
FileName	:	sendfilerequest.h
Author		:	tangquanfa@oristartech.com
Date		:	2012/03/28
Version		:	1.0
Description
History 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GETFILE_REQUEST_H
#define GETFILE_REQUEST_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 formatgetfilerequest( UInt8 filenamelen, TEXT *filename, UInt8 *requestbuf, UInt8 *buflen );
UInt32 parsegetfilerequest( UInt8 *requestbuf, UInt8 buflen, UInt8 *filenamelen, TEXT *filename );

#ifdef __cplusplus
};

class getfilerequest
{
public:
	getfilerequest();
	~getfilerequest();

    UInt32 formatgetfilerequest(
				/* in */ UInt8	filenamelen,
				/* in */ TEXT	*filename,
				/* out*/ UInt8  *requestbuf,
				/* out*/ UInt8  *buflen );

    UInt32 parsegetfilerequest(
				/* in */ UInt8	*requestbuf,
				/* in */ UInt8	buflen,
				/* out*/ UInt8	*filenamelen,
				/* out*/ TEXT	*filename );


//	UInt32 UInt64_UInt8( /* in */ UInt64 len, /* out*/ UInt8 *lenbuf );
//	UInt64 UInt8_UInt64( /*in*/ UInt8 *lenbuf );

private:
	klvKey    *pklvKey;
	klvLen    *pklvLen;
};
#endif

#endif
