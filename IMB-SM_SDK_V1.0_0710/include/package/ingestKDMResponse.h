/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º ingestKDMResponse.h
Author     £º tangquanfa@oristartech.com
Date       £º 2013/06/04
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef INGEST_KDM_RESPONSE_H
#define INGEST_KDM_RESPONSE_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatIngestKDMResponse(	UInt32	RequestId,
								UInt32	ErrorCode,
								UInt8	Response,
								UInt8  *NewResponseBuf,
								UInt32 *BufLen  );
UInt32 ParseIngestKDMResponse(	UInt8	*ResponseBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								UInt32	*ErrorCode,
								UInt8	*Response );

#ifdef __cplusplus
};

class ingestKDMResponse
{
public:

	ingestKDMResponse();
	~ingestKDMResponse();

    UInt32 FormatIngestKDMResponse(
				/* in */ UInt32	RequestId,
				/* in */ UInt32	ErrorCode,
				/* in */ UInt8	Response,
				/* out*/ UInt8  *NewResponseBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseIngestKDMResponse(
				/* in */ UInt8	*ResponseBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ UInt32	*ErrorCode,
				/* out*/ UInt8	*Response );


	UInt32 UInt32_UInt8( UInt32 CertLen, UInt8 *LenBuf );
	UInt32 UInt8_UInt32( UInt8 *LenBuf );
/*
	UInt16 UInt16_UInt8( UInt16 CertLen, UInt8 *LenBuf );
	UInt16 UInt8_UInt16( UInt8 *LenBuf );
*/
private:

	klvKey		*pklvKey;      //klvKey pointer
	klvLen		*pklvLen;      //klvLen pointer
	requestId	*prequestId;   //requestId pointer
};
#endif

#endif
