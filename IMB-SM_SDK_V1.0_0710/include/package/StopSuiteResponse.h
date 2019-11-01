/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StopSuiteResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message (SMS<-SM)--StopSuiteResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STOPSUITERESPONSE_H
#define STOPSUITERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class StopSuiteResponse
{
public:
	StopSuiteResponse();
	~StopSuiteResponse();
	
        /************************************************* 
        Function   �� FormatStopSuiteResponse()
        Description�� format 'StopSuiteResponse' Auditorium Security Message 
        Input      �� RequestId       :Request Message id of StopSuiteRequest 
    		          ResponseStatus  :General Response Elements
        Output     �� NewResponseBuf  :memory address of StopSuiteResponse
    		          len             :length of StopSuiteResponse 
        Return     �� error code, refer to Const.h
        Others     :        
        *************************************************/ 
	    UInt32 FormatStopSuiteResponse(
		/* in*/ UInt32  RequestId,      //��Ӧ StopSuiteRequest ������Ϣ����ϢID
		/* in*/ UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf, //������װ�õ� StopSuiteResponse �ظ���Ϣ�Ļ�������ַ
    	/*out*/ UInt32 *len);           //��װ�õ� StopSuiteResponse ��Ϣ����

        /************************************************* 
        Function   �� ParseStopSuiteResponse()
        Description�� Parse 'StopSuiteResponse'Auditorium Security Message 
        Input      �� ResponseBuf    :memory address of StopSuiteResponse
    		          ResponseLen    :length of StopSuiteResponse 		
        Output     �� RequestId,     :Request Message id of StopSuiteRequest
    		          ResponseStatus :General Response Elements
        Return     �� error code, refer to Const.h
        Others     :        
        *************************************************/
		UInt32 ParseStopSuiteResponse(
		/* in*/ UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/ UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *Requestid,      //��Ӧ StopSuiteRequest ������Ϣ����ϢID
		/*out*/ UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		
private:

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��
};

#endif /* STOPSUITERESPONSE_H*/


