/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetEventIDRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROJ)--GetEventIDRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/

#ifndef GETEVENTIDREQUEST_H
#define GETEVENTIDREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventIDRequest
{

public:

	GetEventIDRequest();
	~GetEventIDRequest();
	
	/************************************************* 
    Function   �� FormatGetEventIDRequest()
    Description�� format 'GetEventIDRequest' Auditorium Security Message 
    Input      �� EventId       :ID of the requested event	         
    Output     �� NewRequestBuf :memory address of GetEventIDRequest
		          len           :the length of GetEventIDRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventIDRequest(
		/*in */ UInt32   EventId,       //�¼�ID
		/*out*/ UInt8   *NewRequestBuf, //������װ�õ� GetEventIDRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32  *len);          //��װ�õ� GetEventIDRequest ������Ϣ����

	/************************************************* 
    Function   �� ParseGetEventIDRequest()
    Description�� Parse 'GetEventIDRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of GetEventIDRequest
		          RequestLen    :the length of GetEventIDRequest 		
    Output     �� RequestId,    :Request Message id of GetEventIDRequest
		          EventId       :ID of the requested event
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseGetEventIDRequest(
		/*in */ UInt8  *RequestBuf,     //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,     //���յ���������Ϣ����
		/*out*/ UInt32 *RequestId,      //������Ϣ����ϢID
    	/*out*/	UInt32 *EventId);       //�¼�ID

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif


