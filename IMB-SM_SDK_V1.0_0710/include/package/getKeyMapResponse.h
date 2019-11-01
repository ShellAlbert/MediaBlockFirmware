/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º getKeyMapResponse.h
Author     £º tangquanfa@oristartech.com
Date       £º 2014/01/08
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GET_KEYMAP_RESPONSE_H
#define GET_KEYMAP_RESPONSE_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatGetKeyMapResponse(	UInt32	RequestId,
								UInt8	KeyMapNum,
								TEXT	*KeyMap,
								UInt8	Response,
								UInt8  *NewResponseBuf,
								UInt32 *BufLen  );
UInt32 ParseGetKeyMapResponse(	UInt8	*ResponseBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								UInt8	*KeyMapNum,
								TEXT	*KeyMap,
								UInt8	*Response );

#ifdef __cplusplus
};

class getKeyMapResponse
{
public:

	getKeyMapResponse();
	~getKeyMapResponse();

    UInt32 FormatGetKeyMapResponse(
				/* in */ UInt32	RequestId,
				/* in */ UInt8	KeyMapNum,
				/* in */ TEXT	*KeyMap,
				/* in */ UInt8	Response,
				/* out*/ UInt8  *NewResponseBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseGetKeyMapResponse(
				/* in */ UInt8	*ResponseBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ UInt8	*KeyMapNum,
				/* out*/ TEXT	*KeyMap,
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
