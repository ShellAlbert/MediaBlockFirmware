/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： GetEventListResponse.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SMS<-SM)--GetEventListResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETEVENTLISTRESPONSE_H
#define GETEVENTLISTRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventListResponse
{

public:

	GetEventListResponse();
	~GetEventListResponse();

    /************************************************* 
    Function   ： FormatGetEventListResponse()
    Description： format 'GetEventListResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of GetEventListRequest 
                  Delimiter       :Delimiter of event id list
                  EventIdBatch    :list of event id 
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of GetEventListResponse
		          len             :the length of GetEventListResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventListResponse(
		/*in */ UInt32    RequestId,      //对应 GetEventListRequest 请求消息的消息ID
		/*in */ UInt8     Delimiter,      //字段分割符
		/*in */ UInt8    *EventIdBatch,   //日志ID链表
		/*in */ UInt8     ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h 
		/*out*/ UInt8    *NewResponseBuf, //接收组装好的 GetEventListResponse 回复消息的缓冲区地址
		/*out*/ UInt32   *len);           //组装好的 GetEventListResponse 消息长度

    /************************************************* 
    Function   ： ParseGetEventListResponse()
    Description： Parse 'GetEventListResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of GetEventListResponse
		          ResponseLen    :the length of GetEventListResponse 			        
    Output     ： RequestId,     :Request Message id of GetEventListRequest
                  EventIdNum     :the number of event id 
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	 UInt32 ParseGetEventListResponse(
		/*in */ UInt8  *ResponseBuf,      //接收到的回复消息的存储区地址
		/*in */ UInt32  ResponseLen,      //接收到的回复消息长度		  
		/*out*/ UInt32 *RequestId,        //对应 GetEventListRequest 请求消息的消息ID
		/*out*/ UInt32 *EventIdNum,       //日志ID个数
		/*out*/ UInt8  *ResponseStatus);  //通用回复状态值，取值为0-3，具体解释参见Const.h
		
	/************************************************* 
    Function   ： GetEventId()
    Description： get event id array 
    Input      ： EventIdNum        :the number of element in TempEventIdSet    
    Output     ： TempEventIdSet    :the array of Event Id           
    Return     ： error code, refer to Const.h
    Others     :  GetEventId  function will copy  the array of Event Id to 
                  memory of 'TempEventIdSet' point to
    *************************************************/ 	
   UInt32 GetEventId(
                /*out*/UInt32 *TempEventIdSet,
                /* in*/UInt32  EventIdNum);
    

private:	    
    /************************************************* 
    Function   ： ParseBufToLen()
    Description： transform the message saved in memory to integer
    Input      ： Buf       :memory address of message
		          BufLEN    :the length of message 	memory		      
    Output     ：
    Return     ： integer match along with message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseBufToLen(
		/*in */ UInt8 *Buf,       //存储字节信息的空间地址
		/*in */ UInt32 BufLEN);   //信息长度

     /************************************************* 
    Function   ： ParseLenToBuf()
    Description： transform integer to the message saved in memory 
    Input      ： IntNum       :integer want to transform	         	      
    Output     ： Buf          :memory address of message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/     
	UInt32 ParseLenToBuf(
		/*in */  UInt32 IntNum,   //要填写的整数
		/*out */ UInt8 *Buf);     //目标地址空间地址
    
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针
	UInt32           *m_EventIdSet;	         //the array of Event Id 
	UInt32            m_EventIdNum;          //tne number of Event Id

};


#endif
