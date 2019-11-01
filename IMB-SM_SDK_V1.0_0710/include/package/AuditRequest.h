/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� AuditRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--AuditRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef AUDITREQUEST_H
#define AUDITREQUEST_H

#include "package/MessageLength.h"
#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class AuditRequest
{
public:

	AuditRequest();
	~AuditRequest();
	
	/************************************************* 
    Function   �� FormatAuditRequest()
    Description�� format 'AuditRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	         
    Output     �� NewRequestBuf :memory address of AuditRequest
		          len           :the length of AuditRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatAuditRequest(
			/*in */ TEXT   *UserID,         //�����û����û�֤��ָ��
			/*out*/ UInt8  *NewRequestBuf,  //������װ�õ�AuditRequest������Ϣ�Ļ�������ַ
			/*out*/ UInt32 *len);           //��װ�õ�AuditRequest������Ϣ����

	/************************************************* 
    Function   �� ParseAuditRequest()
    Description�� Parse 'AuditRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of AuditRequest
		          RequestLen    :the length of AuditRequest 		
    Output     �� RequestId,    :Request Message id of AuditRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseAuditRequest(
			/*in */ UInt8  *RequestBuf,     //���յ���������Ϣ�Ĵ洢����ַ
			/*in */ UInt32  RequestLen,     //���յ���������Ϣ����
			/*out*/ UInt32 *RequestId,      //������Ϣ����ϢID
			/*out*/ TEXT   *UserID);        //����������Ϣ���û���֤��ָ��

private:
	MessageULName    *MyMessageULName;      //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;      //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;   //��ϢID��ָ��
};

#endif


