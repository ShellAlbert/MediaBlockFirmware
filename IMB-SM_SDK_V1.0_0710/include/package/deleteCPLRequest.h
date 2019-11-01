/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   �� deleteCPLRequest.h
Author     �� tangquanfa@oristartech.com
Date       �� 2014/01/08
Version    �� v1.0
Description��
History    �� 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef DELETE_CPL_REQUEST_H
#define DELETE_CPL_REQUEST_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatDeleteCPLRequest(	TEXT	*UserID,
								TEXT	*CPLID,
								UInt8	*NewRequestBuf,
								UInt32	*BufLen );
UInt32 ParseDeleteCPLRequest(	UInt8	*RequestBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								TEXT	*UserID,
								TEXT	*CPLID );

#ifdef __cplusplus
};

class deleteCPLRequest
{
public:

	deleteCPLRequest();
	~deleteCPLRequest();

    UInt32 FormatDeleteCPLRequest(
				/* in */ TEXT	*UserID,
				/* in */ TEXT	*CPLID,
				/* out*/ UInt8  *NewRequestBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseDeleteCPLRequest(
				/* in */ UInt8	*RequestBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ TEXT	*UserID,
				/* out*/ TEXT	*CPLID );

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
