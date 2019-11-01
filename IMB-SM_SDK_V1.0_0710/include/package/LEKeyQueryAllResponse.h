/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyQueryAllResponse.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM<-PROj)--LEKeyQueryAllResponse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYALLRESPONSE_H
#define LEKEYQUERYALLRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryAllResponse
{
public:
	LEKeyQueryAllResponse();
	~LEKeyQueryAllResponse();
	
   /************************************************* 
    Function   ： FormatLEQueryAllResponse()
    Description： format 'LEKeyQueryAllResponse' Auditorium Security Message 
    Input      ： RequestId       :Request Message id of LEKeyQueryAllRequest 
                  Delimiter       :Delimiter of the list 
                  LEKeyIDBatch    :a list of LE Key ID values
		          ResponseStatus  :General Response Elements
    Output     ： NewResponseBuf  :memory address of LEKeyQueryAllResponse
		          len             :the length of LEKeyQueryAllResponse 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEQueryAllResponse (
		/*in */ UInt32  RequestId,      //对应 LEKeyQueryAllRequest 请求消息的消息ID
		/*in */ UInt8   Delimiter,      //指定LEKeyID链字符串分割符
		/*in */ UInt8  *LEKeyIDBatch,   //LEKeyID链，字符串格式为“ID1分割符ID2分割符ID3.....”
		/*in */ UInt8   ResponseStatus, //通用回复状态值，取值为0-3，具体解释参见Const.h 
		/*out*/ UInt8  *NewResponseBuf, //接收组装好的 LEKeyQueryAllResponse 回复消息的缓冲区地址
    	/*out*/ UInt32 *len);           //组装好的 LEKeyQueryAllResponse 消息长度
		
    /************************************************* 
    Function   ： ParseLEKeyQueryAllResponse()
    Description： Parse 'LEKeyQueryAllResponse'Auditorium Security Message 
    Input      ： ResponseBuf    :memory address of LEKeyQueryAllResponse
		          ResponseLen    :the length of LEKeyQueryAllResponse 	
		          Delimiter      :Delimiter of event id list	
    Output     ： RequestId,     :Request Message id of AuditRequest
                  LEKeyIDBatch   :a list of LE Key ID values
		          ResponseStatus :General Response Elements
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyQueryAllResponse(
		/*in */ UInt8  *ResponseBuf,    //接收到的回复消息的存储区地址
		/*in */ UInt32  ResponseLen,    //接收到的回复消息长度
		/*in */ UInt8   Delimiter,      //指定LEKeyID链字符串分割符
		/*out*/ UInt32 *RequestId,      //对应 LEKeyQueryAllRequest 请求消息的消息ID
		/*out*/ UInt8  *LEKeyIDBatch,   //LEKeyID链，字符串格式为“ID1分割符ID2分割符ID3.....”
		/*out*/ UInt8  *ResponseStatus);//通用回复状态值，取值为0-3，具体解释参见Const.h 
		
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
		/*in */ UInt8  *Buf,      //存储字节信息的空间地址
		/*in */ UInt32  BufLEN);  //信息空间的长度

    /************************************************* 
    Function   ： ParseLenToBuf()
    Description： transform integer to the message saved in memory 
    Input      ： IntNum       :integer want to transform	         	      
    Output     ： Buf          :memory address of message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/  
	UInt32 ParseLenToBuf(
		/*in */ UInt32 IntNum,    //要填写的整数
		/*out*/ UInt8 *Buf);      //目标地址空间地址
		
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif	/* LEKEYQUERYALLRESPONSE_H */



