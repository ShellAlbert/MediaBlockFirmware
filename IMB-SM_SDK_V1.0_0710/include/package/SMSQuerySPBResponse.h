/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� SMSQuerySPBResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--SMSQuerySPBResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef SMSQUERYSPBRESPONSE_H
#define SMSQUERYSPBRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class SMSQuerySPBResponse
{

public:

	SMSQuerySPBResponse();
	~SMSQuerySPBResponse();
	
    /************************************************* 
    Function   �� FormatSMSQuerySPBResponse()
    Description�� format 'SMSQuerySPBResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of SMSQuerySPBRequest 
                  status          :status information of projector   
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of SMSQuerySPBResponse
		          len             :length of SMSQuerySPBResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSMSQuerySPBResponse(
		/* in*/ UInt32  RequestId,      //��Ӧ QuerySPBRequest ������Ϣ����ϢID
		/* in*/ UInt8   Protocol_ver,
		/* in*/ UInt8   status,         //��ӳ��״̬  
		/* in*/ UInt64	secureTime,
		/* in*/ Int32	time_adjust,
		/* in*/ UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		/*out*/ UInt8  *NewResponseBuf, //������װ�õ� QuerySPBResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);           //��װ�õ� QuerySPBResponse ��Ϣ����
		
    /************************************************* 
    Function   �� ParseSMSQuerySPBResponse()
    Description�� Parse 'SMSQuerySPBResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of SMSQuerySPBResponse
		          ResponseLen    :length of SMSQuerySPBResponse 		
    Output     �� RequestId,     :Request Message id of SMSQuerySPBRequest
                  status         :status information of projector  
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseSMSQuerySPBResponse(
		/* in*/ UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/ UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,      //��Ӧ QuerySPBRequest ������Ϣ����ϢID
		/*out*/ UInt8  *Protocol_ver,
		/*out*/ UInt8  *Status,         //��ӳ��״̬
		/*out*/ UInt64 *secureTime,
		/*out*/ Int32  *time_adjust,
		/*out*/ UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��		

};

#endif
