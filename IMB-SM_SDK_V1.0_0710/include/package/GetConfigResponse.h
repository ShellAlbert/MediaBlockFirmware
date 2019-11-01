/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetConfigResponse.h
Author     ： zhangliang@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--GetConfigResponse
Others     :  
History    ： 
      < Author >    			     < Date >           < Modification >
zhangliang@dadimedia.com       10/09/29            Add comment
huweihua@dadimedia.com         10/10/25            modify errors of compilation 
********************************************/
#ifndef GetConfigResponse_H
#define GetConfigResponse_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetConfigResponse
{
public:

	GetConfigResponse();
	~GetConfigResponse();
	
    /************************************************* 
    Function   ： FormatGetConfigResponse()
    Description： format 'GetConfigResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of SetConfigRequest 
                  ConfigType      :Config Type, refer to code of each config
                  ConfigValue     :Config Value 
                  ConfigValueLen  :length of config value      
    	          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of GetConfigResponse
    	          len             :the length of GetConfigResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetConfigResponse(
		/* in*/ UInt32    RequestId,      //对应 SetConfigRequest 请求消息的消息ID
		/* in*/ UInt32    ConfigType,     //配置类型
    /* in*/ UInt32    ConfigValueLen, //配置类型长度
    /* in*/ TEXT     *ConfigVaulue,   //配置类型值
		/* in*/ UInt8     ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h
		/*out*/ UInt8    *NewResponseBuf, //接收组装好的 GetConfigResponse 回复消息的缓冲区地址
		/*out*/ UInt32   *len);           //组装好的 GetConfigResponse 消息长度

    /************************************************* 
    Function   ： ParseGetConfigResponse()
    Description： Parse 'GetConfigResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of GetConfigResponse
		          ResponseLen    :the length of GetConfigResponse 		
    Output     ： RequestId      :Request Message id of GetConfigRequest
                  ConfigType     :config type
                  ConfigTypeValue:the value of config type
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetConfigResponse(
		/*in */ UInt8    *ResponseBuf,    //接收到的回复消息的存储区地址
		/*in */ UInt32    ResponseLen,    //接收到的回复消息长度
		/*out*/ UInt32   *RequestId,      //对应 SetConfigRequest 请求消息的消息ID
		/*out*/ UInt32   *ConfigType,     //配置类型
        /*out*/ TEXT     *ConfigVaulue,   //配置类型值
		/*out*/ UInt8    *ResponseStatus);//通用回复状态值，取值为0-3，具体解释参见Const.h

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



