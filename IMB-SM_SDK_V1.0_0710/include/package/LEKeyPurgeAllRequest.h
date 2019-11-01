/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyPurgeAllRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROJ)--LEKeyPurgeAllRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYPURGEALLREQUEST_H
#define LEKEYPURGEALLREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyPurgeAllRequest
{
public:

	LEKeyPurgeAllRequest();
	~LEKeyPurgeAllRequest();
    
   	/************************************************* 
    Function   �� FormatLEKeyPurgeALLRequest()
    Description�� format 'LEKeyPurgeAllRequest' Auditorium Security Message 
    Input      ��         
    Output     �� NewRequestBuf :memory address of LEKeyPurgeAllRequest
		          len           :the length of LEKeyPurgeAllRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEKeyPurgeALLRequest(
		/*out*/ UInt8 *NewRequestBuf,     //����ɹ��Ĳ�ѯ���
		/*out*/ UInt32  *len);            //��ѯ��䳤��

    /************************************************* 
    Function   �� ParseLEKeyPurgeAllRequest()
    Description�� Parse 'LEKeyPurgeAllRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of LEKeyPurgeAllRequest
		          RequestLen    :the length of LEKeyPurgeAllRequest 		
    Output     �� RequestId,    :Request Message id of LEKeyPurgeAllRequest		        
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyPurgeAllRequest(
		/*in */ UInt8 *RequestBuf,        //������Ϣ�洢������
		/*in */ UInt32  RequestLen,       //������Ϣ����   
		/*out*/	UInt32  *RequestId);      //������ϢID
 
private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	

};
#endif


