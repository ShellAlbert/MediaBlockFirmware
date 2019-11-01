/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyQueryIDResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROj)--LEKeyQueryIDResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYIDRESPONSE_H
#define LEKEYQUERYIDRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryIDResponse
{
public:
	LEKeyQueryIDResponse();
	~LEKeyQueryIDResponse();

    /************************************************* 
    Function   �� FormatLEKeyQueryIDResponse()
    Description�� format 'LEKeyQueryIDResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of LEKeyQueryIDRequest 
                  KeyStatus       :'1' if the key is present,'0' otherwise
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of LEKeyQueryIDResponse
		          len             :the length of LEKeyQueryIDResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEKeyQueryIDResponse(
		/* in*/UInt32  RequestId,      //��Ӧ LEKeyQueryIDRequest ������Ϣ����ϢID
		/* in*/UInt8   KeyStatus,      //��·������Կ״̬
		/* in*/UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/UInt8  *NewResponseBuf, //������װ�õ� LEKeyQueryIDResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/UInt32 *len);           //��װ�õ� LEKeyQueryIDResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseLEKeyQueryIDResponse()
    Description�� Parse 'LEKeyQueryIDResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of LEKeyQueryIDResponse
		          ResponseLen    :the length of LEKeyQueryIDResponse 		
    Output     �� RequestId,     :Request Message id of LEKeyQueryIDRequest
                  KeyStatus      :'1' if the key is present,'0' otherwise
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyQueryIDResponse(
		/* in*/UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/UInt32 *RequestId,      //��Ӧ IDAuthenticationRequest ������Ϣ����ϢID
		/*out*/UInt8  *KeyStatus,      //��·������Կ״̬
		/*out*/UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* LEKEYQUERYIDRESPONSE_H */



