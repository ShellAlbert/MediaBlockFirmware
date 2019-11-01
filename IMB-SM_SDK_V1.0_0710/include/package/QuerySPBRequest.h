/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� QuerySPBRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROJ)--QuerySPBRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef QUERYSPBREQUEST_H
#define QUERYSPBREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class QuerySPBRequest
{
public:

	QuerySPBRequest();
	~QuerySPBRequest();
	
	/************************************************* 
    Function   �� FormatQuerySPBRequest()
    Description�� format 'QuerySPBRequest' Auditorium Security Message 
    Input      ��         
    Output     �� NewRequestBuf :memory address of QuerySPBRequest
		          len           :length of QuerySPBRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatQuerySPBRequest(
		/*out*/ UInt8  *NewRequestBuf, //������װ�õ� QuerySPBRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32 *len);          //��װ�õ� QuerySPBRequest ������Ϣ����

 	/************************************************* 
    Function   �� ParseQuerySPBRequest()
    Description�� Parse 'QuerySPBRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of QuerySPBRequest
		          RequestLen    :length of QuerySPBRequest 		
    Output     �� RequestId,    :Request Message id of QuerySPBRequest		         
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseQuerySPBRequest(
		/*in */ UInt8  *RequestBuf,    //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32  RequestLen,    //���յ���������Ϣ����
		/*out*/ UInt32 *RequestId);    //������Ϣ����ϢID

private:	
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��		
};
#endif


