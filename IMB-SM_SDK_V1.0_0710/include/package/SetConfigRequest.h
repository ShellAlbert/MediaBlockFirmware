/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� SetConfigRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--SetConfigRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef SETCONFIGREQUEST_H
#define SETCONFIGREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"


class SetConfigRequest
{
public:

	SetConfigRequest();
	~SetConfigRequest();

	/************************************************* 
    Function   �� FormatSetConfigRequest()
    Description�� format 'SetConfigRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	      
                  ConfigType    :Config Type, refer to code of each config
                  ConfigValueLen:the length of Config Value
                  ConfigValue   :Config Value
    Output     �� NewRequestBuf :memory address of SetConfigRequest
		          len           :the length of SetConfigRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatSetConfigRequest(
       /*in */ TEXT    *UserID,           //�����û����û�֤��ָ��
       /*in */ UInt32   ConfigType,       //�������ͣ���ϸ���鿴������������
       /*in */ UInt32   ConfigValueLen,   //����ֵ����
       /*in */ TEXT    *ConfigValue,      //����ֵ			
       /*out*/ UInt8   *NewRequestBuf,    //������װ�õ� SetConfigRequest ������Ϣ�Ļ�������ַ
       /*out*/ UInt32  *len);             //��װ�õ� SetConfigRequest ������Ϣ����
       
	/************************************************* 
    Function   �� ParseSetConfigRequest()
    Description�� Parse 'SetConfigRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of SetConfigRequest
		          RequestLen    :the length of SetConfigRequest 		
    Output     �� RequestId,    :Request Message id of SetConfigRequest
		          UserID        :Certificate Thumbprint of uesr
		          ConfigType    :Config Type, refer to code of each config
                  ConfigValue   :Config Value
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseSetConfigRequest(
		/*in */ UInt8   *RequestBuf,  //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   RequestLen,  //���յ���������Ϣ����
		/*out*/ UInt32  *RequestId,   //������Ϣ����ϢID
		/*out*/ TEXT    *UserID,      //�����û����û�֤��ָ��
		/*out*/ UInt32  *ConfigType,  //�������ͣ���ϸ���鿴������������
		/*out*/ TEXT    *ConfigValue);//����ֵ


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






