/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName	:
FileName	:	sendfileresponse.h
Author		:	tangquanfa@oristartech.com
Date		:	2012/03/28
Version		:	1.0
Description
History 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GETFILE_RESPONSE_H
#define GETFILE_RESPONSE_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 formatgetfileresponse( UInt64 offset, UInt8 *buf, UInt8 *buflen );
UInt32 parsegetfileresponse( UInt8 *buf, UInt8 buflen, UInt64	*offset );

#ifdef __cplusplus
};

class getfileresponse
{
public:
	getfileresponse();
	~getfileresponse();

	UInt32 formatgetfileresponse(
		/*in */ UInt64	filesize,
		/*out*/ UInt8	*buf,
		/*out*/ UInt8	*buflen );

	UInt32 parsegetfileresponse(
		/*in */ UInt8	*buf,
		/*in */ UInt8	buflen,
		/*out*/ UInt64	*filesize );

	UInt32 UInt64_UInt8( /* in */ UInt64 len,/* out*/ UInt8 *lenbuf );
	UInt64 UInt8_UInt64( /*in*/ UInt8 *lenbuf );

//	UInt32 UInt32_UInt8( /* in */ UInt32 len, /* out*/ UInt8 *lenbuf );
//	UInt32 UInt8_UInt32( /*in*/ UInt8 *lenbuf );

private:
	klvKey    *pklvKey;
	klvLen    *pklvLen;
};
#endif

#endif
