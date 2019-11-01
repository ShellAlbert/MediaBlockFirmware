/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MessageRequestId.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message RequestId class
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef MESSAGEREQUESTID_H
#define MESSAGEREQUESTID_H

#include "package/Const.h"

class MessageRequestId
{
public:

	MessageRequestId();
	~MessageRequestId();
	
    /************************************************* 
    Function   ��GetRequestId()
    Description��transform the Request Id message saved in memory to integer
    Input      : RequestIdBuf  :memory address of LEKeyId message
    Output     ��
    Return     ��Request Id (integer) match along with Request Id message saved in memory
    Others     : 
    *************************************************/ 
	UInt32 GetRequestId(/*out*/UInt8 *RequestIdBuf);
	
	/************************************************* 
    Function   ��GetRequestId()
    Description��transform the Request Id message saved in memory to integer
    Input      : 
    Output     ��
    Return     ��Request Id (integer) 
    Others     : 
    *************************************************/ 
	UInt32 GetRequestId();
	
	
    /************************************************* 
    Function   ParseRequestId()
    Description��transform the Request Id message saved in memory to integer
    Input      : MessageRequestId  :memory address of LEKeyId message
    Output     ��
    Return     ��Request Id (integer) match along with Request Id message saved in memory
    Others     : 
    *************************************************/ 
	UInt32 ParseRequestId(/*in*/UInt8 *MessageRequestId);
	/************************************************* 
    Function   GenerateNewRequestId()
    Description��generate a new request id 
    Input      : 
    Output     ��MessageRequestId  : request id buffer
    Return     ��request id value(integer)
    Others     : 
    *************************************************/ 
	UInt32 GenerateNewRequestId(/*out*/UInt8 *MessageRequestId);
	/************************************************* 
    Function   SetRequestId()
    Description��transform the Request Id message saved in memory to integer
    Input      : RequestIdNum	-	request id value (integer)
    Output     : RequestIdBuf	-	request id buffer(char *)
    Return     ��Request Id (integer) 
    Others     : 
    *************************************************/
	UInt32 SetRequestId(/* in*/ UInt32 RequestIdNum,
	                    /*out*/ UInt8 *RequestIdBuf);

private:	

	static UInt32 RequestId;
};

#endif




