/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   �� getCplListResponse.h
Author     �� tangquanfa@oristartech.com
Date       �� 2014/01/08
Version    �� v1.0
Description��
History    �� 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GET_CPLLIST_RESPONSE_H
#define GET_CPLLIST_RESPONSE_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatGetCplListResponse(	UInt32	RequestId,
								UInt8	CPLNum,
								TEXT	*CPLList,
								UInt8	Response,
								UInt8  *NewResponseBuf,
								UInt32 *BufLen  );
UInt32 ParseGetCplListResponse(	UInt8	*ResponseBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								UInt8	*CPLNum,
								TEXT	*CPLList,
								UInt8	*Response );

#ifdef __cplusplus
};

class getCplListResponse
{
public:

	getCplListResponse();
	~getCplListResponse();

    UInt32 FormatGetCplListResponse(
				/* in */ UInt32	RequestId,
				/* in */ UInt8	CPLNum,
				/* in */ TEXT	*CPLList,
				/* in */ UInt8	Response,
				/* out*/ UInt8  *NewResponseBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseGetCplListResponse(
				/* in */ UInt8	*ResponseBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ UInt8	*CPLNum,
				/* out*/ TEXT	*CPLList,
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
