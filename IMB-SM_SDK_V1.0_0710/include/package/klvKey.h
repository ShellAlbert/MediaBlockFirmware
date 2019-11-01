/********************************************* 
Copyright (C), 2012-2020, oristartech Co., Ltd.
ModuleName :
FileName   £º klvKey.h
Author     £º tangquanfa@oristartech.com
Date       £º 2012/02/21
Version    £º v1.0
Description£º
History    £º 
      < Author >    			< Date >             < Modification >

********************************************/
#ifndef KLV_KEY_H
#define KLV_KEY_H

#include "Const.h"

#ifdef __cplusplus
extern "C" {
#endif

UInt32 SetKLV_Key( UInt32 Key, UInt8 *KLV_KeyBuf );
UInt32 ParseKLV_Key( UInt8 *KLV_KeyBuf );

#ifdef __cplusplus
};

class klvKey
{

public:
	klvKey();
	~klvKey();   

//	const UInt8 *GetKLV_Key();
//	UInt32 SetType( UInt8 Type );
//	UInt8 GetType();

	/************************************************* 
    Description	: format key
    Input		: key(numerical)
    Output		: KLV_KeyBuf		:key(character format)
    Return		: error code, refer to const.h
    *************************************************/
	UInt32 SetKLV_Key( /* in*/ UInt32 Key, /*out*/ UInt8 *KLV_KeyBuf );
					 
	/************************************************* 
    Description	: parse key
    Input		: KLV_KeyBuf			:key(character format)
    Output		:
    Return		: key(numerical)
    *************************************************/
	UInt32 ParseKLV_Key( /*in*/UInt8 *KLV_KeyBuf );
	
private:	
	UInt8 KLV_Key[KLV_KEY_LEN];	//key buffer
};
#endif


#endif
