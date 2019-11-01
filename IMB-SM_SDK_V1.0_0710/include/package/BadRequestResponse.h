/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� BadRequestResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM  SM<-PROJ)--BadRequestResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef BADREQUESTRESPONSE_H
#define BADREQUESTRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class BadRequestResponse
{
public:
	BadRequestResponse();
	~BadRequestResponse();

	/************************************************* 
    Function   �� FormatBadRequestResponse()
    Description�� format 'BadRequestResponse' Auditorium Security Message 
    Input      �� BadRequest       :copy of Request 
                  BadRequestLength :the length of Bad Request
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of BadRequestResponse
		          len             :the length of BadRequestResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	int FormatBadRequestResponse(
			/*in */ UInt8   *BadRequest,       //�洢�����������Ϣ��������ַ
			/*in */ UInt32   BadRequestLength, //�����������Ϣ����
			/*in */ UInt8    ResponseStatus,   //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
			/*out*/ UInt8   *NewResponseBuf,   //������װ�õ� BadRequestResponse ������Ϣ�Ļ�������ַ
			/*out*/ UInt32  *len);             //��װ�õ� BadRequestResponse ������Ϣ����
			
	/************************************************* 
    Function   �� ParseBadRequestResponse()
    Description�� Parse 'BadRequestResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of BadRequestResponse
		          ResponseLen    :the length of BadRequestResponse 		
    Output     �� BadRequest,    :copy of Request 
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	int ParseBadRequestResponse(
			/*in */ UInt8   *ResponseBuf,      //���յ��Ļظ���Ϣ�Ĵ洢����ַ
			/*in */ UInt32   ResponseLen,      //���յ��Ļظ���Ϣ����
			/*out*/ UInt8   *BadRequest,       //���մ����������Ϣ��������ַ
			/*out*/ UInt32  *ResponseStatus);  //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��
};

#endif


