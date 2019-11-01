/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetEventListRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROJ)--GetEventListRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETEVENTLISTREQUEST_H
#define GETEVENTLISTREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventListRequest
{

public:

	GetEventListRequest();
	~GetEventListRequest();
	
	/************************************************* 
    Function   �� FormatGetEventListRequest()
    Description�� format 'GetEventListRequest' Auditorium Security Message 
    Input      �� StartTime     :Event list period start
                  EndTime       :Event list period stop
    Output     �� NewRequestBuf :memory address of GetEventListRequest
		          len           :the length of GetEventListRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventListRequest(
		/*in */ UInt32   StartTime,     //��־����ε���ʼʱ���
		/*in */ UInt32   EndTime,       //��־����ε���ֹʱ���
		/*out*/ UInt8   *NewRequestBuf, //������װ�õ� GetEventListRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32  *len);          //��װ�õ� GetEventListRequest ������Ϣ����
		
	/************************************************* 
    Function   �� ParseGetEventListRequest()
    Description�� Parse 'GetEventListRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of GetEventListRequest
		          RequestLen    :the length of GetEventListRequest 		
    Output     �� RequestId,    :Request Message id of GetEventListRequest
		          StartTime     :Event list period start
                  EndTime       :Event list period stop
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetEventListRequest(
		/*in */ UInt8  *RequestBuf,     //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,     //���յ���������Ϣ����
		/*out*/ UInt32 *RequestId,      //������Ϣ����ϢID
		/*out*/ UInt32 *StartTime,      //��־����ε���ʼʱ���
		/*out*/ UInt32 *EndTime);       //��־����ε���ֹʱ���

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	

};
#endif


