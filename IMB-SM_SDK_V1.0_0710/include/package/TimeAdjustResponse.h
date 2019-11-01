/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� TimeAdjustResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message (SMS<-SM)--TimeAdjustResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef TIMEADJUSTRESPONSE_H
#define TIMEADJUSTRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class TimeAdjustResponse
{
public:

	TimeAdjustResponse();
	~TimeAdjustResponse();

    /************************************************* 
    Function   �� FormatTimeAdjustResponse()
    Description�� format 'TimeAdjustResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of TimeAdjustRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of TimeAdjustResponse
		          len             :length of TimeAdjustResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatTimeAdjustResponse(
		/* in*/ UInt32  RequestId,      //��Ӧ TimeAdjustRequest ������Ϣ����ϢID
		/* in*/ UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf, //������װ�õ� TimeAdjustResponse �ظ���Ϣ�Ļ�������ַ
    	/*out*/ UInt32 *len);           //��װ�õ� TimeAdjustResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseTimeAdjustResponse()
    Description�� Parse 'TimeAdjustResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of TimeAdjustResponse
		          ResponseLen    :length of TimeAdjustResponse 		
    Output     �� RequestId,     :Request Message id of TimeAdjustRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseTimeAdjustResponse(     
		/* in*/ UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/ UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,      //��Ӧ TimeAdjustRequest ������Ϣ����ϢID
		/*out*/ UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:	

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��

};

#endif
