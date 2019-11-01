/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StartPlayResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/08/09
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--StartPlayResponse
Others     :  
History    �� 
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
    Function   �� FormatStartPlayResponse()
    Description�� format 'StartPlayResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of StartPlayRequest 
		              ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of StartPlayResponse
		              len             :length of StartPlayResponse 
    Return     �� error code, refer to Const.h
    Others     :        
  *************************************************/
UInt32 FormatStartPlayResponse(
		/* in*/ UInt32  RequestId,
		/* in*/ UInt8   ResponseStatus,
		/*out*/ UInt8  *NewResponseBuf,
		/*out*/ UInt32 *len);
		
  /************************************************* 
    Function   �� ParseStartPlayResponse()
    Description�� Parse 'StartPlayResponse'Auditorium Security Message
    Input      �� ResponseBuf    :memory address of StartPlayResponse
		              ResponseLen    :length of StartPlayResponse
    Output     �� RequestId,     :Request Message id of StartPlayRequest
		              ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
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


