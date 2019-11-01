/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� SetCertChainResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 2011/8/15
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--SetCertChainResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
 
********************************************/
#ifndef SETCERTCHAINRESPONSE_H
#define SETCERTCHAINRESPONSE_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"

class SetCertChainResponse
{
public:

	SetCertChainResponse();
	~SetCertChainResponse();

    /************************************************* 
    Function   �� FormatSetCertChainResponse()
    Description�� format 'SetCertChainResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of SetCertChainRequest 
                  UserID          :user id
                  CertType        :certificate type  
    	          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of SetCertChainResponse
    	          len             :the length of SetCertChainResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSetCertChainResponse(
		/*in */ UInt32  RequestId,          //��ӦAuditRequest������Ϣ����ϢID
//	/*in */ TEXT   *UserID,        
//	/*in */ UInt32  CertType,          	
		/*in */ UInt8   ResponseStatus,     //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf,     //������װ�õ�AuditResponse�ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);               //��װ�õ�AuditResponse��Ϣ����

    /************************************************* 
    Function   �� ParseSetCertChainResponse()
    Description�� Parse 'SetCertChainResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of SetCertChainResponse
    	          ResponseLen    :length of SetCertChainResponse 		
    Output     �� RequestId,     :Request Message id of SetCertChainRequest
                  UserID         :user id
                  CertType       :certificate type 
    	          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/  
	UInt32 ParseSetCertChainResponse(
		/*in */ UInt8  *ResponseBuf,        //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,        //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,          //��ӦAuditRequest������Ϣ����ϢID
//	/*out*/ TEXT   *UserID,
//	/*out*/ UInt32 *CertType,
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


