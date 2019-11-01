/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetCertChainRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/10/09
Version    ： v1.0
Description： Auditorium Security Message(SM->SMS)--LEKeyLoadRequest
Others     :  
History    ： 
********************************************/
#ifndef GETCERTCHAINREQUEST_H
#define GETCERTCHAINREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetCertChainRequest 
{
public:
	GetCertChainRequest();
	~GetCertChainRequest();

	/************************************************* 
	Function   ： FormatGetCertChainRequest()
	Description： format 'GetCertChainRequest' Auditorium Security Message 
	Input      ： UserID        : Certificate's Thumb print
	              CertType      : Certificate's type
	Output     ： NewRequestBuf :memory address of LEKeyLoadRequest
	              len           :the length of LEKeyLoadRequest 
	Return     ： error code, refer to Const.h
	Others     :        
	*************************************************/
	UInt32 FormatGetCertChainRequest(
		/*in */ TEXT    *UserID,	// Certificate's Thumb print
//		/*in */ UInt32   CertType,	// Certificate's type
		/*out*/ UInt8   *NewRequestBuf,	// 接收组装好的 GetCertChainRequest 请求消息的缓冲区地址
		/*out*/ UInt32  *len);		//组装好的 GetCertChainRequest 请求消息长度

	/************************************************* 
	Function   ： ParseGetCertChainRequest()
	Description： Parse 'GetCertChainRequest'Auditorium Security Message 
	Input      ： RequestBuf   :memory address of LEKeyLoadRequest
	              RequestLen   :the length of LEKeyLoadRequest 		
	Output     ： RequestId    :Request Message id of LEKeyLoadRequest
	              UserID       :The Certificate's Thumb print
				        CertType     :The Certificate's type
	Return     ： error code, refer to Const.h
	Others     : 
	*************************************************/ 
	UInt32 ParseGetCertChainRequest(
		/*in */ UInt8   *RequestBuf,	//接收到的请求消息的存储区地址
		/*in */ UInt32   RequestLen,	//接收到的请求消息长度
		/*out*/ UInt32  *RequestId,		//请求消息的消息ID
		/*out*/ TEXT    *UserID		// Received the Certificate's Thumb print
//		/*out*/ UInt32  *CertType
		);		// Received the Certificate's type
		
private:
	//函数作用：将配置类型按Big-Endian填写到连续的四个字节空间中
	UInt32 SetCertType(
		/*in */ UInt32  CertType,	//要填写的配置类型
		/*out*/ UInt8  *CertBuf);	//目标地址空间地址
	
	//函数作用：将一个按Big-Endian排序的四个字节空间内容转换成配置类型返回						
	UInt32 ParseCertType(
		/*in */ UInt8 *CertBuf);	//存储四个字节信息的空间地址
							
	MessageLength    *MyMessageLength;		//消息头（KEY in KLV struct）类指针
	MessageULName    *MyMessageULName;		//消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;	//消息ID类指针	
};

#endif


