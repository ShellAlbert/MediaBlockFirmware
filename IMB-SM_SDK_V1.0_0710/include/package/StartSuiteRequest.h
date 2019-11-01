/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： StartSuiteRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--StartSuiteRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STARTSUITEREQUEST_H
#define STARTSUITEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

class StartSuiteRequest
{
public:
	StartSuiteRequest();
	~StartSuiteRequest();

	/************************************************* 
    Function   ： FormatStartSuiteRequest()
    Description： format 'StartSuiteRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	         
    Output     ： NewRequestBuf :memory address of StartSuiteRequest
		          len           :length of StartSuiteRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStartSuiteRequest(	
		/* in*/ TEXT   *UserID,        //操作用户的用户证书指纹
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 StartSuiteRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 StartSuiteRequest 请求消息长度
		
	/************************************************* 
    Function   ： ParseStartSuiteRequest()
    Description： Parse 'StartSuiteRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of StartSuiteRequest
		          RequestLen    :length of StartSuiteRequest 		
    Output     ： RequestId,    :Request Message id of StartSuiteRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseStartSuiteRequest(
		/*in */ UInt8  *RequestBuf,   //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,   //接收到的请求消息长度
		/*out*/ TEXT   *UserID,       //操作用户的用户证书指纹
		/*out*/ UInt32 *RequestId);   //请求消息的消息ID

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* STARTSUITEREQUEST_H */


