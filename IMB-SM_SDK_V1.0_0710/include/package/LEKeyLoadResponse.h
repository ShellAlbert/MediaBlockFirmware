/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyLoadResponse.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM<-PROJ)--LEKeyLoadResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef LEKEYLOADRESPONSE_H
#define LEKEYLOADRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class LEKeyLoadResponse
{
public:
	LEKeyLoadResponse();
	~LEKeyLoadResponse();
	
   /************************************************* 
    Function   �� FormatLEKeyLoadResponse()
    Description�� format 'LEKeyLoadResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of AuditRequest 
                  OverflowFlag    :key buffer full.
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of LEKeyLoadResponse
		          len             :the length of LEKeyLoadResponse 
    Return     �� error code, refer to Const.h
    Others     :  A non-zero OverflowFlag value indicates that the LEKeyLoad request has not
                  been successfully executed because the LDB key buffer would have overflowed.
                  A non-zero OverflowFlag value shall also cause the ResponseStatus equal 1
    *************************************************/
	UInt32 FormatLEKeyLoadResponse(
		/*in */	UInt32  RequestId,			// ID of this LEKeyLoadRequest
		/*in */ UInt8   OverflowFlag,		// Key buffer full		
		/*in */ UInt8   ResponseStatus,		// General Response info
		/*out*/ UInt8  *NewResponseBuf,     // �ظ���Ϣ�洢������
		/*out*/ UInt32 *len);				// �ظ���Ϣ����
		
    /************************************************* 
    Function   �� ParseLEKeyLoadResponse()
    Description�� Parse 'LEKeyLoadResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of LEKeyLoadResponse
		          ResponseLen    :the length of LEKeyLoadResponse 		
    Output     �� RequestId,     :Request Message id of LEKeyLoadRequest
                  OverflowFlag   :key buffer full
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLEKeyLoadResponse(
	    /*in */	UInt8  *ResponseBuf,		// �ظ���Ϣ�洢������
		/*in */ UInt32  ResponseLen,	    // �ظ���Ϣ�洢������
		/*out*/ UInt32 *RequestId,			// ��ϢID
		/*out*/ UInt8  *OverflowFlag,		// Key buffer full
		/*out*/ UInt8  *ResponseStatus);	// �ظ���Ϣ״̬

private:
	MessageLength    *MyMessageLength;        //��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;        //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;     //��ϢID��ָ��
};

#endif /* LEKEYLOADRESPONSE_H */



