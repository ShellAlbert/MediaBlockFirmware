/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� DeleteKDMRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/08/09
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--DeleteKDMRequest
Others     :  
History    �� 
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
    Function   �� FormatDeleteKDMRequest()
    Description�� format 'DeleteKDMRequest' Auditorium Security Message
    Input      �� UserID        :Certificate Thumbprint of uesr
    							KDMId,        :KDM file ID
             	    CPLId,        :CPL file ID
    Output     �� NewRequestBuf :memory address of DeleteKDMRequest
		              len           :length of DeleteKDMRequest
    Return     �� error code, refer to Const.h
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
    Function   �� ParseDeleteKDMRequest()
    Description�� Parse 'DeleteKDMRequest'Auditorium Security Message 
    Input      �� RequestBuf     :memory address of DeleteKDMRequest
		              RequestLen     :length of DeleteKDMRequest 		
    Output     �� RequestId,     :Request Message id of AuditRequest
		              UserID         :Certificate Thumbprint of uesr
		              KDMId,         :KDM file ID
		              CPLId,         :CPL file ID
    Return     �� error code, refer to Const.h
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

