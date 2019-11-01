/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyQueryIDRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROj)--LEKeyQueryIDRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYIDREQUEST_H
#define LEKEYQUERYIDREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryIDRequest
{
public:
	LEKeyQueryIDRequest();
	~LEKeyQueryIDRequest();

    /************************************************* 
    Function   ： FormatLEKeyQueryIDRequest()
    Description： format 'LEKeyQueryIDRequest' Auditorium Security Message 
    Input      ： LEKeyId       :unique LE Key id	         
    Output     ： NewRequestBuf :memory address of LEKeyQueryIDRequest
		          len           :the length of LEKeyQueryIDRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatLEKeyQueryIDRequest(
		/*in */UInt32  LEKeyId,       //链路解密密钥
		/*out*/UInt8  *NewRequestBuf, //接收组装好的 LEKeyQueryIDRequest 请求消息的缓冲区地址
		/*out*/UInt32 *len);          //组装好的 LEKeyQueryIDRequest 请求消息长度

	/************************************************* 
    Function   ： ParseLEKeyQueryIDRequest()
    Description： Parse 'LEKeyQueryIDRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of LEKeyQueryIDRequest
		          RequestLen    :the length of LEKeyQueryIDRequest 		
    Output     ： RequestId,    :Request Message id of LEKeyQueryIDRequest
		          LEKeyId       :unique LE Key id	
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseLEKeyQueryIDRequest(
		/*in */UInt8  *ResponseBuf,   //接收到的请求消息的存储区地址
		/*in */UInt32  ResponseLen,   //接收到的请求消息长度
		/*out*/UInt32 *RequestId,     //请求消息的消息ID
		/*out*/UInt32 *LEKeyId);      //链路解密密钥

private:
    
    /************************************************* 
    Function   ： SetLEKeyId()
    Description： transform integer to the LEKeyId message saved in memory 
    Input      ： LEKeyId       :LEKeyId want to transform	         	      
    Output     ： LEKeyBuf      :memory address of  the LEKeyId message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 SetLEKeyId(
        /* in*/UInt32  LEKeyId,      //要填写的LEKeyId
        /*out*/UInt8  *LEKeyBuf);    //目标地址空间地址

    /************************************************* 
    Function   ： ParseLEKeyId()
    Description： transform the LEKeyId message saved in memory to integer
    Input      ： LEKeyBuf       :memory address of LEKeyId  message		           
    Output     ：
    Return     ： integer match along with LEKeyId message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyId(
		/*in*/ UInt8  *LEKeyBuf);    //存储四个字节信息的空间地址

	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* LEKEYQUERYIDREQUEST_H */



