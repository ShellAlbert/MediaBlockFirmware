/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： TimeAdjustRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message (SMS->SM)--TimeAdjustRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef TIMEADJUSTREQUEST_H
#define TIMEADJUSTREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class TimeAdjustRequest
{
public:

	TimeAdjustRequest();
	~TimeAdjustRequest();
	
	/************************************************* 
    Function   ： FormatAuditRequest()
    Description： format 'TimeAdjustRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	 
                  Time          :time want to adjust. time shall be a 64-bitintegerrepresenting 
                                 the number of seconds elapsed since January 1.1970 00:00:00UTC
    Output     ： NewRequestBuf :memory address of TimeAdjustRequest
		          len           :length of TimeAdjustRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatTimeAdjustRequest(
		/* in*/ TEXT     *UserID,        //操作用户的用户证书指纹
		/* in*/ UInt64    Time,          //要调整的时间，表示从1970年1月1日0点0分0秒开始到现在经过的秒数
		/*out*/ UInt8    *NewRequestBuf, //接收组装好的 TimeAdjustRequest 请求消息的缓冲区地址
		/*out*/ UInt32   *len);          //组装好的 TimeAdjustRequest 请求消息长度

		
    /************************************************* 
    Function   ： ParseTimeAdjustRequest()
    Description： Parse 'TimeAdjustRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of TimeAdjustRequest
		          RequestLen    :length of TimeAdjustRequest 		
    Output     ： RequestId,    :Request Message id of TimeAdjustRequest
		          UserID        :Certificate Thumbprint of uesr
		          Time          :time want to adjust. time shall be a 64-bitintegerrepresenting 
                                 the number of seconds elapsed since January 1.1970 00:00:00UTC
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseTimeAdjustRequest(
		/*in */ UInt8   *RequestBuf,   //接收到的请求消息的存储区地址
		/*in */ UInt32   RequestLen,   //接收到的请求消息长度
		/*out*/ UInt32  *RequestId,    //请求消息的消息ID
		/*out*/ TEXT    *UserID,       //操作用户的用户证书指纹
		/*out*/ UInt64  *Time);        //要调整的时间，表示从1970年1月1日0点0分0秒开始到现在经过的秒数

private:	

	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针
};
#endif


