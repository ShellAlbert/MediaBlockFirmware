/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º requestId.h
Author     £º tangquanfa@oristartech.com
Date       £º 2012/02/21
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >

********************************************/
#ifndef REQUEST_ID_H
#define REQUEST_ID_H

#include "Const.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 GenerateNewRequestId( UInt8 *RequestIdBuf );
UInt32 ParseRequestId( UInt8 *RequestIdBuf );
UInt32 SetRequestId( UInt32 RequestIdNum, UInt8 *RequestIdBuf );

#ifdef __cplusplus
};

class requestId
{
public:

	requestId();
	~requestId();
	
    /************************************************* 
    Description: get request code
    Input      :
    Output     : request code(character format)
    Return     : error code, refer to const.h
    *************************************************/ 
	UInt32 GetRequestId(/*out*/UInt8 *RequestIdBuf);


	/************************************************* 
    Description: get request code
    Input      :
    Output     :
    Return     : request code(numerical)
    *************************************************/ 
	UInt32 GetRequestId();
	
	
    /************************************************* 
    Description	: parse request code
    Input		: RequestId			:request code(character format)
    Output		:
    Return		: request code(numerical)
    *************************************************/ 
	UInt32 ParseRequestId(/*in*/UInt8 *RequestId);


	/************************************************* 
    Description	: Generate a new request code
    Input		:
    Output		: RequestIdBuf		:request code(character format)
    Return		: error code, refer to const.h
    *************************************************/ 
	UInt32 GenerateNewRequestId(/*out*/UInt8 *RequestIdBuf);


	/************************************************* 
    Description	: format request code
    Input		: RequestIdNum		:request code(numerical)
    Output		: RequestIdBuf		:request code(character format)
    Return		: error code, refer to const.h
    *************************************************/
	UInt32 SetRequestId(/* in*/ UInt32 RequestIdNum,
	                    /*out*/ UInt8 *RequestIdBuf);

private:	

	static UInt32 RequestId;	//request code
};
#endif

#endif




