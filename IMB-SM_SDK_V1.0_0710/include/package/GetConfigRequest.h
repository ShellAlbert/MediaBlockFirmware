/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetConfigRequest.h
Author     �� zhangliang@dadimedia.com
Date       �� 10/09/29
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--GetConfigRequest
Others     :  
History    �� 
      < Author >    		       < Date >          < Modification >
zhangliang@dadimedia.com       10/09/29            Add comment
huweihua@dadimedia.com         10/10/25            modify errors of compilation 
********************************************/
#ifndef GetConfigRequest_H
#define GetConfigRequest_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetConfigRequest
{
public:

	GetConfigRequest();
	~GetConfigRequest();

	/************************************************* 
    Function   �� FormatGetConfigRequest()
    Description�� format 'GetConfigRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	      
                  ConfigType    :Config Type, refer to code of each config
    Output     �� NewRequestBuf :memory address of GetConfigRequest
		          len           :the length of GetConfigRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetConfigRequest(
       /*in */ TEXT    *UserID,           //�����û����û�֤��ָ��
       /*in */ UInt32   ConfigType,       //�������ͣ���ϸ���鿴������������	
       /*out*/ UInt8   *NewRequestBuf,    //������װ�õ� GetConfigRequest ������Ϣ�Ļ�������ַ
       /*out*/ UInt32  *len);             //��װ�õ� GetConfigRequest ������Ϣ����
       
	/************************************************* 
    Function   �� ParseGetConfigRequest()
    Description�� Parse 'GetConfigRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of GetConfigRequest
		          RequestLen    :the length of GetConfigRequest 		
    Output     �� RequestId,    :Request Message id of GetConfigRequest
		          UserID        :Certificate Thumbprint of uesr
		          ConfigType    :Config Type, refer to code of each config
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetConfigRequest(
		/*in */ UInt8   *RequestBuf,  //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,  //���յ���������Ϣ����
		/*out*/ TEXT    *UserID,      //�����û����û�֤��ָ��
		/*out*/ UInt32  *RequestId,   //������Ϣ����ϢID
		/*out*/ UInt32  *ConfigType);  //�������ͣ���ϸ���鿴������������

private:	
    
    //�������ã����������Ͱ�Big-Endian��д���������ĸ��ֽڿռ���
	UInt32 SetConfigType(
        /* in*/UInt32  ConfigType,   //Ҫ��д����������
        /*out*/UInt8  *ConfigBuf);   //Ŀ���ַ�ռ��ַ

    //�������ã���һ����Big-Endian������ĸ��ֽڿռ�����ת�����������ͷ���
	UInt32 ParseConfigType(
	    /*in*/ UInt8  *ConfigBuf);   //�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ

	MessageULName    *MyMessageULName;       //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;       //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;    //��ϢID��ָ��	
};



#endif






