/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetEventIDResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROJ)--GetEventIDResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETEVENTIDRESPONSE_H
#define GETEVENTIDRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventIDResponse
{
public:

	GetEventIDResponse();
	~GetEventIDResponse();

    /************************************************* 
    Function   �� FormatGetEventIDResponse()
    Description�� format 'GetEventIDResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of GetEventIDRequest 
                  LogRecord       :Record being delivered
                  LogRecordLen    :the length of Record 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of GetEventIDResponse
		          len             :the length of GetEventIDResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventIDResponse(
		/*in */ UInt32   RequestId,      //��Ӧ GetEventIDRequest ������Ϣ����ϢID
		/*in */ TEXT    *LogRecord,      //��־��Ϣ
		/*in */ UInt32   LogRecordLen,   //��־��Ϣ����
		/*in */ UInt8    ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		/*out*/ UInt8   *NewResponseBuf, //������װ�õ� GetEventIDResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32  *len);           //��װ�õ� GetEventIDResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseGetEventIDResponse()
    Description�� Parse 'GetEventIDResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of GetEventIDResponse
		          ResponseLen    :the length of GetEventIDResponse 		
    Output     �� RequestId,     :Request Message id of GetEventIDRequest
                  LogRecord      :Record being delivered
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetEventIDResponse(
		/*in */ UInt8  *ResponseBuf,     //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,     //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,       //��Ӧ GetEventIDRequest ������Ϣ����ϢID
		/*out*/ TEXT   *LogRecord,       //��־��Ϣ
		/*out*/ UInt8  *ResponseStatus); //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	

};


#endif
