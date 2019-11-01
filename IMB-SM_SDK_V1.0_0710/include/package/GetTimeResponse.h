/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetTimeResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM<-PROJ)--GetTimeResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETTIMERESPONSE_H
#define GETTIMERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"
//typedef unsigned long long uint64;
class GetTimeResponse
{

public:

	GetTimeResponse();
	~GetTimeResponse();

    /************************************************* 
    Function   ： FormatGetTimeResponse()
    Description： format 'GetTimeResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of GetTimeRequest 
                  Time            :Responder's time
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of GetTimeResponse
		          len             :the length of GetTimeResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetTimeResponse(
		/*in */ UInt32  RequestId,      //对应 GetTimeRequest 请求消息的消息ID
		/*in */ UInt64  Time,           //放映机的时间快照
		/*in */ UInt8   ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h 
		/*out*/ UInt8  *NewResponseBuf, //接收组装好的 GetTimeResponse 回复消息的缓冲区地址
		/*out*/ UInt32 *len);           //组装好的 GetTimeResponse 消息长度

    /************************************************* 
    Function   ： ParseGetTimeResponse()
    Description： Parse 'GetTimeResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of GetTimeResponse
		          ResponseLen    :the length of GetTimeResponse 		
    Output     ： RequestId      :Request Message id of GetTimeRequest
                  Time           :Responder's time
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetTimeResponse(
		/*in */ UInt8  *ResponseBuf,    //接收到的回复消息的存储区地址
		/*in */ UInt32  ResponseLen,    //接收到的回复消息长度
		/*out*/ UInt32 *RequestId,      //对应 GetTimeRequest 请求消息的消息ID
		/*out*/ UInt64 *Time,           //放映机的时间快照
		/*out*/ UInt8  *ResponseStatus);//通用回复状态值，取值为0-3，具体解释参见Const.h 

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针

};


#endif
