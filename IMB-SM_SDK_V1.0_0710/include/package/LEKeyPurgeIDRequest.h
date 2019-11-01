/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyPurgeIDRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROj)--LEKeyPurgeIDRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYPURGEIDREQUEST_H
#define LEKEYPURGEIDREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyPurgeIDRequest
{
public:
	LEKeyPurgeIDRequest();
	~LEKeyPurgeIDRequest();

    /************************************************* 
    Function   �� FormatLEKeyPurgeIDRequest()
    Description�� format 'LEKeyPurgeIDRequest' Auditorium Security Message 
    Input      �� LEKeyId       :unique key id         
    Output     �� NewRequestBuf :memory address of LEKeyPurgeIDRequest
		          len           :the length of LEKeyPurgeIDRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEKeyPurgeIDRequest (
		/* in*/UInt32  LEKeyId,         //��·������ԿID
		/*out*/UInt8  *NewRequestBuf,   //������װ�õ� LEKeyPurgeIDRequest ������Ϣ�Ļ�������ַ   
		/*out*/UInt32 *len);            //��װ�õ� LEKeyPurgeIDRequest ������Ϣ����
		
	/************************************************* 
    Function   �� ParseLEKeyPurgeIDRequest()
    Description�� Parse 'LEKeyPurgeIDRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of LEKeyPurgeIDRequest
		          RequestLen    :the length of LEKeyPurgeIDRequest 		
    Output     �� RequestId,    :Request Message id of LEKeyPurgeIDRequest
		          LEKeyId       :unique key id  
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyPurgeIDRequest (
		/* in*/UInt8  *RequestBuf,      //���յ���������Ϣ�Ĵ洢����ַ
		/* in*/UInt32  RequestLen,      //���յ���������Ϣ����
		/*out*/UInt32 *RequestId,       //������Ϣ����ϢID
		/*out*/UInt32 *LEKeyId);        //��·������ԿID
		
private:

    /************************************************* 
    Function   �� SetLEKeyId()
    Description�� transform LEKeyId to the LEKeyId message saved in memory 
    Input      �� LEKeyId       :LEKeyId want to transform	         	      
    Output     �� LEKeyBuf      :memory address of LEKeyId message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/   
	UInt32 SetLEKeyId(
        /* in*/UInt32  LEKeyId,    //Ҫ��д��LEKeyId
        /*out*/UInt8  *LEKeyBuf);  //Ŀ���ַ�ռ��ַ

    /************************************************* 
    Function   �� ParseLEKeyId()
    Description�� transform the LEKeyId message saved in memory to integer
    Input      �� LEKeyBuf       :memory address of LEKeyId message		               
    Output     ��
    Return     �� integer match along with LEKeyId message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyId(
		/*in*/ UInt8  *LEKeyBuf);  //�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��
};

#endif /* LEKEYPURGEIDREQUEST_H */



