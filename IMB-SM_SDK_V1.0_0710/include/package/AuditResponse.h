/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： AuditResponse.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--AuditResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef AUDITRESPONSE_H
#define AUDITRESPONSE_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"

class AuditResponse
{
public:

	AuditResponse();
	~AuditResponse();

    /************************************************* 
    Function   ： FormatAuditResponse()
    Description： format 'AuditResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of AuditRequest 
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of AuditResponse
		          len             :the length of AuditResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatAuditResponse(
		/*in */ UInt32  RequestId,          //对应AuditRequest请求消息的消息ID
		/*in */ UInt8   ResponseStatus,     //通用回复状态值，取值为0-3，具体解释参见Const.h
		/*out*/ UInt8  *NewResponseBuf,     //接收组装好的AuditResponse回复消息的缓冲区地址
		/*out*/ UInt32 *len);               //组装好的AuditResponse消息长度

    /************************************************* 
    Function   ： FormatAuditResponse()
    Description： Parse 'AuditResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of AuditResponse
		          ResponseLen    :length of AuditResponse 		
    Output     ： RequestId,     :Request Message id of AuditRequest
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseAuditResponse(
		/*in */ UInt8  *ResponseBuf,        //接收到的回复消息的存储区地址
		/*in */ UInt32  ResponseLen,        //接收到的回复消息长度
		/*out*/ UInt32 *RequestId,          //对应AuditRequest请求消息的消息ID
		/*out*/ UInt8  *ResponseStatus);    //通用回复状态值，取值为0-3，具体解释参见Const.h

private:

	MessageLength    *MyMessageLength;      //消息头（KEY in KLV struct）类指针
	MessageULName    *MyMessageULName;      //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;   //消息ID类指针
};

#endif


