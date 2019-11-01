/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： ClearCSPsRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 11/08/01
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--ClearCSPsRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >  
********************************************/
#ifndef CLEARCSPSREQUEST_H
#define CLEARCSPSREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

class ClearCSPsRequest
{
public:
	ClearCSPsRequest();
	~ClearCSPsRequest();

	/************************************************* 
    Function   ： FormatClearCSPsRequest()
    Description： format 'ClearCSPsRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	         
    Output     ： NewRequestBuf :memory address of ClearCSPsRequest
		          len           :length of ClearCSPsRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatClearCSPsRequest(	
		/* in*/ TEXT   *UserID,        //操作用户的用户证书指纹
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 ClearCSPsRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 ClearCSPsRequest 请求消息长度
		
	/************************************************* 
    Function   ： ParseClearCSPsRequest()
    Description： Parse 'ClearCSPsRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of ClearCSPsRequest
		          RequestLen    :length of ClearCSPsRequest 		
    Output     ： RequestId,    :Request Message id of ClearCSPsRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseClearCSPsRequest(
		/*in */ UInt8  *RequestBuf,   //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,   //接收到的请求消息长度
		/*out*/ TEXT   *UserID,       //操作用户的用户证书指纹
		/*out*/ UInt32 *RequestId);   //请求消息的消息ID

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* CLEARCSPSREQUEST_H */


