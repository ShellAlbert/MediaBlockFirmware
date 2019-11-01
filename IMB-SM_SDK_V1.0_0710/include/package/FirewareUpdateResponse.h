/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� FirewareUpdateResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 11/08/06
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--FirewareUpdateResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification > 
********************************************/
#ifndef FIREWAREUPDATERESPONSE_H
#define FIREWAREUPDATERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class FirewareUpdateResponse
{
public:
	FirewareUpdateResponse();
	~FirewareUpdateResponse();
	
    /************************************************* 
    Function   �� FormatFirewareUpdateResponse()
    Description�� format 'FirewareUpdateResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of StartSuiteRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of FirewareUpdateResponse
		          len             :length of FirewareUpdateResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatFirewareUpdateResponse(
		/* in*/ UInt32  RequestId,       //��Ӧ StartSuiteRequest ������Ϣ����ϢID
		/* in*/ UInt8   ResponseStatus,  //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8  *NewResponseBuf,  //������װ�õ� FirewareUpdateResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);            //��װ�õ� FirewareUpdateResponse ��Ϣ����
		
    /************************************************* 
    Function   �� ParseFirewareUpdateResponse()
    Description�� Parse 'FirewareUpdateResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of FirewareUpdateResponse
		          ResponseLen    :length of FirewareUpdateResponse 		
    Output     �� RequestId,     :Request Message id of StartSuiteRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseFirewareUpdateResponse(
		/* in*/ UInt8   *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/ UInt32   ResponseLen,	 //���յ��Ļظ���Ϣ����	
		/*out*/ UInt32  *RequestId,      //��Ӧ StartSuiteRequest ������Ϣ����ϢID
		/*out*/ UInt8   *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif /* FIREWAREUPDATERESPONSE_H */


