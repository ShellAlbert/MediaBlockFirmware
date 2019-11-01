/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º LogoutRequest.h
Author     £º cuijixin@dadimedia.com
Date       £º 10/08/07
Version    £º v1.0
Description£º Auditorium Security Message(SMS->SM)--LogoutRequest
Others     :  
History    £º 
      < Author >    			< Date >             < Modification >
   
********************************************/
#ifndef LOGOUTREQUEST_H
#define LOGOUTREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LogoutRequest
{
public:
	
	LogoutRequest();
	~LogoutRequest();

#if 0
//----------------old version------------------	
	/************************************************* 
    Function   £º FormatLogoutRequest()
    Description£º format 'LogoutRequest' Auditorium Security Message
    Input      £º UserID        :Certificate Thumbprint of uesr
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Output     £º NewRequestBuf :memory address of LogoutRequest
		              len           :the length of LogoutRequest
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 FormatLogoutRequest(
  	/* in*/ TEXT   *UserID,
  	/* in*/ UInt32  SignedAglth,
  	/* in*/ TEXT   *SignedValue,
  	/* in*/ TEXT   *CertChain,
  	/*out*/ UInt8  *NewRequestBuf,
  	/*out*/ UInt32 *len);
  	
	/************************************************* 
    Function   £º ParseLogoutRequest()
    Description£º Parse 'LogoutRequest'Auditorium Security Message
    Input      £º RequestBuf    :memory address of LogoutRequest
		          RequestLen    :the length of LogoutRequest
    Output     £º RequestId,    :Request Message id of LogoutRequest
		              UserID        :Certificate Thumbprint of uesr
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Return     £º error code, refer to Const.h
    Others     :
  *************************************************/
  UInt32 ParseLogoutRequest(
  	/*in */ UInt8   *RequestBuf,
  	/*in */ UInt32   RequestLen,
  	/*out*/ UInt32  *RequestId,
  	/*out*/ TEXT    *UserID,
  	/*out*/ UInt32  *SignedAglth,
  	/*out*/ TEXT    *SignedValue,
  	/*out*/ TEXT    *CertChain);
//-------------------------------------------------------
#endif


#if 1
//----------------new version--------------------------
	/************************************************* 
    Function   £º FormatLogoutRequest()
    Description£º format 'LogoutRequest' Auditorium Security Message
    Input      £º UserID        :Certificate Thumbprint of uesr
                  role          :the role of user
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value                  
    Output     £º NewRequestBuf :memory address of LogoutRequest
		              len           :the length of LogoutRequest
    Return     £º error code, refer to Const.h
    Others     :  write by huweihua@dadimedia.com     
  *************************************************/
	UInt32 FormatLogoutRequest(
			/* in*/ TEXT   *UserID,
			/* in*/ TEXT   *Role,		
	  	/* in*/ UInt32  SignedAglth,
	  	/* in*/ TEXT   *SignedValue,
	  	/*out*/ UInt8  *NewRequestBuf,
	  	/*out*/ UInt32 *len);
  	
	/************************************************* 
	  Function   £º ParseLogoutRequest()
	  Description£º Parse 'LogoutRequest'Auditorium Security Message
	  Input      £º RequestBuf    :memory address of LogoutRequest
		          RequestLen    :the length of LogoutRequest
	  Output     £º RequestId,    :Request Message id of LogoutRequest
		              UserID        :Certificate Thumbprint of uesr
		              Role          :role of user
	                SingnedAglth  :Singed aglthmodth
	                SingnedValue  :Singed value                 
	  Return     £º error code, refer to Const.h
	  Others     :  write by huweihua@dadimedia.com   
	*************************************************/
	UInt32 ParseLogoutRequest(
	  	/*in */ UInt8   *RequestBuf,
	  	/*in */ UInt32   RequestLen,
	  	/*out*/ UInt32  *RequestId,
	  	/*out*/ TEXT    *UserID,
	  	/*out*/ TEXT    *Role,  	
	  	/*out*/ UInt32  *SignedAglth,
	  	/*out*/ TEXT    *SignedValue);
//-----------------------------------------------------
#endif
private:
	
	/*************************************************
    Function   £º SetLen()
    Description£º transform integer to the message saved in memory
    Input      £º Len       :integer want to transform
    Output     £º Buf       :memory address of message
    Return     £º error code, refer to Const.h
    Others     :
  *************************************************/
  UInt32 SetLen(
    /* in*/UInt32  Len,
    /*out*/UInt8  *Buf);
    
	/*************************************************
    Function   £º ParseLen()
    Description£º transform the message saved in memory to integer
    Input      £º Buf       :memory address of message
    Output     £º
    Return     £º integer match along with message saved in memory
   	Others     :
  *************************************************/
	UInt32 ParseLen(
     /*in*/ UInt8  *Buf);
	
	MessageULName    *MyMessageULName;		//message header
	MessageLength    *MyMessageLength;		//message body length
	MessageRequestId *MyMessageRequestId;	//message id
};

#endif


