/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetConfigRequest.h
Author     ： zhangliang@dadimedia.com
Date       ： 10/09/29
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--GetConfigRequest
Others     :  
History    ： 
      < Author >    		       < Date >          < Modification >
zhangliang@dadimedia.com       10/09/29            Add comment
huweihua@dadimedia.com         10/10/25            modify errors of compilation 
********************************************/
#ifndef GetConfigRequest_H
#define GetConfigRequest_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetConfigRequest
{
public:

	GetConfigRequest();
	~GetConfigRequest();

	/************************************************* 
    Function   ： FormatGetConfigRequest()
    Description： format 'GetConfigRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	      
                  ConfigType    :Config Type, refer to code of each config
    Output     ： NewRequestBuf :memory address of GetConfigRequest
		          len           :the length of GetConfigRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetConfigRequest(
       /*in */ TEXT    *UserID,           //操作用户的用户证书指纹
       /*in */ UInt32   ConfigType,       //配置类型，详细类别查看上述配置类型	
       /*out*/ UInt8   *NewRequestBuf,    //接收组装好的 GetConfigRequest 请求消息的缓冲区地址
       /*out*/ UInt32  *len);             //组装好的 GetConfigRequest 请求消息长度
       
	/************************************************* 
    Function   ： ParseGetConfigRequest()
    Description： Parse 'GetConfigRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of GetConfigRequest
		          RequestLen    :the length of GetConfigRequest 		
    Output     ： RequestId,    :Request Message id of GetConfigRequest
		          UserID        :Certificate Thumbprint of uesr
		          ConfigType    :Config Type, refer to code of each config
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetConfigRequest(
		/*in */ UInt8   *RequestBuf,  //接收到的请求消息的存储区地址
		/*in */ UInt32   RequestLen,  //接收到的请求消息长度
		/*out*/ TEXT    *UserID,      //操作用户的用户证书指纹
		/*out*/ UInt32  *RequestId,   //请求消息的消息ID
		/*out*/ UInt32  *ConfigType);  //配置类型，详细类别查看上述配置类型

private:	
    
    //函数作用：将配置类型按Big-Endian填写到连续的四个字节空间中
	UInt32 SetConfigType(
        /* in*/UInt32  ConfigType,   //要填写的配置类型
        /*out*/UInt8  *ConfigBuf);   //目标地址空间地址

    //函数作用：将一个按Big-Endian排序的四个字节空间内容转换成配置类型返回
	UInt32 ParseConfigType(
	    /*in*/ UInt8  *ConfigBuf);   //存储四个字节信息的空间地址

	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};



#endif






