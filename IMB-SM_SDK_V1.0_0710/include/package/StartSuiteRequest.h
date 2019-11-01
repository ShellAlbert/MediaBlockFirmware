/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StartSuiteRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--StartSuiteRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STARTSUITEREQUEST_H
#define STARTSUITEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/MessageLength.h"
#include "package/Const.h"

class StartSuiteRequest
{
public:
	StartSuiteRequest();
	~StartSuiteRequest();

	/************************************************* 
    Function   �� FormatStartSuiteRequest()
    Description�� format 'StartSuiteRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	         
    Output     �� NewRequestBuf :memory address of StartSuiteRequest
		          len           :length of StartSuiteRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStartSuiteRequest(	
		/* in*/ TEXT   *UserID,        //�����û����û�֤��ָ��
		/*out*/ UInt8  *NewRequestBuf, //������װ�õ� StartSuiteRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);          //��װ�õ� StartSuiteRequest ������Ϣ����
		
	/************************************************* 
    Function   �� ParseStartSuiteRequest()
    Description�� Parse 'StartSuiteRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of StartSuiteRequest
		          RequestLen    :length of StartSuiteRequest 		
    Output     �� RequestId,    :Request Message id of StartSuiteRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseStartSuiteRequest(
		/*in */ UInt8  *RequestBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,   //���յ���������Ϣ����
		/*out*/ TEXT   *UserID,       //�����û����û�֤��ָ��
		/*out*/ UInt32 *RequestId);   //������Ϣ����ϢID

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* STARTSUITEREQUEST_H */


