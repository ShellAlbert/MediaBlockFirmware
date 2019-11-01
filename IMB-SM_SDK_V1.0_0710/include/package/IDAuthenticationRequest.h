/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� IDAuthenticationRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--IDAuthenticationRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef IDAUTHENTICATIONREQUEST_H
#define IDAUTHENTICATIONREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class IDAuthenticationRequest
{
public:

	IDAuthenticationRequest();
	~IDAuthenticationRequest();
#if 0
    /************************************************* 
    Function   �� FormatIDAuthenticationRequest()
    Description�� format 'IDAuthenticationRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Output     �� NewRequestBuf :memory address of IDAuthenticationRequest
		          len           :the length of IDAuthenticationRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatIDAuthenticationRequest(
		/*in */ TEXT     *UserID,         //�����û����û�֤��ָ��
		/*in */ TEXT     *UserName,       //�����û����û���
		/*in */ TEXT     *Password,       //�����û��ĵ�¼����
		/*in */ UInt32    SingnedAglth,   //ǩ���㷨
		/*in */ TEXT     *SingnedValue,   //ǩ��ֵ
		/*in */ TEXT     *CertChain,      //֤����
		/*out*/ UInt8    *NewRequestBuf,  //������װ�õ� IDAuthenticationRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32   *len);           //��װ�õ� IDAuthenticationRequest ������Ϣ����

	/************************************************* 
    Function   �� ParseIDAuthenticationRequest()
    Description�� Parse 'IDAuthenticationRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of IDAuthenticationRequest
		          RequestLen    :the length of IDAuthenticationRequest 		
    Output     �� RequestId,    :Request Message id of IDAuthenticationRequest
		          UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
                  CertChain     :Certificate chain
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseIDAuthenticationRequest(
		/*in */ UInt8   *RequestBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,   //���յ���������Ϣ����
		/*out*/ UInt32  *RequestId,    //������Ϣ����ϢID
		/*out*/ TEXT    *UserID,       //����������Ϣ���û���֤��ָ��
		/*out*/ TEXT    *UserName,     //�����û����û���
		/*out*/ TEXT    *Password,     //�����û��ĵ�¼����
		/*out*/ UInt32  *SingnedAglth, //ǩ���㷨
		/*out*/ TEXT    *SingnedValue, //ǩ��ֵ
		/*out*/ TEXT    *CertChain);   //֤����
#endif 

#if 1
    /************************************************* 
    Function   �� FormatIDAuthenticationRequest()
    Description�� format 'IDAuthenticationRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
    Output     �� NewRequestBuf :memory address of IDAuthenticationRequest
		          len           :the length of IDAuthenticationRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
UInt32 FormatIDAuthenticationRequest(
		/*in */ TEXT     *UserID, 
		/*in */ TEXT     *UserName, 
		/*in */ TEXT     *Password, 
		/*in */ TEXT     *Role, 		 
		/*in */ UInt32    SingnedAglth,
		/*in */ TEXT     *SingnedValue,
		/*out*/ UInt8    *NewRequestBuf, 
		/*out*/ UInt32   *len);
		
	/************************************************* 
    Function   �� ParseIDAuthenticationRequest()
    Description�� Parse 'IDAuthenticationRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of IDAuthenticationRequest
		              RequestLen    :the length of IDAuthenticationRequest 		
    Output     �� RequestId,    :Request Message id of IDAuthenticationRequest
		              UserID        :Certificate Thumbprint of uesr	 
                  UserName      :User name of operator
                  Password      :Password of the user name
                  Role          :role of user
                  SingnedAglth  :Singed aglthmodth
                  SingnedValue  :Singed value
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseIDAuthenticationRequest(
		/*in */ UInt8   *RequestBuf,   //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,   //���յ���������Ϣ����
		/*out*/ UInt32  *RequestId,    //������Ϣ����ϢID
		/*out*/ TEXT    *UserID,       //����������Ϣ���û���֤��ָ��
		/*out*/ TEXT    *UserName,     //�����û����û���
		/*out*/ TEXT    *Password,     //�����û��ĵ�¼����
		/*out*/ TEXT    *Role,        //�����û��ĵ�¼����		
		/*out*/ UInt32  *SingnedAglth, //ǩ���㷨
		/*out*/ TEXT    *SingnedValue); //ǩ��ֵ
		

#endif
private:
	    /************************************************* 
        Function   �� SetLen()
        Description�� transform integer to the message saved in memory 
        Input      �� Len       :integer want to transform	         	      
        Output     �� Buf       :memory address of message
        Return     �� error code, refer to Const.h
        Others     :        
        *************************************************/ 	
		UInt32 SetLen(
        /* in*/UInt32  Len,     //Ҫ��д��32λ����
        /*out*/UInt8  *Buf);    //Ŀ���ַ�ռ��ַ
        
	    /************************************************* 
        Function   �� ParseLen()
        Description�� transform the message saved in memory to integer
        Input      �� Buf       :memory address of message    		          
        Output     ��
        Return     �� integer match along with message saved in memory
        Others     :        
        *************************************************/ 
		UInt32 ParseLen(
        /*in*/ UInt8  *Buf);    //�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};



#endif




