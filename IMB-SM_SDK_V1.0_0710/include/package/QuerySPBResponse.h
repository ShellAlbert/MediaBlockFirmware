/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� QuerySPBResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROJ)--QuerySPBResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef QUERYSPBRESPONSE_H
#define QUERYSPBRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class QuerySPBResponse
{

public:

	QuerySPBResponse();
	~QuerySPBResponse();
	
    /************************************************* 
    Function   �� FormatQuerySPBResponse()
    Description�� format 'QuerySPBResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of QuerySPBRequest 
                  status          :status information of projector
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of QuerySPBResponse
		          len             :length of QuerySPBResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatQuerySPBResponse(
		/* in*/ UInt32  RequestId,      //��Ӧ QuerySPBRequest ������Ϣ����ϢID
		/* in*/ UInt8   status,         //��ӳ��״̬
		/* in*/ UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		/*out*/ UInt8  *NewResponseBuf, //������װ�õ� QuerySPBResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);           //��װ�õ� QuerySPBResponse ��Ϣ����
		
    /************************************************* 
    Function   �� ParseQuerySPBResponse()
    Description�� Parse 'QuerySPBResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of QuerySPBResponse
		          ResponseLen    :length of QuerySPBResponse 		
    Output     �� RequestId,     :Request Message id of QuerySPBRequest
                  status         :status information of projector
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseQuerySPBResponse(
		/* in*/ UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/* in*/ UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32 *RequestId,      //��Ӧ QuerySPBRequest ������Ϣ����ϢID
		/*out*/ UInt8  *Status,         //��ӳ��״̬
		/*out*/ UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��		

};

#endif
