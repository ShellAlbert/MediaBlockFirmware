/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： LEKeyLoadRequest.h
Author     ： cuijixin@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message(SM->PROJ)--LEKeyLoadRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
   huweihua@dadimedia.com        10/05/17            Add KE_KEY_LEN
********************************************/
#ifndef LEKEYLOADREQUEST_H
#define LEKEYLOADREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

#define KE_KEY_LEN  16     //the length of LE KEY

//链路解密密钥结构体
struct LEKeyInfo
{
	UInt32  m_LEKeyID;           //unique key identifier
	UInt8   m_Key[KE_KEY_LEN];   //decryption key
	UInt32  m_ExpireTime;        //calidity period of key in seconds
	UInt64  m_AttributeData;     //data used as input to counter mode cipher
	struct LEKeyInfo* m_pNext;   //next node 
};

class LEKeyLoadRequest
{
public:
	LEKeyLoadRequest();
	~LEKeyLoadRequest();


	/************************************************* 
    Function   ： SetList()
    Description： push each LE key message into list 
    Input      ： KeyID    :unique key identifier        
                  Key      :unique key identifier
                  ExTime   :calidity period of key in seconds
                  AttrData :data used as input to counter mode cipher
    Output     ： head     :the head of list	         
    Return     ： error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.     
    *************************************************/
    // 在组装LEKeyLoadRequest前调用该函数将所有要传输的密钥组成一条链表，
    // 内存分配由函数内部完成，在调用FormatLEKeyLoadRequest后，先前组成的链表自动销毁。
	UInt32 SetList(
		/*in */ const  UInt32      &KeyID,    //链路解密密钥ID
		/*in */ const  UInt8       *Key,      //链路解密密钥
		/*in */ const  UInt32      &ExTime,   //密钥有效的时间长度
		/*in */ const  UInt64      &AttrData, //初始化AES盒的向量
		/*out*/ struct LEKeyInfo  **head);    //链路解密密钥链表头指针

	/************************************************* 
    Function   ： FormatLEKeyLoadRequest()
    Description： format 'LEKeyLoadRequest' Auditorium Security Message 
    Input      ： LEKeyBatch    :a list of LE Key ID to Key, Expire Time and Attribute Data mappings	         
    Output     ： NewRequestBuf :memory address of LEKeyLoadRequest
		          len           :the length of LEKeyLoadRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatLEKeyLoadRequest(
		/*in */ struct LEKeyInfo *LEKeyBatch,   //要传输的密钥链表头指针
		/*out*/ UInt8            *NewRequestBuf,//接收组装好的 LEKeyLoadRequest 请求消息的缓冲区地址
		/*out*/ UInt32           *len);         //组装好的 LEKeyLoadRequest 请求消息长度
 
 
    /************************************************* 
    Function   ： ParseLEKeyLoadRequest()
    Description： Parse 'LEKeyLoadRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of LEKeyLoadRequest
		          RequestLen    :the length of LEKeyLoadRequest 		
    Output     ： RequestId,    :Request Message id of LEKeyLoadRequest
		          head          :the head of the list of LE Key ID 
    Return     ： error code, refer to Const.h
    Others     :  Function will return a list of  LE Key messages, application call 
                  GetListMember() gets each  LE Key messages. the memory been used by list 
                  was malloc and delete inside Function.
    *************************************************/ 
    // 该函数会将消息中的链路解密密钥组成一条连表返回
    // 应用层再调用GetListMember获取单个密钥组，每调用一次获取一个密钥组
    // 链表的内存管理由函数内部完成
	UInt32 ParseLEKeyLoadRequest(
		/*in */ UInt8             *RequestBuf,  //接收到的请求消息的存储区地址
		/*in */ UInt32             RquestLen,   //接收到的请求消息长度
		/*out*/ UInt32            *RequestId,   //请求消息的消息ID
		/*out*/ struct LEKeyInfo **head);       //存储链路解密密钥的链表的头指针


	/************************************************* 
    Function   ： GetListMember()
    Description： get LE key message from list 
    Input      ： head     :the head of list    
    Output     ： KeyID    :unique key identifier        
                  Key      :unique key identifier
                  ExTime   :calidity period of key in seconds
                  AttrData :data used as input to counter mode cipher	         
    Return     ： error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.
                  application  call GetListMember() once gets one LE key's message, untill 
                  list is blank(i.e. head = NULL)
    *************************************************/
    // 函数作用：获取具体的链路解密密钥，每调用一次返回一个密钥组
    //函数返回PARAMETER_ERROR。表示链表读空了
	UInt32 GetListMember(
		/*in */ struct LEKeyInfo **head,        //存储链路解密密钥的链表的头指针
		/*out*/ UInt32            *KeyID,       //链路解密密钥ID
		/*out*/ UInt8             *Key,         //链路解密密钥
		/*out*/ UInt32            *ExTime,      //密钥有效的时间长度
		/*out*/ UInt64            *AttrData);   //初始化AES盒的向量

    /************************************************* 
    Function   ： ParseBufToLen()
    Description： transform the message saved in memory to integer
    Input      ： Buf       :memory address of message
		          BufLEN    :the length of message 	memory		      
    Output     ：
    Return     ： integer match along with message saved in memory
    Others     :        
    *************************************************/ 
	UInt64 ParseBufToLen(
    	/*in */UInt8 *Buf,       //存储四个字节信息的空间地址
    	/*in */UInt32 BufLEN);   //信息空间长度
    	
    /************************************************* 
    Function   ： ParseLenToBuf()
    Description： transform integer to the message saved in memory 
    Input      ： IntNum       :integer want to transform	         	      
    Output     ： Buf          :memory address of message
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLenToBuf(
    	/*in */UInt32 IntNum,    //要填写的32位整数
    	/*out*/UInt8 *Buf);      //目标地址空间地址

private:
	MessageLength    *MyMessageLength;        //消息头（KEY in KLV struct）类指针
	MessageULName    *MyMessageULName;        //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;     //消息ID类指针
};

#endif /*LEKEYLOADREQUEST_H*/


