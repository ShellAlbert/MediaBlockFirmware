/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetCertChainRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/10/09
Version    �� v1.0
Description�� Auditorium Security Message(SM->SMS)--LEKeyLoadRequest
Others     :  
History    �� 
********************************************/
#ifndef GETCERTCHAINREQUEST_H
#define GETCERTCHAINREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetCertChainRequest 
{
public:
	GetCertChainRequest();
	~GetCertChainRequest();

	/************************************************* 
	Function   �� FormatGetCertChainRequest()
	Description�� format 'GetCertChainRequest' Auditorium Security Message 
	Input      �� UserID        : Certificate's Thumb print
	              CertType      : Certificate's type
	Output     �� NewRequestBuf :memory address of LEKeyLoadRequest
	              len           :the length of LEKeyLoadRequest 
	Return     �� error code, refer to Const.h
	Others     :        
	*************************************************/
	UInt32 FormatGetCertChainRequest(
		/*in */ TEXT    *UserID,	// Certificate's Thumb print
//		/*in */ UInt32   CertType,	// Certificate's type
		/*out*/ UInt8   *NewRequestBuf,	// ������װ�õ� GetCertChainRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32  *len);		//��װ�õ� GetCertChainRequest ������Ϣ����

	/************************************************* 
	Function   �� ParseGetCertChainRequest()
	Description�� Parse 'GetCertChainRequest'Auditorium Security Message 
	Input      �� RequestBuf   :memory address of LEKeyLoadRequest
	              RequestLen   :the length of LEKeyLoadRequest 		
	Output     �� RequestId    :Request Message id of LEKeyLoadRequest
	              UserID       :The Certificate's Thumb print
				        CertType     :The Certificate's type
	Return     �� error code, refer to Const.h
	Others     : 
	*************************************************/ 
	UInt32 ParseGetCertChainRequest(
		/*in */ UInt8   *RequestBuf,	//���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,	//���յ���������Ϣ����
		/*out*/ UInt32  *RequestId,		//������Ϣ����ϢID
		/*out*/ TEXT    *UserID		// Received the Certificate's Thumb print
//		/*out*/ UInt32  *CertType
		);		// Received the Certificate's type
		
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


