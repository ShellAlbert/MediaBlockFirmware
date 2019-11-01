/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� AuditResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--AuditResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef AUDITRESPONSE_H
#define AUDITRESPONSE_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"

class AuditResponse
{
public:

	AuditResponse();
	~AuditResponse();

    /************************************************* 
    Function   �� FormatAuditResponse()
    Description�� format 'AuditResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of AuditRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of AuditResponse
		          len             :the length of AuditResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatAuditResponse(
		/*in */ UInt32  RequestId,          //��ӦAuditRequest������Ϣ����ϢID
		/*in */ UInt8   ResponseStatus,     //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf,     //������װ�õ�AuditResponse�ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);               //��װ�õ�AuditResponse��Ϣ����

    /************************************************* 
    Function   �� FormatAuditResponse()
    Description�� Parse 'AuditResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of AuditResponse
		          ResponseLen    :length of AuditResponse 		
    Output     �� RequestId,     :Request Message id of AuditRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseAuditResponse(
		/*in */ UInt8  *ResponseBuf,        //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,        //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,          //��ӦAuditRequest������Ϣ����ϢID
		/*out*/ UInt8  *ResponseStatus);    //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:

	MessageLength    *MyMessageLength;      //��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;      //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;   //��ϢID��ָ��
};

#endif


