/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： FirewareUpdateRequest.h
Author     ： huweihua@dadimedia.com
Date       ： 11/08/06
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--FirewareUpdateRequest
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >  
********************************************/
#ifndef FIREWAREUPDATEREQUEST_H
#define FIREWAREUPDATEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

const int   VERSIONLEN  = 16;
const int   HMACLEN     = 20;

const UInt8 FPGA_V6 	= 0x01;
const UInt8 FPGA_S6J 	= 0x02;
const UInt8 FPGA_S6M 	= 0x03;
const UInt8 IMBSM       = 0x04;

class FirewareUpdateRequest
{
public:
	
	FirewareUpdateRequest();
	~FirewareUpdateRequest();

	/************************************************* 
    Function   ： FormatFirewareUpdateRequest()
    Description： format 'FirewareUpdateRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	         
    Output     ： NewRequestBuf :memory address of FirewareUpdateRequest
		          len           :length of FirewareUpdateRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatFirewareUpdateRequest(	
		/* in*/ TEXT   *UserID,        //操作用户的用户证书指纹
		/* in*/ UInt32  UpdatePackLength,
		/* in*/ TEXT   *UpdatePack,
		/*out*/ UInt8  *NewRequestBuf, //接收组装好的 FirewareUpdateRequest 请求消息的缓冲区地址
		/*out*/ UInt32 *len);          //组装好的 FirewareUpdateRequest 请求消息长度
		
	/************************************************* 
    Function   ： ParseFirewareUpdateRequest()
    Description： Parse 'FirewareUpdateRequest'Auditorium Security Message 
    Input      ： RequestBuf    :memory address of FirewareUpdateRequest
		          RequestLen    :length of FirewareUpdateRequest 		
    Output     ： RequestId,    :Request Message id of FirewareUpdateRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseFirewareUpdateRequest(
		/* in*/ UInt8  *RequestBuf,
		/* in*/ UInt32  RequestLen,		
		/*out*/ TEXT   *UserID,       //操作用户的用户证书指纹
		/*out*/ UInt32 *RequestId);   //请求消息的消息ID
	
	
	UInt32 GetUpdatePackLength();
//	UInt8  GetUpdateTyp();
//	void   GetUpdatePackVersion(TEXT *TempVersion);
	void   GetUpdatePack(TEXT *TempUpdatePack);
//	void   GetUpdatePackHMAC(TEXT *TempUpdatePackHMAC);	
	/*****************************************************
	Function   :  ParseBufToLen()
	Description:  transform the message saved in memory to integer
	Input      :  Buf     : memory address of message
	              BufLen  : the length of message memory
	Output     :  
	Return     :  integer match along with message saved in memory
	Others     :
	*****************************************************/
	UInt64 ParseBufToLen(
		/* in*/UInt8 *Buf,
		/* in*/UInt32 BufLen);

	/*****************************************************
	Function   :  ParseLenToBuf()
	Description:  transform integer to the message saved in memory
	Input      :  IntNum  : integer want to transform 
				  BufLen  :the length of message 	memory
	Output     :  Buf     : memory address of message
	Return     :  error code, refer to Const.h
	Others     :
	*****************************************************/
	UInt64 ParseLenToBuf(
		/* in*/UInt32 IntNum,
		/* in*/UInt32  BufLen,
		/*out*/UInt8 *Buf);
		
private:
	
	struct SUpdatePackInfo
	{
//		UInt8   UpdateType;
//		TEXT    Version[VERSIONLEN];
//		TEXT    HMAC[HMACLEN];
		UInt32  UpdatePackLength;
		TEXT   *UpdatePack;
	};	
	
	struct SUpdatePackInfo* UpdatePackInfo;
	MessageULName    *MyMessageULName;       //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;       //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId;    //消息ID类指针	
};

#endif /* FIREWAREUPDATEREQUEST_H */


