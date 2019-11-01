/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： SMSQuerySPBResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--SMSQuerySPBResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef SMSQUERYSPBRESPONSE_H
#define SMSQUERYSPBRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class SMSQuerySPBResponse
{

public:

	SMSQuerySPBResponse();
	~SMSQuerySPBResponse();
	
    /************************************************* 
    Function   ： FormatSMSQuerySPBResponse()
    Description： format 'SMSQuerySPBResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of SMSQuerySPBRequest 
                  status          :status information of projector   
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of SMSQuerySPBResponse
		          len             :length of SMSQuerySPBResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSMSQuerySPBResponse(
		/* in*/ UInt32  RequestId,      //对应 QuerySPBRequest 请求消息的消息ID
		/* in*/ UInt8   Protocol_ver,
		/* in*/ UInt8   status,         //放映机状态  
		/* in*/ UInt64	secureTime,
		/* in*/ Int32	time_adjust,
		/* in*/ UInt8   ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h 
		/*out*/ UInt8  *NewResponseBuf, //接收组装好的 QuerySPBResponse 回复消息的缓冲区地址
		/*out*/ UInt32 *len);           //组装好的 QuerySPBResponse 消息长度
		
    /************************************************* 
    Function   ： ParseSMSQuerySPBResponse()
    Description： Parse 'SMSQuerySPBResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of SMSQuerySPBResponse
		          ResponseLen    :length of SMSQuerySPBResponse 		
    Output     ： RequestId,     :Request Message id of SMSQuerySPBRequest
                  status         :status information of projector  
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseSMSQuerySPBResponse(
		/* in*/ UInt8  *ResponseBuf,    //接收到的回复消息的存储区地址
		/* in*/ UInt32  ResponseLen,    //接收到的回复消息长度
		/*out*/ UInt32 *RequestId,      //对应 QuerySPBRequest 请求消息的消息ID
		/*out*/ UInt8  *Protocol_ver,
		/*out*/ UInt8  *Status,         //放映机状态
		/*out*/ UInt64 *secureTime,
		/*out*/ Int32  *time_adjust,
		/*out*/ UInt8  *ResponseStatus);//通用回复状态值，取值为0-3，具体解释参见Const.h 

private:	
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针		

};

#endif
