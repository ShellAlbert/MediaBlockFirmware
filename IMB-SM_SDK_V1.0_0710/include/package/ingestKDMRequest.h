/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º ingestKDMRequest.h
Author     £º tangquanfa@oristartech.com
Date       £º 2013/06/04
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef INGEST_KDM_REQUEST_H
#define INGEST_KDM_REQUEST_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatIngestKDMRequest(	TEXT	*UserID,
								UInt32	KDMContent_len,
								TEXT	*KDMContent,
								UInt8	*NewRequestBuf,
								UInt32	*BufLen );
UInt32 ParseIngestKDMRequest(	UInt8	*RequestBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								TEXT	*UserID,
								UInt32	*KDMContent_len,
								TEXT	*KDMContent );

#ifdef __cplusplus
};

class ingestKDMRequest
{
public:

	ingestKDMRequest();
	~ingestKDMRequest();

    UInt32 FormatIngestKDMRequest(
				/* in */ TEXT	*UserID,
				/* in */ UInt32	KDMContent_len,
				/* in */ TEXT	*KDMContent,
				/* out*/ UInt8  *NewRequestBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseIngestKDMRequest(
				/* in */ UInt8	*RequestBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ TEXT	*UserID,
				/* out*/ UInt32	*KDMContent_len,
				/* out*/ TEXT	*KDMContent );

//	void float_UInt8( float Float, UInt8 *Buf );
//	float UInt8_float( UInt8 *Buf );

	UInt32 UInt32_UInt8( UInt32 Len, UInt8 *Buf );
	UInt32 UInt8_UInt32( UInt8 *Buf );
//	UInt16 UInt16_UInt8( UInt16 Len, UInt8 *Buf );
//	UInt16 UInt8_UInt16( UInt8 *Buf );

private:

	klvKey		*pklvKey;      //klvKey pointer
	klvLen		*pklvLen;      //klvLen pointer
	requestId	*prequestId;   //requestId pointer
};
#endif

#endif
