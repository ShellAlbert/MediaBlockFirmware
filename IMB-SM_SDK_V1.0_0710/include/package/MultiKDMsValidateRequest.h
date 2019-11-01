/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MultiKDMsValidateRequest.h
Author     �� sunpeng@dadimedia.com
Date       �� 11/05/06
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--MultiKDMsValidateRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
huweihua@dadimedia.com   11/06/20           implement request according to new message struct
********************************************/
#ifndef MULTIKDMSVALIDATEREQUEST_H
#define MULTIKDMSVALIDATEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

typedef struct KDMInfo
{
	UInt8   KDMID[KDM_ID_MAX_LEN]; 	//KDMID
	UInt8   Index;                  //kdm index in list, add by huweihua 11/06/20	
	UInt32  KDMContentLen;        	//length of KDM Content
	TEXT  	*KDMContent;     		//pointer of KDM Content
	struct 	KDMInfo* pNext;  		//next node
}KDMINFO;

class MultiKDMsValidateRequest
{
public:

	MultiKDMsValidateRequest();
	~MultiKDMsValidateRequest();
	
	/************************************************* 
    Function   �� FormatMultiKDMsValidateRequest()
    Description�� format 'MultiKDMsValidateRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	
    Output     �� NewRequestBuf :memory address of MultiKDMsValidateRequest
		          		len           :length of MultiKDMsValidateRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatMultiKDMsValidateRequest(
		/*in */ TEXT     				*UserID,        				//�����û����û�֤��ָ��
		/*out*/ UInt8    				*NewRequestBuf, 				//������װ�õ� MultiKDMsValidateRequest ������Ϣ�Ļ�������ַ 
		/*out*/ UInt32   				*len);
		
	/************************************************* 
    Function   �� ParseMultiKDMsValidateRequest()
    Description�� Parse 'MultiKDMsValidateRequest'Auditorium Security Message 
    Input      �� RequestBuf     :memory address of MultiKDMsValidateRequest
		          		RequestLen     :length of MultiKDMsValidateRequest 		
    Output     �� RequestId,     :Request Message id of AuditRequest
		          		UserID         :Certificate Thumbprint of uesr
		          		KDMListHead    :the head of the list of KDMInfo
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseMultiKDMsValidateRequest(
		/*in */ UInt8   				*RequestBuf,    			//���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   				RequestLen,    				//���յ���������Ϣ����
		/*out*/ UInt32  				*RequestId,     			//������Ϣ����ϢID
		/*out*/ TEXT    				*UserID,        			//�����û����û�֤��ָ��
		/*out*/ KDMINFO 				**KDMListHead);       		//�洢KDMInfo�������ͷָ��

	/************************************************* 
    Function   �� SetListMember()
    Description�� push each KDM Info into list 
    Input      �� KDMID    					:KDM ID        
                  KDMContentLen     :length of KDM Content
                  KDMContent   			:KDM Content
    Output     �� 	         
    Return     �� error code, refer to Const.h
    Others     :  The function is used to compose a list of KDM before FormatMultiKDMsValidateRequest,
                  the memory been used by list was malloc inside Function and free inside the the function FormatMultiKDMsValidateRequest
    *************************************************/
	UInt32 SetListMember(
		/*in */ const  TEXT      	*KDMID,    			//KDM ID
		/*in */ const  UInt8      Index,    			//KDM index in list, add by huweihua 11/06/20	
		/*in */ const  UInt32    	KDMContentLen,	//KDM���ݵĳ���
		/*in */ const  TEXT     	*KDMContent);		//KDM����

	/*************************************************
	Function   :  GetCurrentKDMLen()
	Description:  Get Current KDM len
	Input      :  KDMListHead	:the head of list 
	Output     :  
	Return     :  the length of the current KDM 
	Others     :  add by huweihua 11/06/23
	*************************************************/
	UInt32 GetCurrentKDMLen(const KDMINFO *&KDMListHead) const;


	/************************************************* 
    Function   �� GetListMember()
    Description�� get KDM Info from list 
    Input      �� KDMListHead				:the head of list    
    Output     �� KDMID    					:KDM ID        
                  pKDMContentLen    :length of KDM Content
                  KDMContent   			:KDM Content	         
    Return     �� error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.
                  application  call GetListMember() once gets one KDM Info, untill 
                  list is blank(i.e. head = NULL)
    *************************************************/
	UInt32 GetListMember(
		/*in */ KDMINFO 			**KDMListHead,		//�洢KDMInfo�������ͷָ��
		/*out*/ TEXT           *KDMID,       		//KDM ID
		/*out*/ UInt8          *Index,       		//KDM index in list, add by huweihua 11/06/20			
//	/*out*/ UInt32				 *pKDMContentLen,	//�洢KDM���ݳ��ȵ�ָ��  //delete by huweihua 11/06/20
		/*out*/ TEXT           *KDMContent);		//KDM����

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
	
	enum {MAXKDMNUM = 10};  //add by huweihua 11/06/20
	
  KDMINFO          *m_KDMListHead;		    //KDM�б�ͷָ��
  int               m_nKDMListNum;			  //KDM�б��а�����KDM����
	MessageULName    *MyMessageULName;      //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;      //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;   //��ϢID��ָ��
};
#endif


