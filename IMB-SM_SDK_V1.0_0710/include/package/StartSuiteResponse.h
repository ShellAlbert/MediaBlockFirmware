/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StartSuiteResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--StartSuiteResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef STARTSUITERESPONSE_H
#define STARTSUITERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class StartSuiteResponse
{
public:
	StartSuiteResponse();
	~StartSuiteResponse();
	
    /************************************************* 
    Function   �� FormatStartSuiteResponse()
    Description�� format 'StartSuiteResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of StartSuiteRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of StartSuiteResponse
		          len             :length of StartSuiteResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStartSuiteResponse(
		/* in*/ UInt32  RequestId,       //��Ӧ StartSuiteRequest ������Ϣ����ϢID
		/* in*/ UInt8   ResponseStatus,  //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf,  //������װ�õ� StartSuiteResponse �ظ���Ϣ�Ļ�������ַ
        /*out*/ UInt32 *len);            //��װ�õ� StartSuiteResponse ��Ϣ����
		
    /************************************************* 
    Function   �� ParseStartSuiteResponse()
    Description�� Parse 'StartSuiteResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of StartSuiteResponse
		          ResponseLen    :length of StartSuiteResponse 		
    Output     �� RequestId,     :Request Message id of StartSuiteRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseStartSuiteResponse(
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


