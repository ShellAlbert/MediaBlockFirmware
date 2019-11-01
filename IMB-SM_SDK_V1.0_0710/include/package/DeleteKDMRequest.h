/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º DeleteKDMRequest.h
Author     £º cuijixin@dadimedia.com
Date       £º 10/08/09
Version    £º v1.0
Description£º Auditorium Security Message(SMS->SM)--DeleteKDMRequest
Others     :  
History    £º 
      < Author >    			< Date >             < Modification >
********************************************/
#ifndef DELETEKDMREQUEST_H
#define DELETEKDMREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class DeleteKDMRequest
{
public:
	
	DeleteKDMRequest();
	~DeleteKDMRequest();
	
	/*************************************************
    Function   £º FormatDeleteKDMRequest()
    Description£º format 'DeleteKDMRequest' Auditorium Security Message
    Input      £º UserID        :Certificate Thumbprint of uesr
    							KDMId,        :KDM file ID
             	    CPLId,        :CPL file ID
    Output     £º NewRequestBuf :memory address of DeleteKDMRequest
		              len           :length of DeleteKDMRequest
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 FormatDeleteKDMRequest(
  	/*in */ TEXT     *UserID,
  	/*in */ TEXT     *KDMId,
  	/*in */ TEXT     *CPLId,
  	/*out*/ UInt8    *NewRequestBuf,
  	/*out*/ UInt32   *len
  );
  
  /************************************************* 
    Function   £º ParseDeleteKDMRequest()
    Description£º Parse 'DeleteKDMRequest'Auditorium Security Message 
    Input      £º RequestBuf     :memory address of DeleteKDMRequest
		              RequestLen     :length of DeleteKDMRequest 		
    Output     £º RequestId,     :Request Message id of AuditRequest
		              UserID         :Certificate Thumbprint of uesr
		              KDMId,         :KDM file ID
		              CPLId,         :CPL file ID
    Return     £º error code, refer to Const.h
    Others     :        
  *************************************************/
  UInt32 ParseDeleteKDMRequest(
  	/*in */ UInt8   *RequestBuf,
  	/*in */ UInt32   RequestLen,
  	/*out*/ UInt32  *RequestId,
  	/*out*/ TEXT    *UserID,
  	/*out*/ TEXT    *KDMId,
  	/*out*/ TEXT    *CPLId
  );
  
private:
	
	MessageULName    *MyMessageULName;
	MessageLength    *MyMessageLength;
	MessageRequestId *MyMessageRequestId;
};

#endif

