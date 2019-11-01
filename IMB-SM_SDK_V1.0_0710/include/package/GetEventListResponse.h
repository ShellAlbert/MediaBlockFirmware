/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetEventListResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--GetEventListResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef GETEVENTLISTRESPONSE_H
#define GETEVENTLISTRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetEventListResponse
{

public:

	GetEventListResponse();
	~GetEventListResponse();

    /************************************************* 
    Function   �� FormatGetEventListResponse()
    Description�� format 'GetEventListResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of GetEventListRequest 
                  Delimiter       :Delimiter of event id list
                  EventIdBatch    :list of event id 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of GetEventListResponse
		          len             :the length of GetEventListResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetEventListResponse(
		/*in */ UInt32    RequestId,      //��Ӧ GetEventListRequest ������Ϣ����ϢID
		/*in */ UInt8     Delimiter,      //�ֶηָ��
		/*in */ UInt8    *EventIdBatch,   //��־ID����
		/*in */ UInt8     ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
		/*out*/ UInt8    *NewResponseBuf, //������װ�õ� GetEventListResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32   *len);           //��װ�õ� GetEventListResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseGetEventListResponse()
    Description�� Parse 'GetEventListResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of GetEventListResponse
		          ResponseLen    :the length of GetEventListResponse 			        
    Output     �� RequestId,     :Request Message id of GetEventListRequest
                  EventIdNum     :the number of event id 
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	 UInt32 ParseGetEventListResponse(
		/*in */ UInt8  *ResponseBuf,      //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32  ResponseLen,      //���յ��Ļظ���Ϣ����		  
		/*out*/ UInt32 *RequestId,        //��Ӧ GetEventListRequest ������Ϣ����ϢID
		/*out*/ UInt32 *EventIdNum,       //��־ID����
		/*out*/ UInt8  *ResponseStatus);  //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		
	/************************************************* 
    Function   �� GetEventId()
    Description�� get event id array 
    Input      �� EventIdNum        :the number of element in TempEventIdSet    
    Output     �� TempEventIdSet    :the array of Event Id           
    Return     �� error code, refer to Const.h
    Others     :  GetEventId  function will copy  the array of Event Id to 
                  memory of 'TempEventIdSet' point to
    *************************************************/ 	
   UInt32 GetEventId(
                /*out*/UInt32 *TempEventIdSet,
                /* in*/UInt32  EventIdNum);
    

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
		/*in */ UInt8 *Buf,       //�洢�ֽ���Ϣ�Ŀռ��ַ
		/*in */ UInt32 BufLEN);   //��Ϣ����

     /************************************************* 
    Function   �� ParseLenToBuf()
    Description�� transform integer to the message saved in memory 
    Input      �� IntNum       :integer want to transform	         	      
    Output     �� Buf          :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/     
	UInt32 ParseLenToBuf(
		/*in */  UInt32 IntNum,   //Ҫ��д������
		/*out */ UInt8 *Buf);     //Ŀ���ַ�ռ��ַ
    
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��
	UInt32           *m_EventIdSet;	         //the array of Event Id 
	UInt32            m_EventIdNum;          //tne number of Event Id

};


#endif
