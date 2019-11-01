/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� StopPlayRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message (SMS->SM)--StopPlayRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com  10/05/17            Add comment
   huweihua@dadimedia.com  11/06/24            implement request according to new message struct
********************************************/
#ifndef STOPPLAYREQUEST_H
#define STOPPLAYREQUEST_H

#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/MessageULName.h"
#include "package/Const.h"


//stopplay for single CPL and KDM 
#if 0 //add by huweihua 11/06/24 
class StopPlayRequest
{
public:

	StopPlayRequest();
	~StopPlayRequest();

	/************************************************* 
    Function   �� FormatStopPlayRequest()
    Description�� format 'StopPlayRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	         
    Output     �� NewRequestBuf :memory address of StopPlayRequest
		          len           :length of StopPlayRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStopPlayRequest(
		/* in */ TEXT   *UserID,       //�����û����û�֤��ָ��
		/* out*/ UInt8  *NewRequestBuf,//������װ�õ� StopPlayRequest ������Ϣ�Ļ�������ַ
		/* out*/ UInt32 *len);         //��װ�õ� StopPlayRequest ������Ϣ����


	/************************************************* 
    Function   �� ParseStopPlayRequest()
    Description�� Parse 'StopPlayRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of StopPlayRequest
		          RequestLen    :length of StopPlayRequest 		
    Output     �� RequestId,    :Request Message id of StopPlayRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseStopPlayRequest(
		/* in */ UInt8  *RequestBuf,  //���յ���������Ϣ�Ĵ洢����ַ
		/* in */ UInt32  RequestLen,  //���յ���������Ϣ����
		/* out*/ UInt32 *RequestId,   //������Ϣ����ϢID
		/* out*/ TEXT   *UserID);     //�����û����û�֤��ָ��

private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};
#endif

//-----------------------------------------------------------------------------------------
//stopplay for multi CPLs and KDMs
//add by huweihua 11/06/24
#if 1
class StopPlayRequest
{
public:
	
	enum STOP_TYPE
	{
		COMPLETE_STOP = 0,
		MANUAL_STOP = 1,
		SINGLE_CPL_STOP = 2,
		INNTERUPT_STOP = 3
	};

	StopPlayRequest();
	~StopPlayRequest();

	/************************************************* 
    Function   �� FormatStopPlayRequest()
    Description�� format 'StopPlayRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	   
    						  StopType      ��Stop Type 
    Output     �� NewRequestBuf :memory address of StopPlayRequest
		          len           :length of StopPlayRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatStopPlayRequest(
		/* in */ TEXT       *UserID,        //�����û����û�֤��ָ��
		/* in*/  STOP_TYPE   StopType,      //ֹͣ����
		/* out*/ UInt8      *NewRequestBuf, //������װ�õ� StopPlayRequest ������Ϣ�Ļ�������ַ
		/* out*/ UInt32     *len);          //��װ�õ� StopPlayRequest ������Ϣ����


	/************************************************* 
    Function   �� ParseStopPlayRequest()
    Description�� Parse 'StopPlayRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of StopPlayRequest
		          RequestLen    :length of StopPlayRequest 		
    Output     �� RequestId,    :Request Message id of StopPlayRequest
		          UserID        :Certificate Thumbprint of uesr
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseStopPlayRequest(
		/* in*/ UInt8     *RequestBuf,  //���յ���������Ϣ�Ĵ洢����ַ
		/* in*/ UInt32     RequestLen,  //���յ���������Ϣ����
		/*out*/ UInt32    *RequestId,   //������Ϣ����ϢID
		/*out*/ TEXT      *UserID,
		/*out*/ STOP_TYPE *StopType);   //�����û����û�֤��ָ��


  /************************************************* 
    Function   �� ParseBufToLen()
    Description�� transform the message saved in memory to integer
    Input      �� Buf       :memory address of message
    	          BufLen    :the length of message 	memory		      
    Output     ��
    Return     �� integer match along with message saved in memory
    Others     :        
    *************************************************/ 			
    UInt32 ParseBufToLen(
            /*in*/UInt8 *Buf, 
            /*in*/UInt32 BufLen);

    /************************************************* 
    Function   �� ParseLenToBuf()
    Description�� transform integer to the message saved in memory 
    Input      �� IntNum       :integer want to transform	
             	  BufLen       :the length of message 	memory
    Output     �� Buf          :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/            
    UInt32 ParseLenToBuf(
            /* in*/UInt32  IntNum,
            /* in*/UInt32  BufLen,
            /*out*/UInt8  *Buf);		
private:
	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};
#endif


#endif


