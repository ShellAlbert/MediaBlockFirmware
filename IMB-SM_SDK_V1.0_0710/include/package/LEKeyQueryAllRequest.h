/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyQueryAllRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROj)--LEKeyQueryAllRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYALLREQUEST_H
#define LEKEYQUERYALLREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryAllRequest
{
public:
	LEKeyQueryAllRequest();
	~LEKeyQueryAllRequest();
	
	/************************************************* 
    Function   ： FormatLEKeyQueryAllRequest()
    Description： format 'LEKeyQueryAllRequest' Auditorium Security Message 
    Input      ：        
    Output     ： NewRequestBuf :memory address of LEKeyQueryAllRequest
		          len           :the length of LEKeyQueryAllRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatLEKeyQueryAllRequest(
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 LEKeyQueryAllRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 LEKeyQueryAllRequest 请求消息长度

	/************************************************* 
    Function   ： ParseLEKeyQueryAllRequest()
    Description： Parse 'LEKeyQueryAllRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of LEKeyQueryAllRequest
		          RequestLen    :the length of LEKeyQueryAllRequest 		
    Output     ： RequestId,    :Request Message id of LEKeyQueryAllRequest		       
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseLEKeyQueryAllRequest(
		/* in*/ UInt8  *RequestBuf,    //接收到的请求消息的存储区地址
		/* in*/	UInt32  RequestLen,    //接收到的请求消息长度
		/*out*/ UInt32 *RequestId);    //请求消息的消息ID

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* LEKEYQUERYALLREQUEST_H */




