/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º StartPlayRequest.h
Author     £º cuijixin@dadimedia.com
Date       £º 10/08/09
Version    £º v1.0
Description£º Auditorium Security Message(SMS->SM)--StartPlayRequest
Others     :  
History    £º 
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
    Function   £º FormatStartPlayRequest()
    Description£º format 'StartPlayRequest' Auditorium Security Message
    Input      £º UserID        :Certificate Thumbprint of uesr
             	    CPLId,        :CPL file ID
    Output     £º NewRequestBuf :memory address of CPLValidateRequest
		              len           :length of CPLValidateRequest
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 FormatStartPlayRequest(
  	/* in*/ TEXT    *UserID,
  	/* in*/ TEXT    *CPLId,
  	/*out*/ UInt8   *NewRequestBuf,
  	/*out*/ UInt32  *len);
  	
	/************************************************* 
    Function   £º ParseStartPlayRequest()
    Description£º Parse 'StartPlayRequest'Auditorium Security Message 
    Input      £º RequestBuf     :memory address of StartPlayRequest
		              RequestLen     :length of StartPlayRequest 		
    Output     £º RequestId,     :Request Message id of AuditRequest
		              UserID         :Certificate Thumbprint of uesr
		              CPLId,         :CPL file ID
    Return     £º error code, refer to Const.h
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
    Function   £º FormatStartPlayRequest()
    Description£º format 'StartPlayRequest' Auditorium Security Message
    Input      £º UserID        :Certificate Thumbprint of uesr
             	    CPLId,        :CPL file ID
             	    CPLTotalCount :CPL Total Count
             	    CurCPLIndex   :current cpl index
    Output     £º NewRequestBuf :memory address of CPLValidateRequest
		              len           :length of CPLValidateRequest
    Return     £º error code, refer to Const.h
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
    Function   £º ParseStartPlayRequest()
    Description£º Parse 'StartPlayRequest'Auditorium Security Message 
    Input      £º RequestBuf     :memory address of StartPlayRequest
		              RequestLen     :length of StartPlayRequest 		
    Output     £º RequestId,     :Request Message id of AuditRequest
		              UserID         :Certificate Thumbprint of uesr
		              CPLId,         :CPL file ID
    Return     £º error code, refer to Const.h
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
    Function   £º ParseBufToLen()
    Description£º transform the message saved in memory to integer
    Input      £º Buf       :memory address of message
    	          BufLen    :the length of message 	memory		      
    Output     £º
    Return     £º integer match along with message saved in memory
    Others     :        
    *************************************************/ 			
    UInt32 ParseBufToLen(
            /*in*/UInt8 *Buf, 
            /*in*/UInt32 BufLen);

    /************************************************* 
    Function   £º ParseLenToBuf()
    Description£º transform integer to the message saved in memory 
    Input      £º IntNum       :integer want to transform	
             	  BufLen       :the length of message 	memory
    Output     £º Buf          :memory address of message
    Return     £º error code, refer to Const.h
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

