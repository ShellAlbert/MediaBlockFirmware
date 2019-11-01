/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyQueryIDRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROj)--LEKeyQueryIDRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYIDREQUEST_H
#define LEKEYQUERYIDREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryIDRequest
{
public:
	LEKeyQueryIDRequest();
	~LEKeyQueryIDRequest();

    /************************************************* 
    Function   �� FormatLEKeyQueryIDRequest()
    Description�� format 'LEKeyQueryIDRequest' Auditorium Security Message 
    Input      �� LEKeyId       :unique LE Key id	         
    Output     �� NewRequestBuf :memory address of LEKeyQueryIDRequest
		          len           :the length of LEKeyQueryIDRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatLEKeyQueryIDRequest(
		/*in */UInt32  LEKeyId,       //��·������Կ
		/*out*/UInt8  *NewRequestBuf, //������װ�õ� LEKeyQueryIDRequest ������Ϣ�Ļ�������ַ
		/*out*/UInt32 *len);          //��װ�õ� LEKeyQueryIDRequest ������Ϣ����

	/************************************************* 
    Function   �� ParseLEKeyQueryIDRequest()
    Description�� Parse 'LEKeyQueryIDRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of LEKeyQueryIDRequest
		          RequestLen    :the length of LEKeyQueryIDRequest 		
    Output     �� RequestId,    :Request Message id of LEKeyQueryIDRequest
		          LEKeyId       :unique LE Key id	
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseLEKeyQueryIDRequest(
		/*in */UInt8  *ResponseBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */UInt32  ResponseLen,   //���յ���������Ϣ����
		/*out*/UInt32 *RequestId,     //������Ϣ����ϢID
		/*out*/UInt32 *LEKeyId);      //��·������Կ

private:
    
    /************************************************* 
    Function   �� SetLEKeyId()
    Description�� transform integer to the LEKeyId message saved in memory 
    Input      �� LEKeyId       :LEKeyId want to transform	         	      
    Output     �� LEKeyBuf      :memory address of  the LEKeyId message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 SetLEKeyId(
        /* in*/UInt32  LEKeyId,      //Ҫ��д��LEKeyId
        /*out*/UInt8  *LEKeyBuf);    //Ŀ���ַ�ռ��ַ

    /************************************************* 
    Function   �� ParseLEKeyId()
    Description�� transform the LEKeyId message saved in memory to integer
    Input      �� LEKeyBuf       :memory address of LEKeyId  message		           
    Output     ��
    Return     �� integer match along with LEKeyId message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyId(
		/*in*/ UInt8  *LEKeyBuf);    //�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* LEKEYQUERYIDREQUEST_H */



