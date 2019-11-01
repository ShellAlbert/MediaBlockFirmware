/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� TimeAdjustRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message (SMS->SM)--TimeAdjustRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef TIMEADJUSTREQUEST_H
#define TIMEADJUSTREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class TimeAdjustRequest
{
public:

	TimeAdjustRequest();
	~TimeAdjustRequest();
	
	/************************************************* 
    Function   �� FormatAuditRequest()
    Description�� format 'TimeAdjustRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	 
                  Time          :time want to adjust. time shall be a 64-bitintegerrepresenting 
                                 the number of seconds elapsed since January 1.1970 00:00:00UTC
    Output     �� NewRequestBuf :memory address of TimeAdjustRequest
		          len           :length of TimeAdjustRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatTimeAdjustRequest(
		/* in*/ TEXT     *UserID,        //�����û����û�֤��ָ��
		/* in*/ UInt64    Time,          //Ҫ������ʱ�䣬��ʾ��1970��1��1��0��0��0�뿪ʼ�����ھ���������
		/*out*/ UInt8    *NewRequestBuf, //������װ�õ� TimeAdjustRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32   *len);          //��װ�õ� TimeAdjustRequest ������Ϣ����

		
    /************************************************* 
    Function   �� ParseTimeAdjustRequest()
    Description�� Parse 'TimeAdjustRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of TimeAdjustRequest
		          RequestLen    :length of TimeAdjustRequest 		
    Output     �� RequestId,    :Request Message id of TimeAdjustRequest
		          UserID        :Certificate Thumbprint of uesr
		          Time          :time want to adjust. time shall be a 64-bitintegerrepresenting 
                                 the number of seconds elapsed since January 1.1970 00:00:00UTC
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseTimeAdjustRequest(
		/*in */ UInt8   *RequestBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,   //���յ���������Ϣ����
		/*out*/ UInt32  *RequestId,    //������Ϣ����ϢID
		/*out*/ TEXT    *UserID,       //�����û����û�֤��ָ��
		/*out*/ UInt64  *Time);        //Ҫ������ʱ�䣬��ʾ��1970��1��1��0��0��0�뿪ʼ�����ھ���������

private:	

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��
};
#endif


