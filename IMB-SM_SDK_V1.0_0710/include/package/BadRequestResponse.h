/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： BadRequestResponse.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM  SM<-PROJ)--BadRequestResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef BADREQUESTRESPONSE_H
#define BADREQUESTRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class BadRequestResponse
{
public:
	BadRequestResponse();
	~BadRequestResponse();

	/************************************************* 
    Function   ： FormatBadRequestResponse()
    Description： format 'BadRequestResponse' Auditorium Security Message 
    Input      ： BadRequest       :copy of Request 
                  BadRequestLength :the length of Bad Request
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of BadRequestResponse
		          len             :the length of BadRequestResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	int FormatBadRequestResponse(
			/*in */ UInt8   *BadRequest,       //存储错误的请求消息缓冲区地址
			/*in */ UInt32   BadRequestLength, //错误的请求消息长度
			/*in */ UInt8    ResponseStatus,   //通用回复状态值，取值为0-3，具体解释参见Const.h
			/*out*/ UInt8   *NewResponseBuf,   //接收组装好的 BadRequestResponse 请求消息的缓冲区地址
			/*out*/ UInt32  *len);             //组装好的 BadRequestResponse 请求消息长度
			
	/************************************************* 
    Function   ： ParseBadRequestResponse()
    Description： Parse 'BadRequestResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of BadRequestResponse
		          ResponseLen    :the length of BadRequestResponse 		
    Output     ： BadRequest,    :copy of Request 
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	int ParseBadRequestResponse(
			/*in */ UInt8   *ResponseBuf,      //接收到的回复消息的存储区地址
			/*in */ UInt32   ResponseLen,      //接收到的回复消息长度
			/*out*/ UInt8   *BadRequest,       //接收错误的请求消息缓冲区地址
			/*out*/ UInt32  *ResponseStatus);  //通用回复状态值，取值为0-3，具体解释参见Const.h

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针
};

#endif


