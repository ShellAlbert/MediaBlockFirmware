/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� ClearCSPsRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 11/08/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--ClearCSPsRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >  
********************************************/
#ifndef CLEARCSPSREQUEST_H
#define CLEARCSPSREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

class ClearCSPsRequest
{
public:
	ClearCSPsRequest();
	~ClearCSPsRequest();

	/************************************************* 
    Function   �� FormatClearCSPsRequest()
    Description�� format 'ClearCSPsRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	         
    Output     �� NewRequestBuf :memory address of ClearCSPsRequest
		          len           :length of ClearCSPsRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatClearCSPsRequest(	
		/* in*/ TEXT   *UserID,        //�����û����û�֤��ָ��
		/*out*/ UInt8  *NewRequestBuf, //������װ�õ� ClearCSPsRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);          //��װ�õ� ClearCSPsRequest ������Ϣ����
		
	/************************************************* 
    Function   �� ParseClearCSPsRequest()
    Description�� Parse 'ClearCSPsRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of ClearCSPsRequest
		          RequestLen    :length of ClearCSPsRequest 		
    Output     �� RequestId,    :Request Message id of ClearCSPsRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseClearCSPsRequest(
		/*in */ UInt8  *RequestBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,   //���յ���������Ϣ����
		/*out*/ TEXT   *UserID,       //�����û����û�֤��ָ��
		/*out*/ UInt32 *RequestId);   //������Ϣ����ϢID

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* CLEARCSPSREQUEST_H */


