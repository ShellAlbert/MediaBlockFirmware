/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º MessageRequestId.h
Author     £º huweihua@dadimedia.com
Date       £º 10/03/01
Version    £º v1.0
Description£º Auditorium Security Message RequestId class
Others     :  
History    £º 
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
    Function   £ºGetRequestId()
    Description£ºtransform the Request Id message saved in memory to integer
    Input      : RequestIdBuf  :memory address of LEKeyId message
    Output     £º
    Return     £ºRequest Id (integer) match along with Request Id message saved in memory
    Others     : 
    *************************************************/ 
	UInt32 GetRequestId(/*out*/UInt8 *RequestIdBuf);
	
	/************************************************* 
    Function   £ºGetRequestId()
    Description£ºtransform the Request Id message saved in memory to integer
    Input      : 
    Output     £º
    Return     £ºRequest Id (integer) 
    Others     : 
    *************************************************/ 
	UInt32 GetRequestId();
	
	
    /************************************************* 
    Function   ParseRequestId()
    Description£ºtransform the Request Id message saved in memory to integer
    Input      : MessageRequestId  :memory address of LEKeyId message
    Output     £º
    Return     £ºRequest Id (integer) match along with Request Id message saved in memory
    Others     : 
    *************************************************/ 
	UInt32 ParseRequestId(/*in*/UInt8 *MessageRequestId);
	/************************************************* 
    Function   GenerateNewRequestId()
    Description£ºgenerate a new request id 
    Input      : 
    Output     £ºMessageRequestId  : request id buffer
    Return     £ºrequest id value(integer)
    Others     : 
    *************************************************/ 
	UInt32 GenerateNewRequestId(/*out*/UInt8 *MessageRequestId);
	/************************************************* 
    Function   SetRequestId()
    Description£ºtransform the Request Id message saved in memory to integer
    Input      : RequestIdNum	-	request id value (integer)
    Output     : RequestIdBuf	-	request id buffer(char *)
    Return     £ºRequest Id (integer) 
    Others     : 
    *************************************************/
	UInt32 SetRequestId(/* in*/ UInt32 RequestIdNum,
	                    /*out*/ UInt8 *RequestIdBuf);

private:	

	static UInt32 RequestId;
};

#endif




