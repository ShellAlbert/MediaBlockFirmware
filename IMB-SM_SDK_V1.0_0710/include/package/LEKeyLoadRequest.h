/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� LEKeyLoadRequest.h
Author     �� cuijixin@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message(SM->PROJ)--LEKeyLoadRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
   huweihua@dadimedia.com        10/05/17            Add KE_KEY_LEN
********************************************/
#ifndef LEKEYLOADREQUEST_H
#define LEKEYLOADREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

#define KE_KEY_LEN  16     //the length of LE KEY

//��·������Կ�ṹ��
struct LEKeyInfo
{
	UInt32  m_LEKeyID;           //unique key identifier
	UInt8   m_Key[KE_KEY_LEN];   //decryption key
	UInt32  m_ExpireTime;        //calidity period of key in seconds
	UInt64  m_AttributeData;     //data used as input to counter mode cipher
	struct LEKeyInfo* m_pNext;   //next node 
};

class LEKeyLoadRequest
{
public:
	LEKeyLoadRequest();
	~LEKeyLoadRequest();


	/************************************************* 
    Function   �� SetList()
    Description�� push each LE key message into list 
    Input      �� KeyID    :unique key identifier        
                  Key      :unique key identifier
                  ExTime   :calidity period of key in seconds
                  AttrData :data used as input to counter mode cipher
    Output     �� head     :the head of list	         
    Return     �� error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.     
    *************************************************/
    // ����װLEKeyLoadRequestǰ���øú���������Ҫ�������Կ���һ������
    // �ڴ�����ɺ����ڲ���ɣ��ڵ���FormatLEKeyLoadRequest����ǰ��ɵ������Զ����١�
	UInt32 SetList(
		/*in */ const  UInt32      &KeyID,    //��·������ԿID
		/*in */ const  UInt8       *Key,      //��·������Կ
		/*in */ const  UInt32      &ExTime,   //��Կ��Ч��ʱ�䳤��
		/*in */ const  UInt64      &AttrData, //��ʼ��AES�е�����
		/*out*/ struct LEKeyInfo  **head);    //��·������Կ����ͷָ��

	/************************************************* 
    Function   �� FormatLEKeyLoadRequest()
    Description�� format 'LEKeyLoadRequest' Auditorium Security Message 
    Input      �� LEKeyBatch    :a list of LE Key ID to Key, Expire Time and Attribute Data mappings	         
    Output     �� NewRequestBuf :memory address of LEKeyLoadRequest
		          len           :the length of LEKeyLoadRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 FormatLEKeyLoadRequest(
		/*in */ struct LEKeyInfo *LEKeyBatch,   //Ҫ�������Կ����ͷָ��
		/*out*/ UInt8            *NewRequestBuf,//������װ�õ� LEKeyLoadRequest ������Ϣ�Ļ�������ַ
		/*out*/ UInt32           *len);         //��װ�õ� LEKeyLoadRequest ������Ϣ����
 
 
    /************************************************* 
    Function   �� ParseLEKeyLoadRequest()
    Description�� Parse 'LEKeyLoadRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of LEKeyLoadRequest
		          RequestLen    :the length of LEKeyLoadRequest 		
    Output     �� RequestId,    :Request Message id of LEKeyLoadRequest
		          head          :the head of the list of LE Key ID 
    Return     �� error code, refer to Const.h
    Others     :  Function will return a list of  LE Key messages, application call 
                  GetListMember() gets each  LE Key messages. the memory been used by list 
                  was malloc and delete inside Function.
    *************************************************/ 
    // �ú����Ὣ��Ϣ�е���·������Կ���һ��������
    // Ӧ�ò��ٵ���GetListMember��ȡ������Կ�飬ÿ����һ�λ�ȡһ����Կ��
    // ������ڴ�����ɺ����ڲ����
	UInt32 ParseLEKeyLoadRequest(
		/*in */ UInt8             *RequestBuf,  //���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32             RquestLen,   //���յ���������Ϣ����
		/*out*/ UInt32            *RequestId,   //������Ϣ����ϢID
		/*out*/ struct LEKeyInfo **head);       //�洢��·������Կ�������ͷָ��


	/************************************************* 
    Function   �� GetListMember()
    Description�� get LE key message from list 
    Input      �� head     :the head of list    
    Output     �� KeyID    :unique key identifier        
                  Key      :unique key identifier
                  ExTime   :calidity period of key in seconds
                  AttrData :data used as input to counter mode cipher	         
    Return     �� error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.
                  application  call GetListMember() once gets one LE key's message, untill 
                  list is blank(i.e. head = NULL)
    *************************************************/
    // �������ã���ȡ�������·������Կ��ÿ����һ�η���һ����Կ��
    //��������PARAMETER_ERROR����ʾ���������
	UInt32 GetListMember(
		/*in */ struct LEKeyInfo **head,        //�洢��·������Կ�������ͷָ��
		/*out*/ UInt32            *KeyID,       //��·������ԿID
		/*out*/ UInt8             *Key,         //��·������Կ
		/*out*/ UInt32            *ExTime,      //��Կ��Ч��ʱ�䳤��
		/*out*/ UInt64            *AttrData);   //��ʼ��AES�е�����

    /************************************************* 
    Function   �� ParseBufToLen()
    Description�� transform the message saved in memory to integer
    Input      �� Buf       :memory address of message
		          BufLEN    :the length of message 	memory		      
    Output     ��
    Return     �� integer match along with message saved in memory
    Others     :        
    *************************************************/ 
	UInt64 ParseBufToLen(
    	/*in */UInt8 *Buf,       //�洢�ĸ��ֽ���Ϣ�Ŀռ��ַ
    	/*in */UInt32 BufLEN);   //��Ϣ�ռ䳤��
    	
    /************************************************* 
    Function   �� ParseLenToBuf()
    Description�� transform integer to the message saved in memory 
    Input      �� IntNum       :integer want to transform	         	      
    Output     �� Buf          :memory address of message
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 ParseLenToBuf(
    	/*in */UInt32 IntNum,    //Ҫ��д��32λ����
    	/*out*/UInt8 *Buf);      //Ŀ���ַ�ռ��ַ

private:
	MessageLength    *MyMessageLength;        //��Ϣͷ��KEY in KLV struct����ָ��
	MessageULName    *MyMessageULName;        //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;     //��ϢID��ָ��
};

#endif /*LEKEYLOADREQUEST_H*/


