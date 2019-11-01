/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetTimeRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROJ)--GetTimeRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETTIMEREQUEST_H
#define GETTIMEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetTimeRequest
{

public:

	GetTimeRequest();
	~GetTimeRequest();

	/************************************************* 
    Function   ： FormatGetTimeRequest()
    Description： format 'GetTimeRequest' Auditorium Security Message 
    Input      ：         
    Output     ： NewRequestBuf :memory address of GetTimeRequest
		          len           :the length of GetTimeRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatGetTimeRequest(
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 GetTimeRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 GetTimeRequest 请求消息长度
		
	/************************************************* 
    Function   ： ParseGetTimeRequest()
    Description： Parse 'AuditRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of GetTimeRequest
		          RequestLen    :the length of GetTimeRequest 		
    Output     ： RequestId,    :Request Message id of GetTimeRequest		          
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetTimeRequest(
		/*in */ UInt8  *RequestBuf,    //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,    //接收到的请求消息长度
		/*out*/ UInt32 *RequestId);    //请求消息的消息ID
private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针

};
#endif


