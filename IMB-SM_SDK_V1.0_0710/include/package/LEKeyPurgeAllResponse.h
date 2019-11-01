/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyPurgeAllResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROJ)--LEKeyPurgeAllResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYPURGEALLRESPONSE_H
#define LEKEYPURGEALLRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyPurgeAllResponse
{

public:

	LEKeyPurgeAllResponse();
	~LEKeyPurgeAllResponse();


    /************************************************* 
    Function   �� FormatLEKeyPurgeALLResponse()
    Description�� format 'LEKeyPurgeAllResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of LEKeyPurgeAllRequest 
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of LEKeyPurgeAllResponse
		          len             :the length of LEKeyPurgeAllResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatLEKeyPurgeALLResponse(
		/*in */ UInt32   RequestId,      //��ϢID
		/*in */ UInt8    ResponseStatus, //�ظ���Ϣ״̬
		/*out*/ UInt8   *NewResponseBuf, //�ظ���Ϣ�洢������
		/*out*/ UInt32  *len);           //�ظ���Ϣ����

    /************************************************* 
    Function   �� ParseLEKeyPurgeAllResponse()
    Description�� Parse 'LEKeyPurgeAllResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of LEKeyPurgeAllResponse
		          ResponseLen    :the length of LEKeyPurgeAllResponse 		
    Output     �� RequestId,     :Request Message id of LEKeyPurgeAllRequest
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseLEKeyPurgeAllResponse(
		/*in */	UInt8  *ResponseBuf,     //�ظ���Ϣ�洢������
     	/*in */ UInt32  ResponseLen,     //�ظ���Ϣ�洢����������
		/*out*/	UInt32 *RequestId,       //��ϢID
		/*out*/	UInt8  *ResponseStatus); //�ظ���Ϣ״̬

private:	
	MessageLength    *MyMessageLength;        //��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;        //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;     //��ϢID��ָ��

};


#endif
