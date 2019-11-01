/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º klvLen.h
Author     £º tangquanfa@oristartech.com
Date       £º 2012/02/21
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >

********************************************/
#ifndef KLV_LEN_H
#define KLV_LEN_H

#include "Const.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 SetKLV_Len( UInt32 Len, UInt8 *KLV_LenBuf );
UInt32 ParseKLV_Len( UInt8 *KLV_LenBuf );

#ifdef __cplusplus
};
class klvLen
{
public:
	klvLen();
	~klvLen();
	/************************************************* 
    Description	: get length
    Input		:
    Output		:
    Return		: length(character format) 
    *************************************************/
	const UInt8 *GetKLV_Len();


	/************************************************* 
    Description	: parse length
    Input		: KLV_LenBuf		:length(character format)
    Output		:
    Return		: length(numerical)
    *************************************************/
	UInt32 ParseKLV_Len( /*in*/UInt8 *KLV_LenBuf );


	/************************************************* 
    Description	: set length
    Input		: Len				:length(numerical)
    Output		:
    Return		: error code, refer to const.h
    *************************************************/
	UInt32 SetKLV_Len( /*in*/UInt32 Len );


	/************************************************* 
    Description	: format length
    Input		: Len				:length(numerical)
    Output		: KLV_LenBuf		:length(character format)
    Return		: error code, refer to const.h
    *************************************************/
	UInt32 SetKLV_Len( /* in*/UInt32 Len,
	                 /*out*/UInt8 *KLV_LenBuf );
private:
	UInt8 KLV_Len[KLV_LEN_LEN];	//length buffer
};
#endif

#endif
