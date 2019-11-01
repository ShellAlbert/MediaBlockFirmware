/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LogoutRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/08/07
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--LogoutRequest
Others     :  
History    �� 
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
    Function   �� FormatLogoutRequest()
    Description�� format 'LogoutRequest' Auditorium Security Message
    Input      �� UserID        :Certificate Thumbprint of uesr
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Output     �� NewRequestBuf :memory address of LogoutRequest
		              len           :the length of LogoutRequest
    Return     �� error code, refer to Const.h
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
    Function   �� ParseLogoutRequest()
    Description�� Parse 'LogoutRequest'Auditorium Security Message
    Input      �� RequestBuf    :memory address of LogoutRequest
		          RequestLen    :the length of LogoutRequest
    Output     �� RequestId,    :Request Message id of LogoutRequest
		              UserID        :Certificate Thumbprint of uesr
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Return     �� error code, refer to Const.h
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
    Function   �� FormatLogoutRequest()
    Description�� format 'LogoutRequest' Auditorium Security Message
    Input      �� UserID        :Certificate Thumbprint of uesr
                  role          :the role of user
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value                  
    Output     �� NewRequestBuf :memory address of LogoutRequest
		              len           :the length of LogoutRequest
    Return     �� error code, refer to Const.h
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
	  Function   �� ParseLogoutRequest()
	  Description�� Parse 'LogoutRequest'Auditorium Security Message
	  Input      �� RequestBuf    :memory address of LogoutRequest
		          RequestLen    :the length of LogoutRequest
	  Output     �� RequestId,    :Request Message id of LogoutRequest
		              UserID        :Certificate Thumbprint of uesr
		              Role          :role of user
	                SingnedAglth  :Singed aglthmodth
	                SingnedValue  :Singed value                 
	  Return     �� error code, refer to Const.h
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
    Function   �� SetLen()
    Description�� transform integer to the message saved in memory
    Input      �� Len       :integer want to transform
    Output     �� Buf       :memory address of message
    Return     �� error code, refer to Const.h
    Others     :
  *************************************************/
  UInt32 SetLen(
    /* in*/UInt32  Len,
    /*out*/UInt8  *Buf);
    
	/*************************************************
    Function   �� ParseLen()
    Description�� transform the message saved in memory to integer
    Input      �� Buf       :memory address of message
    Output     ��
    Return     �� integer match along with message saved in memory
   	Others     :
  *************************************************/
	UInt32 ParseLen(
     /*in*/ UInt8  *Buf);
	
	MessageULName    *MyMessageULName;		//message header
	MessageLength    *MyMessageLength;		//message body length
	MessageRequestId *MyMessageRequestId;	//message id
};

#endif


