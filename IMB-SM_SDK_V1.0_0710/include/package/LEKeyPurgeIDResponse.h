/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyPurgeIDResponse.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM<-PROj)--LEKeyPurgeIDResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYPURGEIDRESPONSE_H
#define LEKEYPURGEIDRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyPurgeIDResponse
{
public:
	LEKeyPurgeIDResponse();
	~LEKeyPurgeIDResponse();
	
    /************************************************* 
    Function   ： FormatLEKeyPurgeIDResponse()
    Description： format 'LEKeyPurgeIDResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of LEKeyPurgeIDRequest 
                  KeyIdStatus     :the status of key
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of LEKeyPurgeIDResponse
		          len             :the length of LEKeyPurgeIDResponse 
    Return     ： error code, refer to Const.h
    Others     :  A non-zero value for KeyIdStatus indicates that the indentified key 
                  to be purged was not present. the value of ResponseStatus for this
                  condition is 0.      
    *************************************************/ 
	UInt32 FormatLEKeyPurgeIDResponse(
		/* in */  UInt32  RequestId,      //对应 LEKeyPurgeIDRequest 请求消息的消息ID
		/* in */  UInt8   KeyIdStatus,    //链路解密密钥状态 
		/* in */  UInt8   ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h
		/* out*/  UInt8  *NewResponseBuf, //接收组装好的 LEKeyPurgeIDResponse 回复消息的缓冲区地址
		/* out*/  UInt32 *len);           //组装好的 LEKeyPurgeIDResponse 消息长度

    /************************************************* 
    Function   ： ParseLEKeyPurgeIDResponse()
    Description： Parse 'LEKeyPurgeIDResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of LEKeyPurgeIDResponse
		          ResponseLen    :the length of LEKeyPurgeIDResponse 		
    Output     ： RequestId,     :Request Message id of LEKeyPurgeIDRequest
                  KeyIdStatus    :the status of key
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyPurgeIDResponse(
		/* in*/  UInt8  *ResponseBuf,     //接收到的回复消息的存储区地址
		/* in*/  UInt32  ResponseLen,     //接收到的回复消息长度
		/*out*/  UInt32 *RequestId,       //对应 LEKeyPurgeIDRequest 请求消息的消息ID
		/*out*/  UInt8  *KeyStatus,       //链路解密密钥状态 
		/*out*/  UInt8  *ResponseStatus); //通用回复状态值，取值为0-3，具体解释参见Const.h

private:
	MessageULName    *MyMessageULName;    //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;    //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId; //消息ID类指针
};

#endif /* LEKEYPURGEIDRESPONSE_H*/



