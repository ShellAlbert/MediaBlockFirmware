/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StopPlayResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message (SMS<-SM)--StopPlayResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STOPPLAYRESPONSE_H
#define STOPPLAYRESPONSE_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"

class StopPlayResponse
{
public:

	StopPlayResponse();
	~StopPlayResponse();

    /************************************************* 
    Function   �� FormatStopPlayResponse()
    Description�� format 'StopPlayResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of StopPlayRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of StopPlayResponse
		          len             :length of StopPlayResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStopPlayResponse(
		/* in*/ UInt32   RequestId,      //��Ӧ StopPlayRequest ������Ϣ����ϢID
		/* in*/ UInt8    ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8   *NewResponseBuf, //������װ�õ� StopPlayResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32  *len);           //��װ�õ� StopPlayResponse ��Ϣ����

     /************************************************* 
    Function   �� ParseStopPlayResponse()
    Description�� Parse 'StopPlayResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of StopPlayResponse
		          ResponseLen    :length of StopPlayResponse 		
    Output     �� RequestId,     :Request Message id of StopPlayRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseStopPlayResponse(
		/*in */ UInt8    *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32    ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32   *RequestId,      //��Ӧ StopPlayRequest ������Ϣ����ϢID
		/*out*/ UInt8    *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif


