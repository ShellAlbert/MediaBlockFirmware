/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º StartPlayResponse.h
Author     £º cuijixin@dadimedia.com
Date       £º 10/08/09
Version    £º v1.0
Description£º Auditorium Security Message(SMS<-SM)--StartPlayResponse
Others     :  
History    £º 
      < Author >    			< Date >             < Modification >
********************************************/
#ifndef STARTPLAYRESPONSE_H
#define STARTPLAYRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class StartPlayResponse
{
public:
	
	StartPlayResponse();
	~StartPlayResponse();
	
	/************************************************* 
    Function   £º FormatStartPlayResponse()
    Description£º format 'StartPlayResponse' Auditorium Security Message 
    Input      £º RequestId       :Request Message id of StartPlayRequest 
		              ResponseStatus  :General Response Elements
    Output     £º NewResponseBuf  :memory address of StartPlayResponse
		              len             :length of StartPlayResponse 
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
UInt32 FormatStartPlayResponse(
		/* in*/ UInt32  RequestId,
		/* in*/ UInt8   ResponseStatus,
		/*out*/ UInt8  *NewResponseBuf,
		/*out*/ UInt32 *len);
		
  /************************************************* 
    Function   £º ParseStartPlayResponse()
    Description£º Parse 'StartPlayResponse'Auditorium Security Message
    Input      £º ResponseBuf    :memory address of StartPlayResponse
		              ResponseLen    :length of StartPlayResponse
    Output     £º RequestId,     :Request Message id of StartPlayRequest
		              ResponseStatus :General Response Elements
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
UInt32 ParseStartPlayResponse(
		/* in*/ UInt8  *ResponseBuf,
		/* in*/ UInt32  ResponseLen,
		/*out*/ UInt32 *RequestId,
		/*out*/ UInt8  *ResponseStatus);
		
private:
	
	MessageLength    *MyMessageLength;			//message body length
	MessageULName    *MyMessageULName;			//message header
	MessageRequestId *MyMessageRequestId;		//message id
};

#endif


