/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetEventListRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROJ)--GetEventListRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETEVENTLISTREQUEST_H
#define GETEVENTLISTREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventListRequest
{

public:

	GetEventListRequest();
	~GetEventListRequest();
	
	/************************************************* 
    Function   ： FormatGetEventListRequest()
    Description： format 'GetEventListRequest' Auditorium Security Message 
    Input      ： StartTime     :Event list period start
                  EndTime       :Event list period stop
    Output     ： NewRequestBuf :memory address of GetEventListRequest
		          len           :the length of GetEventListRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventListRequest(
		/*in */ UInt32   StartTime,     //日志链表段的起始时间点
		/*in */ UInt32   EndTime,       //日志链表段的终止时间点
		/*out*/ UInt8   *NewRequestBuf, //接收组装好的 GetEventListRequest 请求消息的缓冲区地址
		/*out*/ UInt32  *len);          //组装好的 GetEventListRequest 请求消息长度
		
	/************************************************* 
    Function   ： ParseGetEventListRequest()
    Description： Parse 'GetEventListRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of GetEventListRequest
		          RequestLen    :the length of GetEventListRequest 		
    Output     ： RequestId,    :Request Message id of GetEventListRequest
		          StartTime     :Event list period start
                  EndTime       :Event list period stop
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetEventListRequest(
		/*in */ UInt8  *RequestBuf,     //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,     //接收到的请求消息长度
		/*out*/ UInt32 *RequestId,      //请求消息的消息ID
		/*out*/ UInt32 *StartTime,      //日志链表段的起始时间点
		/*out*/ UInt32 *EndTime);       //日志链表段的终止时间点

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	

};
#endif


