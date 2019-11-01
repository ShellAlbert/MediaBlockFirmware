/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： SetCertChainResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 2011/8/15
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--SetCertChainResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
 
********************************************/
#ifndef SETCERTCHAINRESPONSE_H
#define SETCERTCHAINRESPONSE_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"

class SetCertChainResponse
{
public:

	SetCertChainResponse();
	~SetCertChainResponse();

    /************************************************* 
    Function   ： FormatSetCertChainResponse()
    Description： format 'SetCertChainResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of SetCertChainRequest 
                  UserID          :user id
                  CertType        :certificate type  
    	          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of SetCertChainResponse
    	          len             :the length of SetCertChainResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSetCertChainResponse(
		/*in */ UInt32  RequestId,          //对应AuditRequest请求消息的消息ID
//	/*in */ TEXT   *UserID,        
//	/*in */ UInt32  CertType,          	
		/*in */ UInt8   ResponseStatus,     //通用回复状态值，取值为0-3，具体解释参见Const.h
		/*out*/ UInt8  *NewResponseBuf,     //接收组装好的AuditResponse回复消息的缓冲区地址
		/*out*/ UInt32 *len);               //组装好的AuditResponse消息长度

    /************************************************* 
    Function   ： ParseSetCertChainResponse()
    Description： Parse 'SetCertChainResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of SetCertChainResponse
    	          ResponseLen    :length of SetCertChainResponse 		
    Output     ： RequestId,     :Request Message id of SetCertChainRequest
                  UserID         :user id
                  CertType       :certificate type 
    	          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/  
	UInt32 ParseSetCertChainResponse(
		/*in */ UInt8  *ResponseBuf,        //接收到的回复消息的存储区地址
		/*in */ UInt32  ResponseLen,        //接收到的回复消息长度
		/*out*/ UInt32 *RequestId,          //对应AuditRequest请求消息的消息ID
//	/*out*/ TEXT   *UserID,
//	/*out*/ UInt32 *CertType,
		/*out*/ UInt8  *ResponseStatus);    //通用回复状态值，取值为0-3，具体解释参见Const.h
		
    /************************************************* 
    Function   ： SetCertType()
    Description： transform certificate type to the message saved in memory 
    Input      ： CertType     :certificate type
    Output     ： CertTypeBuf  :memory address of message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 		
    UInt32 SetCertType(
        /* in*/UInt32  CertType, 
        /*out*/UInt8  *CertTypeBuf);
        
    /************************************************* 
    Function   ： ParseCertType()
    Description： transform the message saved in memory to certificate type
    Input      ： CertTypeBuf   :memory address of message	          	      
    Output     ： 
    Return     ： certificate type
    Others     :        
    *************************************************/         
    UInt32 ParseCertType(
    /*in*/ UInt8  *CertTypeBuf);

private:

	MessageLength    *MyMessageLength;      //消息头（KEY in KLV struct）类指针
	MessageULName    *MyMessageULName;      //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;   //消息ID类指针
};

#endif


