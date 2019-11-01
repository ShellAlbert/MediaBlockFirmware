/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StopSuiteRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message (SMS->SM)--StopSuiteRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STOPSUITEREQUEST_H
#define STOPSUITEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

class StopSuiteRequest
{
public:
	StopSuiteRequest();
	~StopSuiteRequest();

	/************************************************* 
    Function   �� FormatStopSuiteRequest()
    Description�� format 'StopSuiteRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	         
    Output     �� NewRequestBuf :memory address of StopSuiteRequest
		          len           :length of StopSuiteRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 	
	UInt32 FormatStopSuiteRequest(	
		/* in*/ TEXT   *UserID,       //�����û����û�֤��ָ��
		/*out*/ UInt8  *NewRequestBuf,//������װ�õ� StopSuiteRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);         //��װ�õ� StopSuiteRequest ������Ϣ����

	
	/************************************************* 
    Function   �� ParseAuditRequest()
    Description�� Parse 'StopSuiteRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of StopSuiteRequest
		          RequestLen    :length of StopSuiteRequest 		
    Output     �� RequestId,    :Request Message id of StopSuiteRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
		UInt32 ParseStopSuiteRequest(
		/*in */ UInt8  *RequestBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,   //���յ���������Ϣ����
		/*out*/ TEXT   *UserID,       //�����û����û�֤��ָ��
		/*out*/ UInt32 *RequestId);   //����������Ϣ���û���֤��ָ��
		
private:

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��
};

#endif /* STARTSUITEREQUEST_H */
 

