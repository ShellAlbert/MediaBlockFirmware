/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyPurgeIDResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROj)--LEKeyPurgeIDResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYPURGEIDRESPONSE_H
#define LEKEYPURGEIDRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyPurgeIDResponse
{
public:
	LEKeyPurgeIDResponse();
	~LEKeyPurgeIDResponse();
	
    /************************************************* 
    Function   �� FormatLEKeyPurgeIDResponse()
    Description�� format 'LEKeyPurgeIDResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of LEKeyPurgeIDRequest 
                  KeyIdStatus     :the status of key
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of LEKeyPurgeIDResponse
		          len             :the length of LEKeyPurgeIDResponse 
    Return     �� error code, refer to Const.h
    Others     :  A non-zero value for KeyIdStatus indicates that the indentified key 
                  to be purged was not present. the value of ResponseStatus for this
                  condition is 0.      
    *************************************************/ 
	UInt32 FormatLEKeyPurgeIDResponse(
		/* in */  UInt32  RequestId,      //��Ӧ LEKeyPurgeIDRequest ������Ϣ����ϢID
		/* in */  UInt8   KeyIdStatus,    //��·������Կ״̬ 
		/* in */  UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/* out*/  UInt8  *NewResponseBuf, //������װ�õ� LEKeyPurgeIDResponse �ظ���Ϣ�Ļ�������ַ
		/* out*/  UInt32 *len);           //��װ�õ� LEKeyPurgeIDResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseLEKeyPurgeIDResponse()
    Description�� Parse 'LEKeyPurgeIDResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of LEKeyPurgeIDResponse
		          ResponseLen    :the length of LEKeyPurgeIDResponse 		
    Output     �� RequestId,     :Request Message id of LEKeyPurgeIDRequest
                  KeyIdStatus    :the status of key
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyPurgeIDResponse(
		/* in*/  UInt8  *ResponseBuf,     //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/  UInt32  ResponseLen,     //���յ��Ļظ���Ϣ����
		/*out*/  UInt32 *RequestId,       //��Ӧ LEKeyPurgeIDRequest ������Ϣ����ϢID
		/*out*/  UInt8  *KeyStatus,       //��·������Կ״̬ 
		/*out*/  UInt8  *ResponseStatus); //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
	MessageULName    *MyMessageULName;    //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;    //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId; //��ϢID��ָ��
};

#endif /* LEKEYPURGEIDRESPONSE_H*/



