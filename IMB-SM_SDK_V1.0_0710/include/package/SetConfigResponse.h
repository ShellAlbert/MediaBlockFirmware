/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� SetConfigResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--SetConfigResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef SETCONFIGRESPONSE_H
#define SETCONFIGRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class SetConfigResponse
{
public:

	SetConfigResponse();
	~SetConfigResponse();
	
    /************************************************* 
    Function   �� FormatSetConfigResponse()
    Description�� format 'SetConfigResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of SetConfigRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of SetConfigResponse
		          len             :the length of SetConfigResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSetConfigResponse(
		/* in*/ UInt32    RequestId,      //��Ӧ SetConfigRequest ������Ϣ����ϢID
		/* in*/ UInt8     ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8    *NewResponseBuf, //������װ�õ� SetConfigResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32   *len);           //��װ�õ� SetConfigResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseSetConfigResponse()
    Description�� Parse 'AuditResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of SetConfigResponse
		          ResponseLen    :the length of SetConfigResponse 		
    Output     �� RequestId,     :Request Message id of SetConfigRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseSetConfigResponse(
		/*in */ UInt8    *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32    ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32   *RequestId,      //��Ӧ SetConfigRequest ������Ϣ����ϢID
		/*out*/ UInt8    *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��		
};



#endif



