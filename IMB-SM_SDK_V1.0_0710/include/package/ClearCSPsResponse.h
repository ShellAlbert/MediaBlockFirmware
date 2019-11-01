/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� ClearCSPsResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 11/08/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--ClearCSPsResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification > 
********************************************/
#ifndef CLEARCSPSRESPONSE_H
#define CLEARCSPSRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class ClearCSPsResponse
{
public:
	ClearCSPsResponse();
	~ClearCSPsResponse();
	
    /************************************************* 
    Function   �� FormatClearCSPsResponse()
    Description�� format 'ClearCSPsResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of StartSuiteRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of ClearCSPsResponse
		          len             :length of ClearCSPsResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatClearCSPsResponse(
		/* in*/ UInt32  RequestId,       //��Ӧ StartSuiteRequest ������Ϣ����ϢID
		/* in*/ UInt8   ResponseStatus,  //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf,  //������װ�õ� ClearCSPsResponse �ظ���Ϣ�Ļ�������ַ
        /*out*/ UInt32 *len);            //��װ�õ� ClearCSPsResponse ��Ϣ����
		
    /************************************************* 
    Function   �� ParseClearCSPsResponse()
    Description�� Parse 'ClearCSPsResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of ClearCSPsResponse
		          ResponseLen    :length of ClearCSPsResponse 		
    Output     �� RequestId,     :Request Message id of StartSuiteRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseClearCSPsResponse(
		/* in*/ UInt8   *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/ UInt32   ResponseLen,	 //���յ��Ļظ���Ϣ����	
		/*out*/ UInt32  *RequestId,      //��Ӧ StartSuiteRequest ������Ϣ����ϢID
		/*out*/ UInt8   *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* STARTSUITERESPONSE_H */


