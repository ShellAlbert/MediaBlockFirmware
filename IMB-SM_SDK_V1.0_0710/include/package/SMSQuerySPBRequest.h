/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： SMSQuerySPBRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--SMSQuerySPBRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef SMSQUERYSPBREQUEST_H
#define SMSQUERYSPBREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class SMSQuerySPBRequest
{
public:

	SMSQuerySPBRequest();
	~SMSQuerySPBRequest();
	
	/************************************************* 
    Function   ： FormatSMSQuerySPBRequest()
    Description： format 'SMSQuerySPBRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	      
    Output     ： NewRequestBuf :memory address of SMSQuerySPBRequest
		          len           :length of SMSQuerySPBRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSMSQuerySPBRequest(
	    /*in */ TEXT   *UserID,        //Certificate Thumbprint of uesr	
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 SMSQuerySPBRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 SMSQuerySPBRequest 请求消息长度

 	/* ************************************************ 
    Function   ： ParseSMSQuerySPBRequest()
    Description： Parse 'SMSQuerySPBRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of SMSQuerySPBRequest
		          RequestLen    :length of SMSQuerySPBRequest 		
    Output     ： RequestId,    :Request Message id of SMSQuerySPBRequest	
    	          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    ************************************************ */ 
	UInt32 ParseSMSQuerySPBRequest(
		/*in */ UInt8  *RequestBuf,    //接收到的请求消息的存储区地址
		/*in */ UInt32  RequestLen,    //接收到的请求消息长度
		/*out*/ UInt32 *RequestId,     //请求消息的消息ID
		/*out*/ TEXT   *UserID);    

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针		
};
#endif


