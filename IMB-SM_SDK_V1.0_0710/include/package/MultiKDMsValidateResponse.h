/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MultiKDMsValidateResponse.h
Author     �� sunpeng@dadimedia.com
Date       �� 11/05/06
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--MultiKDMsValidateRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
huweihua@dadimedia.com   11/06/20           implement request according to new message struct
********************************************/
#ifndef MULTIKDMSVALIDATERESPONSE_H
#define MULTIKDMSVALIDATERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

//comment by huweihua 11/06/20
//typedef struct KDMResult
//{
//	UInt8   KDMID[KDM_ID_MAX_LEN]; 		//KDMID
//	UInt32  KDMValidResult;        		//result of KDM validate
//	struct 	KDMResult* pNext;  			//next node
//}KDMRESULT;

class MultiKDMsValidateResponse
{
public:

	MultiKDMsValidateResponse();
	~MultiKDMsValidateResponse();
	
	/************************************************* 
    Function   �� FormatMultiKDMsValidateResponse()
    Description�� format 'MultiKDMsValidateResponse' Auditorium Security Message 
    Input      �� RequestId        	:Request Message id of 	MultiKDMsValidateRequest
        		  		ResponseStatus  	:General Response Elements
    Output     �� NewResponseBuf 		:memory address of MultiKDMsValidateResponse
		          		len           		:length of MultiKDMsValidateResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatMultiKDMsValidateResponse(
		/*in */ UInt32  							RequestId, 							//��Ӧ MultiKDMsValidateRequest ������Ϣ����ϢID
		/*in */ UInt8   							ResponseStatus, 				//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8    							*NewResponseBuf, 				//������װ�õ� MultiKDMsValidateResponse �ظ���Ϣ�Ļ�������ַ 
		/*out*/ UInt32   							*len);									//��װ�õ� MultiKDMsValidateResponse ��Ϣ����
		
	/************************************************* 
    Function   �� ParseMultiKDMsValidateResponse()
    Description�� Parse 'MultiKDMsValidateResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of MultiKDMsValidateResponse
		          		ResponseLen    :length of MultiKDMsValidateResponse 		
    Output     �� RequestId,     :Request Message id of MultiKDMsValidateRequest
		          		KDMResultListHead           :the head of the list of KDMResult
        		  		ResponseStatus :General Response Elements
	          		
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseMultiKDMsValidateResponse(
		/*in */ UInt8   							*ResponseBuf,    			//���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32   							 ResponseLen,    			//���յ��Ļظ���Ϣ����
		/*out*/ UInt32  							*RequestId,     			//������Ϣ����ϢID
//	/*out*/ KDMRESULT 					 **KDMResultListHead,   //�洢KDMResultList�������ͷָ�� delete by huweihua 11/06/20
		/*out*/ UInt8  								*ResponseStatus); 		//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h


//delete by huweihua 11/06/20
//	/************************************************* 
//    Function   �� SetListMember()
//    Description�� push each KDM Result into list 
//    Input      �� KDMID    					:KDM ID        
//                  KDMValidResult   			:Result of KDM Validation
//    Output     �� 	         
//    Return     �� error code, refer to Const.h
//    Others     :  The function is used to compose a list of KDM before FormatMultiKDMsValidateResponse,
//                  the memory been used by list was malloc inside Function and free inside the the function FormatMultiKDMsValidateResponse
//    *************************************************/
// 
//	UInt32 SetListMember(
//		/*in */ const  TEXT      			*KDMID,    				//KDM ID
//		/*in */ const  UInt32    			KDMValidResult);		//KDM ��֤���
//
//
//	/************************************************* 
//    Function   �� GetListMember()
//    Description�� get KDM Info from list 
//	Input      �� KDMResultListHead			:the head of list    
//    Output     �� KDMID    					:KDM ID        
//                  pKDMResult				:Result of KDM Validation
//    Return     �� error code, refer to Const.h
//    Others     :  the memory been used by list  was malloc and delete inside Function.
//                  application  call GetListMember() once gets one KDM Result
//    *************************************************/
//	UInt32 GetListMember(
//		/*in */ KDMRESULT 					**KDMResultListHead,    //�洢KDMInfo�������ͷָ��
//		/*out*/ TEXT            			*KDMID,      			//KDM ID
//		/*out*/ UInt32        				*pKDMResult);			//KDM ��֤�����ָ��
//
//    /************************************************* 
//    Function   �� ParseBufToLen()
//    Description�� transform the message saved in memory to integer
//    Input      �� Buf       :memory address of message
//    	          BufLen    :the length of message 	memory		      
//    Output     ��
//    Return     �� integer match along with message saved in memory
//    Others     :        
//    *************************************************/ 			
//    UInt32 ParseBufToLen(
//            /*in*/UInt8 *Buf, 
//            /*in*/UInt32 BufLen);
//
//    /************************************************* 
//    Function   �� ParseLenToBuf()
//    Description�� transform integer to the message saved in memory 
//    Input      �� IntNum       :integer want to transform	
//             	  BufLen       :the length of message 	memory
//    Output     �� Buf          :memory address of message
//    Return     �� error code, refer to Const.h
//    Others     :        
//    *************************************************/            
//    UInt32 ParseLenToBuf(
//            /* in*/UInt32  IntNum,
//            /* in*/UInt32  BufLen,
//            /*out*/UInt8  *Buf);		
//
//	/*************************************************
//	Function   :  SetKDMResult()
//	Description:  transform KDMResult to the message saved in memory
//	Input      :  KDMResult:			KDMResult want to set
//	Output     :  KDMResultBuf:			memory address of KDMResult message
//	Return     �� error code, refer to Const.h
//	Others     :        
//	 *************************************************/
//	UInt32 SetKDMResult(
//		/*in */ UInt32  KDMResult,
//		/*out*/ UInt8  *KDMResultBuf);
//
//	/*************************************************
//	Function   :  GetKDMResult()
//	Description:  transform the KDMResult message saved in memory to integer
//	Input      :  KDMResultBuf : memory address of KDMResult message	
//	Output     :  
//	Return     :  error code, refer to Const.h
//	Others     :
//	*************************************************/
//	UInt32 GetKDMResult(
//	/*in */ UInt8  *KDMResultBuf);
		
private:	
	
//delete by huweihua 11/06/20	
//KDMRESULT       *m_KDMResultListHead;		//KDM��֤����б�ͷָ��
//int              m_KDMResultListNum;		//�б��а�����KDM��֤����ĸ���

	MessageULName    *MyMessageULName;			//��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;			//��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;		//��ϢID��ָ��
};
#endif


