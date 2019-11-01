/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetEventIDResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM<-PROJ)--GetEventIDResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETEVENTIDRESPONSE_H
#define GETEVENTIDRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventIDResponse
{
public:

	GetEventIDResponse();
	~GetEventIDResponse();

    /************************************************* 
    Function   ： FormatGetEventIDResponse()
    Description： format 'GetEventIDResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of GetEventIDRequest 
                  LogRecord       :Record being delivered
                  LogRecordLen    :the length of Record 
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of GetEventIDResponse
		          len             :the length of GetEventIDResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventIDResponse(
		/*in */ UInt32   RequestId,      //对应 GetEventIDRequest 请求消息的消息ID
		/*in */ TEXT    *LogRecord,      //日志信息
		/*in */ UInt32   LogRecordLen,   //日志信息长度
		/*in */ UInt8    ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h 
		/*out*/ UInt8   *NewResponseBuf, //接收组装好的 GetEventIDResponse 回复消息的缓冲区地址
		/*out*/ UInt32  *len);           //组装好的 GetEventIDResponse 消息长度

    /************************************************* 
    Function   ： ParseGetEventIDResponse()
    Description： Parse 'GetEventIDResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of GetEventIDResponse
		          ResponseLen    :the length of GetEventIDResponse 		
    Output     ： RequestId,     :Request Message id of GetEventIDRequest
                  LogRecord      :Record being delivered
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetEventIDResponse(
		/*in */ UInt8  *ResponseBuf,     //接收到的回复消息的存储区地址
		/*in */ UInt32  ResponseLen,     //接收到的回复消息长度
		/*out*/ UInt32 *RequestId,       //对应 GetEventIDRequest 请求消息的消息ID
		/*out*/ TEXT   *LogRecord,       //日志信息
		/*out*/ UInt8  *ResponseStatus); //通用回复状态值，取值为0-3，具体解释参见Const.h 

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	

};


#endif
