/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： ClearCSPsResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 11/08/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--ClearCSPsResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification > 
********************************************/
#ifndef CLEARCSPSRESPONSE_H
#define CLEARCSPSRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class ClearCSPsResponse
{
public:
	ClearCSPsResponse();
	~ClearCSPsResponse();
	
    /************************************************* 
    Function   ： FormatClearCSPsResponse()
    Description： format 'ClearCSPsResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of StartSuiteRequest 
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of ClearCSPsResponse
		          len             :length of ClearCSPsResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatClearCSPsResponse(
		/* in*/ UInt32  RequestId,       //对应 StartSuiteRequest 请求消息的消息ID
		/* in*/ UInt8   ResponseStatus,  //通用回复状态值，取值为0-3，具体解释参见Const.h
		/*out*/ UInt8  *NewResponseBuf,  //接收组装好的 ClearCSPsResponse 回复消息的缓冲区地址
        /*out*/ UInt32 *len);            //组装好的 ClearCSPsResponse 消息长度
		
    /************************************************* 
    Function   ： ParseClearCSPsResponse()
    Description： Parse 'ClearCSPsResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of ClearCSPsResponse
		          ResponseLen    :length of ClearCSPsResponse 		
    Output     ： RequestId,     :Request Message id of StartSuiteRequest
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseClearCSPsResponse(
		/* in*/ UInt8   *ResponseBuf,    //接收到的回复消息的存储区地址
		/* in*/ UInt32   ResponseLen,	 //接收到的回复消息长度	
		/*out*/ UInt32  *RequestId,      //对应 StartSuiteRequest 请求消息的消息ID
		/*out*/ UInt8   *ResponseStatus);//通用回复状态值，取值为0-3，具体解释参见Const.h

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* STARTSUITERESPONSE_H */


