/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyQueryAllResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROj)--LEKeyQueryAllResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYQUERYALLRESPONSE_H
#define LEKEYQUERYALLRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyQueryAllResponse
{
public:
	LEKeyQueryAllResponse();
	~LEKeyQueryAllResponse();
	
   /************************************************* 
    Function   �� FormatLEQueryAllResponse()
    Description�� format 'LEKeyQueryAllResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of LEKeyQueryAllRequest 
                  Delimiter       :Delimiter of the list 
                  LEKeyIDBatch    :a list of LE Key ID values
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of LEKeyQueryAllResponse
		          len             :the length of LEKeyQueryAllResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEQueryAllResponse (
		/*in */ UInt32  RequestId,      //��Ӧ LEKeyQueryAllRequest ������Ϣ����ϢID
		/*in */ UInt8   Delimiter,      //ָ��LEKeyID���ַ����ָ��
		/*in */ UInt8  *LEKeyIDBatch,   //LEKeyID�����ַ�����ʽΪ��ID1�ָ��ID2�ָ��ID3.....��
		/*in */ UInt8   ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		/*out*/ UInt8  *NewResponseBuf, //������װ�õ� LEKeyQueryAllResponse �ظ���Ϣ�Ļ�������ַ
    	/*out*/ UInt32 *len);           //��װ�õ� LEKeyQueryAllResponse ��Ϣ����
		
    /************************************************* 
    Function   �� ParseLEKeyQueryAllResponse()
    Description�� Parse 'LEKeyQueryAllResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of LEKeyQueryAllResponse
		          ResponseLen    :the length of LEKeyQueryAllResponse 	
		          Delimiter      :Delimiter of event id list	
    Output     �� RequestId,     :Request Message id of AuditRequest
                  LEKeyIDBatch   :a list of LE Key ID values
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyQueryAllResponse(
		/*in */ UInt8  *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,    //���յ��Ļظ���Ϣ����
		/*in */ UInt8   Delimiter,      //ָ��LEKeyID���ַ����ָ��
		/*out*/ UInt32 *RequestId,      //��Ӧ LEKeyQueryAllRequest ������Ϣ����ϢID
		/*out*/ UInt8  *LEKeyIDBatch,   //LEKeyID�����ַ�����ʽΪ��ID1�ָ��ID2�ָ��ID3.....��
		/*out*/ UInt8  *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		
private:
    
    /************************************************* 
    Function   �� ParseBufToLen()
    Description�� transform the message saved in memory to integer
    Input      �� Buf       :memory address of message
		          BufLEN    :the length of message 	memory		      
    Output     ��
    Return     �� integer match along with message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseBufToLen(
		/*in */ UInt8  *Buf,      //�洢�ֽ���Ϣ�Ŀռ��ַ
		/*in */ UInt32  BufLEN);  //��Ϣ�ռ�ĳ���

    /************************************************* 
    Function   �� ParseLenToBuf()
    Description�� transform integer to the message saved in memory 
    Input      �� IntNum       :integer want to transform	         	      
    Output     �� Buf          :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/  
	UInt32 ParseLenToBuf(
		/*in */ UInt32 IntNum,    //Ҫ��д������
		/*out*/ UInt8 *Buf);      //Ŀ���ַ�ռ��ַ
		
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};

#endif	/* LEKEYQUERYALLRESPONSE_H */



