/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： AuditRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--AuditRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef AUDITREQUEST_H
#define AUDITREQUEST_H

#include "package/MessageLength.h"
#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class AuditRequest
{
public:

	AuditRequest();
	~AuditRequest();
	
	/************************************************* 
    Function   ： FormatAuditRequest()
    Description： format 'AuditRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	         
    Output     ： NewRequestBuf :memory address of AuditRequest
		          len           :the length of AuditRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatAuditRequest(
			/*in */ TEXT   *UserID,         //操作用户的用户证书指纹
			/*out*/ UInt8  *NewRequestBuf,  //接收组装好的AuditRequest请求消息的缓冲区地址
			/*out*/ UInt32 *len);           //组装好的AuditRequest请求消息长度

	/************************************************* 
    Function   ： ParseAuditRequest()
    Description： Parse 'AuditRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of AuditRequest
		          RequestLen    :the length of AuditRequest 		
    Output     ： RequestId,    :Request Message id of AuditRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseAuditRequest(
			/*in */ UInt8  *RequestBuf,     //接收到的请求消息的存储区地址
			/*in */ UInt32  RequestLen,     //接收到的请求消息长度
			/*out*/ UInt32 *RequestId,      //请求消息的消息ID
			/*out*/ TEXT   *UserID);        //发出请求消息的用户的证书指纹

private:
	MessageULName    *MyMessageULName;      //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;      //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;   //消息ID类指针
};

#endif


