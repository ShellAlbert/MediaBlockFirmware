/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� GetConfigResponse.h
Author     �� zhangliang@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SMS<-SM)--GetConfigResponse
Others     :  
History    �� 
      < Author >    			     < Date >           < Modification >
zhangliang@dadimedia.com       10/09/29            Add comment
huweihua@dadimedia.com         10/10/25            modify errors of compilation 
********************************************/
#ifndef GetConfigResponse_H
#define GetConfigResponse_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

class GetConfigResponse
{
public:

	GetConfigResponse();
	~GetConfigResponse();
	
    /************************************************* 
    Function   �� FormatGetConfigResponse()
    Description�� format 'GetConfigResponse' Auditorium Security Message 
    Input      �� RequestId       :Request Message id of SetConfigRequest 
                  ConfigType      :Config Type, refer to code of each config
                  ConfigValue     :Config Value 
                  ConfigValueLen  :length of config value      
    	          ResponseStatus  :General Response Elements
    Output     �� NewResponseBuf  :memory address of GetConfigResponse
    	          len             :the length of GetConfigResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatGetConfigResponse(
		/* in*/ UInt32    RequestId,      //��Ӧ SetConfigRequest ������Ϣ����ϢID
		/* in*/ UInt32    ConfigType,     //��������
    /* in*/ UInt32    ConfigValueLen, //�������ͳ���
    /* in*/ TEXT     *ConfigVaulue,   //��������ֵ
		/* in*/ UInt8     ResponseStatus, //ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8    *NewResponseBuf, //������װ�õ� GetConfigResponse �ظ���Ϣ�Ļ�������ַ
		/*out*/ UInt32   *len);           //��װ�õ� GetConfigResponse ��Ϣ����

    /************************************************* 
    Function   �� ParseGetConfigResponse()
    Description�� Parse 'GetConfigResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of GetConfigResponse
		          ResponseLen    :the length of GetConfigResponse 		
    Output     �� RequestId      :Request Message id of GetConfigRequest
                  ConfigType     :config type
                  ConfigTypeValue:the value of config type
		          ResponseStatus :General Response Elements
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseGetConfigResponse(
		/*in */ UInt8    *ResponseBuf,    //���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32    ResponseLen,    //���յ��Ļظ���Ϣ����
		/*out*/ UInt32   *RequestId,      //��Ӧ SetConfigRequest ������Ϣ����ϢID
		/*out*/ UInt32   *ConfigType,     //��������
        /*out*/ TEXT     *ConfigVaulue,   //��������ֵ
		/*out*/ UInt8    *ResponseStatus);//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

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



