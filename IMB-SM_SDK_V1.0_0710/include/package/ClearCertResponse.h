/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� ClearCertResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 11/08/06
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--ClearCertResponse
Others     :  
History    �� 
              < Author >    			     < Date >         < Modification >
     zhangliang@dadimedia.com        10/10/11           Add comment 
********************************************/
#ifndef CLEARCERTRESPONSE_H
#define CLEARCERTRESPONSE_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"

class ClearCertResponse
{
public:

	ClearCertResponse();
	~ClearCertResponse();

    /************************************************* 
    Function   �� FormatClearCertResponse()
    Description�� format 'ClearCertResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of SetCertChainRequest 
                  CertType        :certificate type  
    	          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of ClearCertResponse
    	          len             :the length of ClearCertResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatClearCertResponse(
		/*in */ UInt32  RequestId,          //��ӦAuditRequest������Ϣ����ϢID      
//		/*in */ UInt32  CertType,          	
		/*in */ UInt8   ResponseStatus,     //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf,     //������װ�õ�AuditResponse�ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);               //��װ�õ�AuditResponse��Ϣ����

    /************************************************* 
    Function   �� FormatClearCertResponse()
    Description�� Parse 'ClearCertResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of ClearCertResponse
    	          ResponseLen    :length of ClearCertResponse 		
    Output     �� RequestId,     :Request Message id of SetCertChainRequest
                  CertType       :certificate type 
    	          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/  
	UInt32 ParseClearCertResponse(
		/*in */ UInt8  *ResponseBuf,        //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,        //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,          //��ӦAuditRequest������Ϣ����ϢID
//		/*out*/ UInt32 *CertType,
		/*out*/ UInt8  *ResponseStatus);    //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		
    /************************************************* 
    Function   �� SetCertType()
    Description�� transform certificate type to the message saved in memory 
    Input      �� CertType     :certificate type
    Output     �� CertTypeBuf  :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 		
    UInt32 SetCertType(
        /* in*/UInt32  CertType, 
        /*out*/UInt8  *CertTypeBuf);
        
    /************************************************* 
    Function   �� ParseCertType()
    Description�� transform the message saved in memory to certificate type
    Input      �� CertTypeBuf   :memory address of message	          	      
    Output     �� 
    Return     �� certificate type
    Others     :        
    *************************************************/         
    UInt32 ParseCertType(
    /*in*/ UInt8  *CertTypeBuf);

private:

	MessageLength    *MyMessageLength;      //��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;      //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;   //��ϢID��ָ��
};

#endif


