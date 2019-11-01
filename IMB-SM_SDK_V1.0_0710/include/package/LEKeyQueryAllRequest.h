/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyQueryAllRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROj)--LEKeyQueryAllRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYALLREQUEST_H
#define LEKEYQUERYALLREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryAllRequest
{
public:
	LEKeyQueryAllRequest();
	~LEKeyQueryAllRequest();
	
	/************************************************* 
    Function   �� FormatLEKeyQueryAllRequest()
    Description�� format 'LEKeyQueryAllRequest' Auditorium Security Message 
    Input      ��        
    Output     �� NewRequestBuf :memory address of LEKeyQueryAllRequest
		          len           :the length of LEKeyQueryAllRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatLEKeyQueryAllRequest(
		/*out*/ UInt8  *NewRequestBuf, //������װ�õ� LEKeyQueryAllRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);          //��װ�õ� LEKeyQueryAllRequest ������Ϣ����

	/************************************************* 
    Function   �� ParseLEKeyQueryAllRequest()
    Description�� Parse 'LEKeyQueryAllRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of LEKeyQueryAllRequest
		          RequestLen    :the length of LEKeyQueryAllRequest 		
    Output     �� RequestId,    :Request Message id of LEKeyQueryAllRequest		       
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseLEKeyQueryAllRequest(
		/* in*/ UInt8  *RequestBuf,    //���յ���������Ϣ�Ĵ洢����ַ
		/* in*/	UInt32  RequestLen,    //���յ���������Ϣ����
		/*out*/ UInt32 *RequestId);    //������Ϣ����ϢID

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* LEKEYQUERYALLREQUEST_H */




