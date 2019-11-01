/********************************************* 
Copyright (C), 2013-2020, oristartech Co., Ltd.
ModuleName :
FileName   �� getCertificateResponse.h
Author     �� tangquanfa@oristartech.com
Date       �� 2014/01/08
Version    �� v1.0
Description��
History    �� 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef GET_CERTIFICATE_RESPONSE_H
#define GET_CERTIFICATE_RESPONSE_H

#include "Const.h"
#include "klvKey.h"
#include "klvLen.h"

#include "requestId.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 FormatGetCertificateResponse(	UInt32	RequestId,
								UInt32	CertLength,
								TEXT	*CertContent,
								UInt8	Response,
								UInt8  *NewResponseBuf,
								UInt32 *BufLen  );
UInt32 ParseGetCertificateResponse(	UInt8	*ResponseBuf,
								UInt32	BufLen,
								UInt32	*RequestId,
								UInt32	*CertLength,
								TEXT	*CertContent,
								UInt8	*Response );

#ifdef __cplusplus
};

class getCertificateResponse
{
public:

	getCertificateResponse();
	~getCertificateResponse();

    UInt32 FormatGetCertificateResponse(
				/* in */ UInt32	RequestId,
				/* in */ UInt32	CertLength,
				/* in */ TEXT	*CertContent,
				/* in */ UInt8	Response,
				/* out*/ UInt8  *NewResponseBuf,
				/* out*/ UInt32 *BufLen );

    UInt32 ParseGetCertificateResponse(
				/* in */ UInt8	*ResponseBuf,
				/* in */ UInt32	BufLen,
				/* out*/ UInt32	*RequestId,
				/* out*/ UInt32	*CertLength,
				/* out*/ TEXT	*CertContent,
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
