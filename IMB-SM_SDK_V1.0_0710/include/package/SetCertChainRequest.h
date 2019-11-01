/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� SetCertChainRequest.h
Author     �� huweihua@dadimedia.com
Date       �� 2011/8/15
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--SetCertChainRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
  
********************************************/
#ifndef SETCERTCHAINREQUEST_H
#define SETCERTCHAINREQUEST_H

#include "package/MessageLength.h"
#include "package/MessageULName.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

//֤����Ϣ
typedef struct CertNode
{
    int   CertNameLen;      //֤��������
    char *CertName;         //֤����
    int   CertContentLen;   //֤�����ݳ���
    char *CertContent;      //֤������
    struct CertNode *next;  //�б���һ���ڵ�
}CERTNODE;

class SetCertChainRequest
{
public:

	SetCertChainRequest();
	~SetCertChainRequest();
	
    /************************************************* 
    Function   �� FormatSetCertChainRequest()
    Description�� format 'SetCertChainRequest' Auditorium Security Message 
    Input      �� CertType  ��Certificate type	         
    Output     �� NewRequestBuf :memory address of SetCertChainRequest
    	          len           :length of SetCertChainRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
    UInt32 FormatSetCertChainRequest(
      	/* in*/ TEXT    *UserID,
//			/* in*/  UInt32  CertType,			
				/* out*/ UInt8  *NewRequestBuf, 
				/* out*/ UInt32 *len);    

    /************************************************* 
    Function   �� ParseSetCertChainRequest()
    Description�� Parse 'SetCertChainRequest'Auditorium Security Message 
    Input      �� RequestBuf    :memory address of SetCertChainRequest
    	          RequestLen    :length of SetCertChainRequest 		
    Output     �� RequestId,    :Request Message id of SetCertChainRequest
    	          CertType      :Certificate type
    	          OCertListHead :the head of Certificate list 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/  
    UInt32 ParseSetCertChainRequest(
            	/* in */ UInt8     *RequestBuf, 
            	/* in */ UInt32     RequestLen, 
            	/* out*/ UInt32    *RequestId, 
  						/* out*/ TEXT      *UserID,
//            /* out*/ UInt32    *CertType,
            	/* out*/ CERTNODE  **OCertListHead);       

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
            
    /************************************************* 
    Function   �� AddCertInfo()
    Description�� add new certificate information to certificate list
    Input      �� CertNameLen   :the length of certificate name	
             	  CertName      :certificate name	
             	  CertContentLen:the length of certificate content
             	  CertContent   :certificate content
    Output     �� none
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/            
    UInt32 AddCertInfo(
            /* in*/int        CertNameLen, 
            /* in*/char      *CertName,
            /* in*/int        CertContentLen,
            /* in*/char      *CertContent);
            
     /************************************************* 
    Function   �� GetCertInfo()
    Description�� get ertificate information from certificate list
    Input      �� OCertListHead :the head of certificate list	         	 
    Output     �� CertNameLen   :the length of certificate name	
             	  CertName      :certificate name	
             	  CertContentLen:the length of certificate content
             	  CertContent   :certificate content
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/           
    UInt32 GetCertInfo(
            /* in*/CERTNODE **OCertListHead,
            /*out*/int       *CertNameLen, 
            /*out*/char      *CertName,
            /*out*/int       *CertContentLen,
            /*out*/char      *CertContent);

private:
    
	CERTNODE         *m_CertListHead;       //֤���б�
	int               m_CertListLen;        //֤���б����֤����
	MessageULName    *MyMessageULName;      //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;      //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;   //��ϢID��ָ��
};

#endif


