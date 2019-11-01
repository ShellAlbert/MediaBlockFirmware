/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º GetCertChainResponse.h
Author     £º cuijixin@dadimedia.com
Date       £º 10/10/09
Version    £º v1.0
Description£º Auditorium Security Message(SMS->SM)--GetCertChainResponse
Others     :  
History    £º 
< Author >    			< Date >             < Modification >

********************************************/
#ifndef GETCERTCHAINRESPONSE_H
#define GETCERTCHAINRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

typedef struct CertInfo
{
	int    CertNameLength;	// certificate name length
	char  *pCertName;		// certificate name
	int    CertLength;		// certificate content length
	char  *pCertValue;		// certificate content 
	struct CertInfo* pNext;	// next node 
}CERTINFONODE;


class GetCertChainResponse
{
public:
	GetCertChainResponse();
	~GetCertChainResponse();

	/*****************************************************
	Function   :  ParseBufToLen()
	Description:  transform the message saved in memory to integer
	Input      :  Buf     : memory address of message
	              BufLen  : the length of message memory
	Output     :  
	Return     :  integer match along with message saved in memory
	Others     :
	*****************************************************/
	UInt64 ParseBufToLen(
		/* in*/UInt8 *Buf,
		/* in*/UInt32 BufLen);

	/*****************************************************
	Function   :  ParseLenToBuf()
	Description:  transform integer to the message saved in memory
	Input      :  IntNum  : integer want to transform 
				  BufLen  :the length of message 	memory
	Output     :  Buf     : memory address of message
	Return     :  error code, refer to Const.h
	Others     :
	*****************************************************/
	UInt64 ParseLenToBuf(
		/* in*/UInt32 IntNum,
		/* in*/UInt32  BufLen,
		/*out*/UInt8 *Buf);

	/*****************************************************
	Function   :  FormatGetCertChainResponse()
	Description:  format 'GetCertChainResponse' Auditorium Security Message
	Input      :  RequestId     :Request Message id of GetCertChainResponse
	              CertType      :Certificate type
				  ResponseStatus:General Response Elements
	Output     :  NewResponseBuf:memory address of GetCertChainResponse
	              len           :length of GetCertChainResponse
	Return     :  error code, refer to Const.h
	Others     :
	*****************************************************/
	UInt32 FormatGetCertChainResponse(
		/* in*/UInt32 RequestId,
//		/* in*/UInt32 CertType,
		/* in*/UInt8  ResponseStatus,
		/*out*/UInt8 *NewResponseBuf,
		/*out*/UInt32 *len);

	/************************************************* 
	Function   £º ParseGetCertChainResponse()
	Description£º Parse 'GetCertChainResponse'Auditorium Security Message 
	Input      :  RequestBuf    :memory address of GetCertChainResponse
	              RequestLen    :length of GetCertChainResponse	
	Output     £º RequestId     :Request Message id of GetCertChainResponse
	              CertType      :Certificate type
	              ResponseStatus:General Response Elements
				  head          :the head of Certificate list
	Return     £º error code, refer to Const.h
	Others     :        
	*************************************************/ 
	UInt32 ParseGetCertChainResponse(
		/* in*/UInt8 *ResponseBuf,
		/* in*/UInt32 ResponseLen,
		/*out*/UInt32 *RequestId,
//		/*out*/UInt32 *CertType,
		/*out*/UInt8 *ResponseStatus,
		/*out*/CERTINFONODE **head);

	/************************************************* 
	Function   £º AddCertInfo()
	Description£º add new certificate information to certificate list
	Input      £º CertNameLen   :the length of certificate name	
	              CertName      :certificate name	
	              CertContentLen:the length of certificate content
	              CertContent   :certificate content
	Output     £º none
	Return     £º error code, refer to Const.h
	Others     :        
	*************************************************/            
	UInt32 AddCertInfo(
		/* in*/UInt32     CertNameLen, 
		/* in*/TEXT      *CertName,
		/* in*/UInt32     CertContentLen,
		/* in*/TEXT      *CertContent);

	/************************************************* 
	Function   £º GetCertInfo()
	Description£º get certificate information from certificate list
	Input      £º OCertListHead :the head of certificate list	         	 
	Output     £º CertNameLen   :the length of certificate name	
	              CertName      :certificate name	
	              CertContentLen:the length of certificate content
	              CertContent   :certificate content
	Return     £º error code, refer to Const.h
	Others     :        
	*************************************************/           
	UInt32 GetCertInfo(
		/* in*/CERTINFONODE **OCertListHead,  
		/*out*/UInt32    *CertNameLen, 
		/*out*/TEXT      *CertName,
		/*out*/UInt32    *CertContentLen,
		/*out*/TEXT      *CertContent);

	void  ClearCertInfo();

private:
  CERTINFONODE     *m_CertListHead;     
	int               m_CertListLen;
	MessageLength    *MyMessageLength;
	MessageULName    *MyMessageULName;
	MessageRequestId *MyMessageRequestId;
};

#endif


