/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： IDAuthenticationRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--IDAuthenticationRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef IDAUTHENTICATIONREQUEST_H
#define IDAUTHENTICATIONREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class IDAuthenticationRequest
{
public:

	IDAuthenticationRequest();
	~IDAuthenticationRequest();
#if 0
    /************************************************* 
    Function   ： FormatIDAuthenticationRequest()
    Description： format 'IDAuthenticationRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Output     ： NewRequestBuf :memory address of IDAuthenticationRequest
		          len           :the length of IDAuthenticationRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatIDAuthenticationRequest(
		/*in */ TEXT     *UserID,         //操作用户的用户证书指纹
		/*in */ TEXT     *UserName,       //操作用户的用户名
		/*in */ TEXT     *Password,       //操作用户的登录密码
		/*in */ UInt32    SingnedAglth,   //签名算法
		/*in */ TEXT     *SingnedValue,   //签名值
		/*in */ TEXT     *CertChain,      //证书链
		/*out*/ UInt8    *NewRequestBuf,  //接收组装好的 IDAuthenticationRequest 请求消息的缓冲区地址
		/*out*/ UInt32   *len);           //组装好的 IDAuthenticationRequest 请求消息长度

	/************************************************* 
    Function   ： ParseIDAuthenticationRequest()
    Description： Parse 'IDAuthenticationRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of IDAuthenticationRequest
		          RequestLen    :the length of IDAuthenticationRequest 		
    Output     ： RequestId,    :Request Message id of IDAuthenticationRequest
		          UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseIDAuthenticationRequest(
		/*in */ UInt8   *RequestBuf,   //接收到的请求消息的存储区地址
		/*in */ UInt32   RequestLen,   //接收到的请求消息长度
		/*out*/ UInt32  *RequestId,    //请求消息的消息ID
		/*out*/ TEXT    *UserID,       //发出请求消息的用户的证书指纹
		/*out*/ TEXT    *UserName,     //操作用户的用户名
		/*out*/ TEXT    *Password,     //操作用户的登录密码
		/*out*/ UInt32  *SingnedAglth, //签名算法
		/*out*/ TEXT    *SingnedValue, //签名值
		/*out*/ TEXT    *CertChain);   //证书链
#endif 

#if 1
    /************************************************* 
    Function   ： FormatIDAuthenticationRequest()
    Description： format 'IDAuthenticationRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
    Output     ： NewRequestBuf :memory address of IDAuthenticationRequest
		          len           :the length of IDAuthenticationRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
UInt32 FormatIDAuthenticationRequest(
		/*in */ TEXT     *UserID, 
		/*in */ TEXT     *UserName, 
		/*in */ TEXT     *Password, 
		/*in */ TEXT     *Role, 		 
		/*in */ UInt32    SingnedAglth,
		/*in */ TEXT     *SingnedValue,
		/*out*/ UInt8    *NewRequestBuf, 
		/*out*/ UInt32   *len);
		
	/************************************************* 
    Function   ： ParseIDAuthenticationRequest()
    Description： Parse 'IDAuthenticationRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of IDAuthenticationRequest
		              RequestLen    :the length of IDAuthenticationRequest 		
    Output     ： RequestId,    :Request Message id of IDAuthenticationRequest
		              UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  Role          :role of user
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseIDAuthenticationRequest(
		/*in */ UInt8   *RequestBuf,   //接收到的请求消息的存储区地址
		/*in */ UInt32   RequestLen,   //接收到的请求消息长度
		/*out*/ UInt32  *RequestId,    //请求消息的消息ID
		/*out*/ TEXT    *UserID,       //发出请求消息的用户的证书指纹
		/*out*/ TEXT    *UserName,     //操作用户的用户名
		/*out*/ TEXT    *Password,     //操作用户的登录密码
		/*out*/ TEXT    *Role,        //操作用户的登录密码		
		/*out*/ UInt32  *SingnedAglth, //签名算法
		/*out*/ TEXT    *SingnedValue); //签名值
		

#endif
private:
	    /************************************************* 
        Function   ： SetLen()
        Description： transform integer to the message saved in memory 
        Input      ： Len       :integer want to transform	         	      
        Output     ： Buf       :memory address of message
        Return     ： error code, refer to Const.h
        Others     :        
        *************************************************/ 	
		UInt32 SetLen(
        /* in*/UInt32  Len,     //要填写的32位整数
        /*out*/UInt8  *Buf);    //目标地址空间地址
        
	    /************************************************* 
        Function   ： ParseLen()
        Description： transform the message saved in memory to integer
        Input      ： Buf       :memory address of message    		          
        Output     ：
        Return     ： integer match along with message saved in memory
        Others     :        
        *************************************************/ 
		UInt32 ParseLen(
        /*in*/ UInt8  *Buf);    //存储四个字节信息的空间地址

	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};



#endif




