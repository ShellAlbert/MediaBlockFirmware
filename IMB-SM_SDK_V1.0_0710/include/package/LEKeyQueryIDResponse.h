/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyQueryIDResponse.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM<-PROj)--LEKeyQueryIDResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYIDRESPONSE_H
#define LEKEYQUERYIDRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryIDResponse
{
public:
	LEKeyQueryIDResponse();
	~LEKeyQueryIDResponse();

    /************************************************* 
    Function   ： FormatLEKeyQueryIDResponse()
    Description： format 'LEKeyQueryIDResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of LEKeyQueryIDRequest 
                  KeyStatus       :'1' if the key is present,'0' otherwise
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of LEKeyQueryIDResponse
		          len             :the length of LEKeyQueryIDResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEKeyQueryIDResponse(
		/* in*/UInt32  RequestId,      //对应 LEKeyQueryIDRequest 请求消息的消息ID
		/* in*/UInt8   KeyStatus,      //链路解密密钥状态
		/* in*/UInt8   ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h
		/*out*/UInt8  *NewResponseBuf, //接收组装好的 LEKeyQueryIDResponse 回复消息的缓冲区地址
		/*out*/UInt32 *len);           //组装好的 LEKeyQueryIDResponse 消息长度

    /************************************************* 
    Function   ： ParseLEKeyQueryIDResponse()
    Description： Parse 'LEKeyQueryIDResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of LEKeyQueryIDResponse
		          ResponseLen    :the length of LEKeyQueryIDResponse 		
    Output     ： RequestId,     :Request Message id of LEKeyQueryIDRequest
                  KeyStatus      :'1' if the key is present,'0' otherwise
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyQueryIDResponse(
		/* in*/UInt8  *ResponseBuf,    //接收到的回复消息的存储区地址
		/* in*/UInt32  ResponseLen,    //接收到的回复消息长度
		/*out*/UInt32 *RequestId,      //对应 IDAuthenticationRequest 请求消息的消息ID
		/*out*/UInt8  *KeyStatus,      //链路解密密钥状态
		/*out*/UInt8  *ResponseStatus);//通用回复状态值，取值为0-3，具体解释参见Const.h

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* LEKEYQUERYIDRESPONSE_H */



