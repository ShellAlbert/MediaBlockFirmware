/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� IDAuthenticationResponse.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--IDAuthenticationResponse
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef IDAUTHENTICATIONRESPONSE_H
#define IDAUTHENTICATIONRESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class IDAuthenticationResponse
{
public:

	IDAuthenticationResponse();
	~IDAuthenticationResponse();

    /************************************************* 
    Function   �� FormatIDAuthenticationResponse()
    Description�� format 'IDAuthenticationResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of IDAuthenticationRequest 
                  RightsList      :Rights list of user
		          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of IDAuthenticationResponse
		          len             :the length of IDAuthenticationResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatIDAuthenticationResponse(
    		/* in*/ UInt32     RequestId,      //��Ӧ IDAuthenticationRequest ������Ϣ����ϢID
			/* in*/ UInt32     RightsList,     //Ȩ���б�
    		/* in*/ UInt8      ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h 
    		/*out*/ UInt8     *NewResponseBuf, //������װ�õ� IDAuthenticationResponse �ظ���Ϣ�Ļ�������ַ
    		/*out*/ UInt32    *len);           //��װ�õ� IDAuthenticationResponse ��Ϣ����
                        		
    /************************************************* 
    Function   �� ParseIDAuthenticationResponse()
    Description�� Parse 'IDAuthenticationResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of IDAuthenticationResponse
		          ResponseLen    :the length of IDAuthenticationResponse 		
    Output     �� RequestId,     :Request Message id of IDAuthenticationRequest
                  RightsList     :Rights list of user
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseIDAuthenticationResponse(
    		/*in */ UInt8    *ResponseBuf,     //���յ��Ļظ���Ϣ�Ĵ洢����ַ
    		/*in */ UInt32    ResponseLen,     //���յ��Ļظ���Ϣ����
    		/*out*/ UInt32   *RequestId,       //��Ӧ IDAuthenticationRequest ������Ϣ����ϢID
    		/*out*/ UInt32   *RightsList,      //Ȩ���б�
    		/*out*/ UInt8    *ResponseStatus); //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

private:
    
	/************************************************* 
    Function   �� SetRightsList()
    Description�� Rights List(integer) List to the message saved in memory 
    Input      �� RightsList   : Rights List want to transform	         	      
    Output     �� Buf          :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 SetRightsList(
        /* in*/UInt32  RightsList, //Ҫ��д��Ȩ���б�
        /*out*/UInt8  *Buf);       //Ŀ���ַ�ռ��ַ
        
     /************************************************* 
    Function   �� ParseRightsList()
    Description�� transform the Rights List message saved in memory to integer
    Input      �� Buf       :memory address of Rights List message		            
    Output     ��
    Return     �� Rights List(integer) match along with  Rights List message saved in memory
    Others     :        
    *************************************************/ 
	UInt32 ParseRightsList(
		/*in*/ UInt8  *Buf);       //�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ

	MessageLength    *MyMessageLength;        //��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;        //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;     //��ϢID��ָ��
};



#endif



