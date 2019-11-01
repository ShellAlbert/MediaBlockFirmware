/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： StopSuiteRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message (SMS->SM)--StopSuiteRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STOPSUITEREQUEST_H
#define STOPSUITEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

class StopSuiteRequest
{
public:
	StopSuiteRequest();
	~StopSuiteRequest();

	/************************************************* 
    Function   ： FormatStopSuiteRequest()
    Description： format 'StopSuiteRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	         
    Output     ： NewRequestBuf :memory address of StopSuiteRequest
		          len           :length of StopSuiteRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 	
	UInt32 FormatStopSuiteRequest(	
		/* in*/ TEXT   *UserID,       //操作用户的用户证书指纹
		/*out*/ UInt8  *NewRequestBuf,//接收组装好的 StopSuiteRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);         //组装好的 StopSuiteRequest 请求消息长度

	
	/************************************************* 
    Function   ： ParseAuditRequest()
    Description： Parse 'StopSuiteRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of StopSuiteRequest
		          RequestLen    :length of StopSuiteRequest 		
    Output     ： RequestId,    :Request Message id of StopSuiteRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
		UInt32 ParseStopSuiteRequest(
		/*in */ UInt8  *RequestBuf,   //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,   //接收到的请求消息长度
		/*out*/ TEXT   *UserID,       //操作用户的用户证书指纹
		/*out*/ UInt32 *RequestId);   //发出请求消息的用户的证书指纹
		
private:

	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针
};

#endif /* STARTSUITEREQUEST_H */
 

