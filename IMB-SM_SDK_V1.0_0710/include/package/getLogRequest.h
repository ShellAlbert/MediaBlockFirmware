/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º getLogRequest.h
Author     £º tangquanfa@oristartech.com
Date       £º 2013/02/1
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GET_LOG_REQUEST_H
#define GET_LOG_REQUEST_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

const UInt8 SYSLOG  = 0x00;
const UInt8 SECULOG = 0x01;
const UInt8 PROJLOG = 0x02;

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatGetLogRequest(	TEXT	*UserID,
									UInt8	LogType,
									UInt64	Starttime,
									UInt64	Endtime,
									TEXT	*IPAddress,
									TEXT	*Port,
									UInt8  *NewRequestBuf,
									UInt32 *BufLen ); 
UInt32 ParseGetLogRequest(	UInt8	*RequestBuf,
									UInt32	BufLen,
									UInt32	*RequestId,
									TEXT	*UserID,
									UInt8	*LogType,
									UInt64	*Starttime,
									UInt64	*Endtime,
									TEXT	*IPAddress,
									TEXT	*Port );

#ifdef __cplusplus
};

class getLogRequest
{
public:

	getLogRequest();
	~getLogRequest();

    UInt32 FormatGetLogRequest(
				/* in */ TEXT	*UserID,
				/* in */ UInt8	LogType,
				/* in */ UInt64	Starttime,
				/* in */ UInt64	Endtime,
				/* in */ TEXT	*IPAddress,
				/* in */ TEXT	*Port,
				/* out*/ UInt8  *NewRequestBuf,
				/* out*/ UInt32 *BufLen );    

    UInt32 ParseGetLogRequest(
				/* in */ UInt8	*RequestBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ TEXT	*UserID,
				/* out*/ UInt8	*LogType,
				/* out*/ UInt64	*Starttime,
				/* out*/ UInt64	*Endtime,
				/* out*/ TEXT	*IPAddress,
				/* out*/ TEXT	*Port );       

	void UInt64_UInt8( UInt64 Len, UInt8 *Buf );
	UInt64 UInt8_UInt64( UInt8 *Buf );
/*
	void float_UInt8( float Float, UInt8 *Buf );
	float UInt8_float( UInt8 *Buf );
	UInt32 UInt32_UInt8( UInt32 Len, UInt8 *Buf );
	UInt32 UInt8_UInt32( UInt8 *Buf );
	UInt16 UInt16_UInt8( UInt16 Len, UInt8 *Buf );
	UInt16 UInt8_UInt16( UInt8 *Buf );
*/

private:

	klvKey		*pklvKey;      //klvKey pointer
	klvLen		*pklvLen;      //klvLen pointer
	requestId	*prequestId;   //requestId pointer
};
#endif

#endif
