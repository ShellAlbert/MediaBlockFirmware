/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LogoutResponse.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/08/07
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--LogoutResponse.h
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >

********************************************/
#ifndef LOGOUTRESPONSE_H
#define LOGOUTRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LogoutResponse
{
public:
	
	LogoutResponse();
	~LogoutResponse();
	
	/************************************************* 
    Function   ： FormatLogoutResponse()
    Description： format 'LogoutResponse' Auditorium Security Message
    Input      ： RequestId       :Request Message id of LogoutResponse
		          		esponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of LogoutResponse
		          		len             :length of LogoutResponse
    Return     ： error code, refer to Const.h
    Others     :
  *************************************************/
UInt32 FormatLogoutResponse(
		/*in */ UInt32  RequestId,
		/*in */ UInt8   ResponseStatus,
		/*out*/ UInt8  *NewResponseBuf,
		/*out*/ UInt32 *len);
		
  /************************************************* 
    Function   ： ParseLogoutResponse()
    Description： Parse 'LogoutResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of LogoutResponse
		          ResponseLen    :length of LogoutResponse	
    Output     ： RequestId,     :Request Message id of LogoutResponse
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
  *************************************************/
UInt32 ParseLogoutResponse(
		/*in */ UInt8  *ResponseBuf,
		/*in */ UInt32  ResponseLen,
		/*out*/ UInt32 *RequestId,
		/*out*/ UInt8  *ResponseStatus);
	
private:
	
	MessageLength    *MyMessageLength;        //消息头（KEY in KLV struct）类指针
	MessageULName    *MyMessageULName;        //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;     //消息ID类指针
};
#endif


