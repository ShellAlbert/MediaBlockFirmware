/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º DeleteKDMResponse.h
Author     £º cuijixin@dadimedia.com
Date       £º 10/08/09
Version    £º v1.0
Description£º Auditorium Security Message(SMS<-SM)--DeleteKDMResponse
Others     :  
History    £º 
      < Author >    			< Date >             < Modification >

********************************************/
#ifndef DELETEKDMRESPONSE_H
#define DELETEKDMRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class DeleteKDMResponse
{
public:
	
	DeleteKDMResponse();
	~DeleteKDMResponse();
	
	/************************************************* 
    Function   £º FormatDeleteKDMResponse()
    Description£º format 'DeleteKDMResponse' Auditorium Security Message 
    Input      £º RequestId       :Request Message id of DeleteKDMRequest 
		              ResponseStatus  :General Response Elements
    Output     £º NewResponseBuf  :memory address of DeleteKDMResponse
		              len             :length of DeleteKDMResponse 
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/	
 	UInt32 FormatDeleteKDMResponse(
 		/* in*/ UInt32  RequestId,
		/* in*/ UInt8   ResponseStatus,
		/*out*/ UInt8  *NewResponseBuf,
		/*out*/ UInt32 *len);
		
  /************************************************* 
    Function   £º ParseDeleteKDMResponse()
    Description£º Parse 'DeleteKDMResponse'Auditorium Security Message
    Input      £º ResponseBuf    :memory address of DeleteKDMResponse
		              ResponseLen    :length of DeleteKDMResponse
    Output     £º RequestId,     :Request Message id of DeleteKDMRequest
		              ResponseStatus :General Response Elements
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 ParseDeleteKDMResponse(
  	/* in*/ UInt8  *ResponseBuf,
		/* in*/ UInt32  ResponseLen,
		/*out*/ UInt32 *RequestId,
		/*out*/ UInt8  *ResponseStatus);
		
private:
	
	MessageLength    *MyMessageLength;
	MessageULName    *MyMessageULName;
	MessageRequestId *MyMessageRequestId;
};

#endif


