/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyPurgeIDRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROj)--LEKeyPurgeIDRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYPURGEIDREQUEST_H
#define LEKEYPURGEIDREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyPurgeIDRequest
{
public:
	LEKeyPurgeIDRequest();
	~LEKeyPurgeIDRequest();

    /************************************************* 
    Function   ： FormatLEKeyPurgeIDRequest()
    Description： format 'LEKeyPurgeIDRequest' Auditorium Security Message 
    Input      ： LEKeyId       :unique key id         
    Output     ： NewRequestBuf :memory address of LEKeyPurgeIDRequest
		          len           :the length of LEKeyPurgeIDRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEKeyPurgeIDRequest (
		/* in*/UInt32  LEKeyId,         //链路解密密钥ID
		/*out*/UInt8  *NewRequestBuf,   //接收组装好的 LEKeyPurgeIDRequest 请求消息的缓冲区地址   
		/*out*/UInt32 *len);            //组装好的 LEKeyPurgeIDRequest 请求消息长度
		
	/************************************************* 
    Function   ： ParseLEKeyPurgeIDRequest()
    Description： Parse 'LEKeyPurgeIDRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of LEKeyPurgeIDRequest
		          RequestLen    :the length of LEKeyPurgeIDRequest 		
    Output     ： RequestId,    :Request Message id of LEKeyPurgeIDRequest
		          LEKeyId       :unique key id  
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyPurgeIDRequest (
		/* in*/UInt8  *RequestBuf,      //接收到的请求消息的存储区地址
		/* in*/UInt32  RequestLen,      //接收到的请求消息长度
		/*out*/UInt32 *RequestId,       //请求消息的消息ID
		/*out*/UInt32 *LEKeyId);        //链路解密密钥ID
		
private:

    /************************************************* 
    Function   ： SetLEKeyId()
    Description： transform LEKeyId to the LEKeyId message saved in memory 
    Input      ： LEKeyId       :LEKeyId want to transform	         	      
    Output     ： LEKeyBuf      :memory address of LEKeyId message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/   
	UInt32 SetLEKeyId(
        /* in*/UInt32  LEKeyId,    //要填写的LEKeyId
        /*out*/UInt8  *LEKeyBuf);  //目标地址空间地址

    /************************************************* 
    Function   ： ParseLEKeyId()
    Description： transform the LEKeyId message saved in memory to integer
    Input      ： LEKeyBuf       :memory address of LEKeyId message		               
    Output     ：
    Return     ： integer match along with LEKeyId message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyId(
		/*in*/ UInt8  *LEKeyBuf);  //存储四个字节信息的空间地址

	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针
};

#endif /* LEKEYPURGEIDREQUEST_H */



