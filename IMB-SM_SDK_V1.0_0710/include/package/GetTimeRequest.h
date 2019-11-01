/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetTimeRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROJ)--GetTimeRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETTIMEREQUEST_H
#define GETTIMEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetTimeRequest
{

public:

	GetTimeRequest();
	~GetTimeRequest();

	/************************************************* 
    Function   �� FormatGetTimeRequest()
    Description�� format 'GetTimeRequest' Auditorium Security Message 
    Input      ��         
    Output     �� NewRequestBuf :memory address of GetTimeRequest
		          len           :the length of GetTimeRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatGetTimeRequest(
		/*out*/ UInt8  *NewRequestBuf, //������װ�õ� GetTimeRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);          //��װ�õ� GetTimeRequest ������Ϣ����
		
	/************************************************* 
    Function   �� ParseGetTimeRequest()
    Description�� Parse 'AuditRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of GetTimeRequest
		          RequestLen    :the length of GetTimeRequest 		
    Output     �� RequestId,    :Request Message id of GetTimeRequest		          
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetTimeRequest(
		/*in */ UInt8  *RequestBuf,    //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,    //���յ���������Ϣ����
		/*out*/ UInt32 *RequestId);    //������Ϣ����ϢID
private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��

};
#endif


