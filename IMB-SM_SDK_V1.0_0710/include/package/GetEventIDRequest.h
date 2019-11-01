/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetEventIDRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROJ)--GetEventIDRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/

#ifndef GETEVENTIDREQUEST_H
#define GETEVENTIDREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventIDRequest
{

public:

	GetEventIDRequest();
	~GetEventIDRequest();
	
	/************************************************* 
    Function   ： FormatGetEventIDRequest()
    Description： format 'GetEventIDRequest' Auditorium Security Message 
    Input      ： EventId       :ID of the requested event	         
    Output     ： NewRequestBuf :memory address of GetEventIDRequest
		          len           :the length of GetEventIDRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventIDRequest(
		/*in */ UInt32   EventId,       //事件ID
		/*out*/ UInt8   *NewRequestBuf, //接收组装好的 GetEventIDRequest 请求消息的缓冲区地址
		/*out*/ UInt32  *len);          //组装好的 GetEventIDRequest 请求消息长度

	/************************************************* 
    Function   ： ParseGetEventIDRequest()
    Description： Parse 'GetEventIDRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of GetEventIDRequest
		          RequestLen    :the length of GetEventIDRequest 		
    Output     ： RequestId,    :Request Message id of GetEventIDRequest
		          EventId       :ID of the requested event
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseGetEventIDRequest(
		/*in */ UInt8  *RequestBuf,     //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,     //接收到的请求消息长度
		/*out*/ UInt32 *RequestId,      //请求消息的消息ID
    	/*out*/	UInt32 *EventId);       //事件ID

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif


