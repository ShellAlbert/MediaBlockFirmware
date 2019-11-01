/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： StopPlayRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message (SMS->SM)--StopPlayRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com  10/05/17            Add comment
   huweihua@dadimedia.com  11/06/24            implement request according to new message struct
********************************************/
#ifndef STOPPLAYREQUEST_H
#define STOPPLAYREQUEST_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"


//stopplay for single CPL and KDM 
#if 0 //add by huweihua 11/06/24 
class StopPlayRequest
{
public:

	StopPlayRequest();
	~StopPlayRequest();

	/************************************************* 
    Function   ： FormatStopPlayRequest()
    Description： format 'StopPlayRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	         
    Output     ： NewRequestBuf :memory address of StopPlayRequest
		          len           :length of StopPlayRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStopPlayRequest(
		/* in */ TEXT   *UserID,       //操作用户的用户证书指纹
		/* out*/ UInt8  *NewRequestBuf,//接收组装好的 StopPlayRequest 请求消息的缓冲区地址
		/* out*/ UInt32 *len);         //组装好的 StopPlayRequest 请求消息长度


	/************************************************* 
    Function   ： ParseStopPlayRequest()
    Description： Parse 'StopPlayRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of StopPlayRequest
		          RequestLen    :length of StopPlayRequest 		
    Output     ： RequestId,    :Request Message id of StopPlayRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseStopPlayRequest(
		/* in */ UInt8  *RequestBuf,  //接收到的请求消息的存储区地址
		/* in */ UInt32  RequestLen,  //接收到的请求消息长度
		/* out*/ UInt32 *RequestId,   //请求消息的消息ID
		/* out*/ TEXT   *UserID);     //操作用户的用户证书指纹

private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};
#endif

//-----------------------------------------------------------------------------------------
//stopplay for multi CPLs and KDMs
//add by huweihua 11/06/24
#if 1
class StopPlayRequest
{
public:
	
	enum STOP_TYPE
	{
		COMPLETE_STOP = 0,
		MANUAL_STOP = 1,
		SINGLE_CPL_STOP = 2,
		INNTERUPT_STOP = 3
	};

	StopPlayRequest();
	~StopPlayRequest();

	/************************************************* 
    Function   ： FormatStopPlayRequest()
    Description： format 'StopPlayRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	   
    						  StopType      ：Stop Type 
    Output     ： NewRequestBuf :memory address of StopPlayRequest
		          len           :length of StopPlayRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStopPlayRequest(
		/* in */ TEXT       *UserID,        //操作用户的用户证书指纹
		/* in*/  STOP_TYPE   StopType,      //停止类型
		/* out*/ UInt8      *NewRequestBuf, //接收组装好的 StopPlayRequest 请求消息的缓冲区地址
		/* out*/ UInt32     *len);          //组装好的 StopPlayRequest 请求消息长度


	/************************************************* 
    Function   ： ParseStopPlayRequest()
    Description： Parse 'StopPlayRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of StopPlayRequest
		          RequestLen    :length of StopPlayRequest 		
    Output     ： RequestId,    :Request Message id of StopPlayRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseStopPlayRequest(
		/* in*/ UInt8     *RequestBuf,  //接收到的请求消息的存储区地址
		/* in*/ UInt32     RequestLen,  //接收到的请求消息长度
		/*out*/ UInt32    *RequestId,   //请求消息的消息ID
		/*out*/ TEXT      *UserID,
		/*out*/ STOP_TYPE *StopType);   //操作用户的用户证书指纹


  /************************************************* 
    Function   ： ParseBufToLen()
    Description： transform the message saved in memory to integer
    Input      ： Buf       :memory address of message
    	          BufLen    :the length of message 	memory		      
    Output     ：
    Return     ： integer match along with message saved in memory
    Others     :        
    *************************************************/ 			
    UInt32 ParseBufToLen(
            /*in*/UInt8 *Buf, 
            /*in*/UInt32 BufLen);

    /************************************************* 
    Function   ： ParseLenToBuf()
    Description： transform integer to the message saved in memory 
    Input      ： IntNum       :integer want to transform	
             	  BufLen       :the length of message 	memory
    Output     ： Buf          :memory address of message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/            
    UInt32 ParseLenToBuf(
            /* in*/UInt32  IntNum,
            /* in*/UInt32  BufLen,
            /*out*/UInt8  *Buf);		
private:
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};
#endif


#endif


