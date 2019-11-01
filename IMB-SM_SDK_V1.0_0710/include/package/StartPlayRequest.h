/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StartPlayRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/08/09
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--StartPlayRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
huweihua@dadimedia.com   11/06/24           implement request according to new message struct
********************************************/
#ifndef STARTPLAYREQUEST_H
#define STARTPLAYREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"


//startplay for single CPLs and KDMs
#if 0
class StartPlayRequest
{
public:
	
	StartPlayRequest();
	~StartPlayRequest();
	
	/*************************************************
    Function   �� FormatStartPlayRequest()
    Description�� format 'StartPlayRequest' Auditorium Security Message
    Input      �� UserID        :Certificate Thumbprint of uesr
             	    CPLId,        :CPL file ID
    Output     �� NewRequestBuf :memory address of CPLValidateRequest
		              len           :length of CPLValidateRequest
    Return     �� error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 FormatStartPlayRequest(
  	/* in*/ TEXT    *UserID,
  	/* in*/ TEXT    *CPLId,
  	/*out*/ UInt8   *NewRequestBuf,
  	/*out*/ UInt32  *len);
  	
	/************************************************* 
    Function   �� ParseStartPlayRequest()
    Description�� Parse 'StartPlayRequest'Auditorium Security Message 
    Input      �� RequestBuf     :memory address of StartPlayRequest
		              RequestLen     :length of StartPlayRequest 		
    Output     �� RequestId,     :Request Message id of AuditRequest
		              UserID         :Certificate Thumbprint of uesr
		              CPLId,         :CPL file ID
    Return     �� error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 ParseStartPlayRequest(
  	/*in */ UInt8   *RequestBuf,
  	/*in */ UInt32   RequestLen,
  	/*out*/ UInt32  *RequestId,
  	/*out*/ TEXT    *UserID,
  	/*out*/ TEXT    *CPLId);
  	
private:
	
	MessageULName    *MyMessageULName;		//message header
	MessageLength    *MyMessageLength;		//message body length
	MessageRequestId *MyMessageRequestId;	//message ID
};
#endif


//-----------------------------------------------------------------------------------------
//startplay for multi CPLs and KDMs 
//add by huweihua 11/06/24
#if 1
class StartPlayRequest
{
public:
	
	StartPlayRequest();
	~StartPlayRequest();
	
	/*************************************************
    Function   �� FormatStartPlayRequest()
    Description�� format 'StartPlayRequest' Auditorium Security Message
    Input      �� UserID        :Certificate Thumbprint of uesr
             	    CPLId,        :CPL file ID
             	    CPLTotalCount :CPL Total Count
             	    CurCPLIndex   :current cpl index
    Output     �� NewRequestBuf :memory address of CPLValidateRequest
		              len           :length of CPLValidateRequest
    Return     �� error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 FormatStartPlayRequest(
  	/* in*/ TEXT    *UserID,
  	/* in*/ TEXT    *CPLId,
  	/* in*/ UInt8   CPLTotalCount,
   	/* in*/ UInt8   CurCPLIndex,
   	/* in*/ UInt32	HorizontalPixel,
   	/* in*/ UInt32	VerticalPixel,   	
  	/*out*/ UInt8   *NewRequestBuf,
  	/*out*/ UInt32  *len);


//  UInt32 FormatStartPlayRequest(
//  	/* in*/ TEXT    *UserID,
//  	/* in*/ TEXT    *CPLId,
//  	/* in*/ UInt8   CPLTotalCount,
//   	/* in*/ UInt8   CurCPLIndex,  	
//  	/*out*/ UInt8   *NewRequestBuf,
//  	/*out*/ UInt32  *len);  	
	/************************************************* 
    Function   �� ParseStartPlayRequest()
    Description�� Parse 'StartPlayRequest'Auditorium Security Message 
    Input      �� RequestBuf     :memory address of StartPlayRequest
		              RequestLen     :length of StartPlayRequest 		
    Output     �� RequestId,     :Request Message id of AuditRequest
		              UserID         :Certificate Thumbprint of uesr
		              CPLId,         :CPL file ID
    Return     �� error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 ParseStartPlayRequest(
  	/*in */ UInt8   *RequestBuf,
  	/*in */ UInt32   RequestLen,
  	/*out*/ UInt32  *RequestId,
  	/*out*/ TEXT    *UserID,
  	/*out*/ TEXT    *CPLId,
  	/*out*/ UInt8   *CPLTotalCount,
  	/*out*/ UInt8   *CurCPLIndex,
  	/*out*/ UInt32  *HorizontalPixel,
  	/*out*/ UInt32  *VerticalPixel);

  /************************************************* 
    Function   �� ParseBufToLen()
    Description�� transform the message saved in memory to integer
    Input      �� Buf       :memory address of message
    	          BufLen    :the length of message 	memory		      
    Output     ��
    Return     �� integer match along with message saved in memory
    Others     :        
    *************************************************/ 			
    UInt32 ParseBufToLen(
            /*in*/UInt8 *Buf, 
            /*in*/UInt32 BufLen);

    /************************************************* 
    Function   �� ParseLenToBuf()
    Description�� transform integer to the message saved in memory 
    Input      �� IntNum       :integer want to transform	
             	  BufLen       :the length of message 	memory
    Output     �� Buf          :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/            
    UInt32 ParseLenToBuf(
            /* in*/UInt32  IntNum,
            /* in*/UInt32  BufLen,
            /*out*/UInt8  *Buf);		
private:
	
	MessageULName    *MyMessageULName;		//message header
	MessageLength    *MyMessageLength;		//message body length
	MessageRequestId *MyMessageRequestId;	//message ID
};
#endif



#endif

