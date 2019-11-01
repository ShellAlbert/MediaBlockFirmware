/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º getKeyMapRequest.h
Author     £º tangquanfa@oristartech.com
Date       £º 2014/01/08
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GET_KEYMAP_REQUEST_H
#define GET_KEYMAP_REQUEST_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatGetKeyMapRequest(	TEXT	*UserID,
								UInt8	*NewRequestBuf,
								UInt32	*BufLen );
UInt32 ParseGetKeyMapRequest(	UInt8	*RequestBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								TEXT	*UserID );

#ifdef __cplusplus
};

class getKeyMapRequest
{
public:

	getKeyMapRequest();
	~getKeyMapRequest();

    UInt32 FormatGetKeyMapRequest(
				/* in */ TEXT	*UserID,
				/* out*/ UInt8  *NewRequestBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseGetKeyMapRequest(
				/* in */ UInt8	*RequestBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ TEXT	*UserID );

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
