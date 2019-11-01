/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� SMSQuerySPBRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--SMSQuerySPBRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef SMSQUERYSPBREQUEST_H
#define SMSQUERYSPBREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class SMSQuerySPBRequest
{
public:

	SMSQuerySPBRequest();
	~SMSQuerySPBRequest();
	
	/************************************************* 
    Function   �� FormatSMSQuerySPBRequest()
    Description�� format 'SMSQuerySPBRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	      
    Output     �� NewRequestBuf :memory address of SMSQuerySPBRequest
		          len           :length of SMSQuerySPBRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSMSQuerySPBRequest(
	    /*in */ TEXT   *UserID,        //Certificate Thumbprint of uesr	
		/*out*/ UInt8  *NewRequestBuf, //������װ�õ� SMSQuerySPBRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);          //��װ�õ� SMSQuerySPBRequest ������Ϣ����

 	/* ************************************************ 
    Function   �� ParseSMSQuerySPBRequest()
    Description�� Parse 'SMSQuerySPBRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of SMSQuerySPBRequest
		          RequestLen    :length of SMSQuerySPBRequest 		
    Output     �� RequestId,    :Request Message id of SMSQuerySPBRequest	
    	          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    ************************************************ */ 
	UInt32 ParseSMSQuerySPBRequest(
		/*in */ UInt8  *RequestBuf,    //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,    //���յ���������Ϣ����
		/*out*/ UInt32 *RequestId,     //������Ϣ����ϢID
		/*out*/ TEXT   *UserID);    

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��		
};
#endif


