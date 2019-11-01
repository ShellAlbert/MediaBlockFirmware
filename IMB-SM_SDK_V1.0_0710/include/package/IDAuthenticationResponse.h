/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： IDAuthenticationResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--IDAuthenticationResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef IDAUTHENTICATIONRESPONSE_H
#define IDAUTHENTICATIONRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class IDAuthenticationResponse
{
public:

	IDAuthenticationResponse();
	~IDAuthenticationResponse();

    /************************************************* 
    Function   ： FormatIDAuthenticationResponse()
    Description： format 'IDAuthenticationResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of IDAuthenticationRequest 
                  RightsList      :Rights list of user
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of IDAuthenticationResponse
		          len             :the length of IDAuthenticationResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatIDAuthenticationResponse(
    		/* in*/ UInt32     RequestId,      //对应 IDAuthenticationRequest 请求消息的消息ID
			/* in*/ UInt32     RightsList,     //权限列表
    		/* in*/ UInt8      ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h 
    		/*out*/ UInt8     *NewResponseBuf, //接收组装好的 IDAuthenticationResponse 回复消息的缓冲区地址
    		/*out*/ UInt32    *len);           //组装好的 IDAuthenticationResponse 消息长度
                        		
    /************************************************* 
    Function   ： ParseIDAuthenticationResponse()
    Description： Parse 'IDAuthenticationResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of IDAuthenticationResponse
		          ResponseLen    :the length of IDAuthenticationResponse 		
    Output     ： RequestId,     :Request Message id of IDAuthenticationRequest
                  RightsList     :Rights list of user
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseIDAuthenticationResponse(
    		/*in */ UInt8    *ResponseBuf,     //接收到的回复消息的存储区地址
    		/*in */ UInt32    ResponseLen,     //接收到的回复消息长度
    		/*out*/ UInt32   *RequestId,       //对应 IDAuthenticationRequest 请求消息的消息ID
    		/*out*/ UInt32   *RightsList,      //权限列表
    		/*out*/ UInt8    *ResponseStatus); //通用回复状态值，取值为0-3，具体解释参见Const.h

private:
    
	/************************************************* 
    Function   ： SetRightsList()
    Description： Rights List(integer) List to the message saved in memory 
    Input      ： RightsList   : Rights List want to transform	         	      
    Output     ： Buf          :memory address of message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 SetRightsList(
        /* in*/UInt32  RightsList, //要填写的权限列表
        /*out*/UInt8  *Buf);       //目标地址空间地址
        
     /************************************************* 
    Function   ： ParseRightsList()
    Description： transform the Rights List message saved in memory to integer
    Input      ： Buf       :memory address of Rights List message		            
    Output     ：
    Return     ： Rights List(integer) match along with  Rights List message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseRightsList(
		/*in*/ UInt8  *Buf);       //存储四个字节信息的空间地址

	MessageLength    *MyMessageLength;        //消息头（KEY in KLV struct）类指针
	MessageULName    *MyMessageULName;        //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;     //消息ID类指针
};



#endif



