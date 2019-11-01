/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetTimeResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROJ)--GetTimeResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETTIMERESPONSE_H
#define GETTIMERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"
//typedef unsigned long long uint64;
class GetTimeResponse
{

public:

	GetTimeResponse();
	~GetTimeResponse();

    /************************************************* 
    Function   �� FormatGetTimeResponse()
    Description�� format 'GetTimeResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of GetTimeRequest 
                  Time            :Responder's time
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of GetTimeResponse
		          len             :the length of GetTimeResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetTimeResponse(
		/*in */ UInt32  RequestId,      //��Ӧ GetTimeRequest ������Ϣ����ϢID
		/*in */ UInt64  Time,           //��ӳ����ʱ�����
		/*in */ UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		/*out*/ UInt8  *NewResponseBuf, //������װ�õ� GetTimeResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);           //��װ�õ� GetTimeResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseGetTimeResponse()
    Description�� Parse 'GetTimeResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of GetTimeResponse
		          ResponseLen    :the length of GetTimeResponse 		
    Output     �� RequestId      :Request Message id of GetTimeRequest
                  Time           :Responder's time
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetTimeResponse(
		/*in */ UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,      //��Ӧ GetTimeRequest ������Ϣ����ϢID
		/*out*/ UInt64 *Time,           //��ӳ����ʱ�����
		/*out*/ UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��

};


#endif
