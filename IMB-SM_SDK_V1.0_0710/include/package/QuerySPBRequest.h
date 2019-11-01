/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： QuerySPBRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROJ)--QuerySPBRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef QUERYSPBREQUEST_H
#define QUERYSPBREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class QuerySPBRequest
{
public:

	QuerySPBRequest();
	~QuerySPBRequest();
	
	/************************************************* 
    Function   ： FormatQuerySPBRequest()
    Description： format 'QuerySPBRequest' Auditorium Security Message 
    Input      ：         
    Output     ： NewRequestBuf :memory address of QuerySPBRequest
		          len           :length of QuerySPBRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatQuerySPBRequest(
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 QuerySPBRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 QuerySPBRequest 请求消息长度

 	/************************************************* 
    Function   ： ParseQuerySPBRequest()
    Description： Parse 'QuerySPBRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of QuerySPBRequest
		          RequestLen    :length of QuerySPBRequest 		
    Output     ： RequestId,    :Request Message id of QuerySPBRequest		         
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseQuerySPBRequest(
		/*in */ UInt8  *RequestBuf,    //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,    //接收到的请求消息长度
		/*out*/ UInt32 *RequestId);    //请求消息的消息ID

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针		
};
#endif


