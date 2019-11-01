/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� ClearCertRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 11/08/06
Version    �� v1.0
Description�� Auditorium Security Message--ClearCertRequest
Others     :  
History    ��
      < Author >    			           < Date >         < Modification >
     zhangliang@dadimedia.com        10/10/9           Add comment 
********************************************/
#ifndef CLEARCERTREQUEST_H
#define CLEARCERTREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class ClearCertRequest 
{
public:
	ClearCertRequest();
	~ClearCertRequest();

	/************************************************* 
	Function   �� FormatClearCertRequest()
	Description�� format 'ClearCertRequest' Auditorium Security Message 
	Input      �� UserID        : Certificate's Thumb print
	              CertType      : Certificate's type
	Output     �� NewRequestBuf :memory address of LEKeyLoadRequest
	              len           :the length of LEKeyLoadRequest 
	Return     �� error code, refer to Const.h
	Others     :        
	*************************************************/
	UInt32 FormatClearCertRequest(
		/*in */ TEXT    *UserID,	// Certificate's Thumb print
//	/*in */ UInt32   CertType,	// Certificate's type
		/*out*/ UInt8   *NewRequestBuf,	// ������װ�õ� ClearCertRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32  *len);		//��װ�õ� ClearCertRequest ������Ϣ����

	/************************************************* 
	Function   �� ParseClearCertRequest()
	Description�� Parse 'ClearCertRequest'Auditorium Security Message 
	Input      �� RequestBuf   :memory address of LEKeyLoadRequest
	              RequestLen   :the length of LEKeyLoadRequest 		
	Output     �� RequestId    :Request Message id of LEKeyLoadRequest
	              UserID       :The Certificate's Thumb print
				        CertType     :The Certificate's type
	Return     �� error code, refer to Const.h
	Others     : 
	*************************************************/ 
	UInt32 ParseClearCertRequest(
		/*in */ UInt8   *RequestBuf,	//���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,	//���յ���������Ϣ����
		/*out*/ TEXT    *UserID,      // Received the Certificate's Thumb print
		/*out*/ UInt32  *RequestId);	//������Ϣ����ϢID		
//	/*out*/ UInt32  *CertType);		// Received the Certificate's type
		
private:
	//�������ã����������Ͱ�Big-Endian��д���������ĸ��ֽڿռ���
	UInt32 SetCertType(
		/*in */ UInt32  CertType,	//Ҫ��д����������
		/*out*/ UInt8  *CertBuf);	//Ŀ���ַ�ռ��ַ
	
	//�������ã���һ����Big-Endian������ĸ��ֽڿռ�����ת�����������ͷ���						
	UInt32 ParseCertType(
		/*in */ UInt8 *CertBuf);	//�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ
							
	MessageLength    *MyMessageLength;		//��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;		//��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;	//��ϢID��ָ��	
};

#endif


