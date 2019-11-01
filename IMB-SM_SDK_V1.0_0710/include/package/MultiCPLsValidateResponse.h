/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MultiCPLsValidateResponse.h
Author     �� sunpeng@dadimedia.com
Date       �� 11/05/10
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--MultiCPLsValidateRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
 huweihua@dadimedia.com   11/06/20           implement request according to new message struct
********************************************/
#ifndef MULTICPLSVALIDATERESPONSE_H
#define MULTICPLSVALIDATERESPONSE_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

//delete by huweihua 11/06/20
//typedef struct CPLResult
//{
//	UInt8   CPLID[CPL_ID_MAX_LEN]; 		//CPLID
//	UInt32  CPLValidResult;        		//result of CPL validate
//	struct 	CPLResult* pNext;  			//next node
//}CPLRESULT;

class MultiCPLsValidateResponse
{
public:

	MultiCPLsValidateResponse();
	~MultiCPLsValidateResponse();
	
	/************************************************* 
    Function   �� FormatMultiCPLsValidateResponse()
    Description�� format 'MultiCPLsValidateResponse' Auditorium Security Message 
    Input      �� RequestId        	:Request Message id of 	MultiCPLsValidateRequest
        		  		ResponseStatus  	:General Response Elements
    Output     �� NewResponseBuf 		:memory address of MultiCPLsValidateResponse
		          		len           		:length of MultiCPLsValidateResponse 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatMultiCPLsValidateResponse(
		/*in */ UInt32  							 RequestId, 						//��Ӧ MultiCPLsValidateRequest ������Ϣ����ϢID
		/*in */ UInt8   							 ResponseStatus, 				//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h
		/*out*/ UInt8    							*NewResponseBuf, 				//������װ�õ� MultiCPLsValidateResponse �ظ���Ϣ�Ļ�������ַ 
		/*out*/ UInt32   							*len);							//��װ�õ� MultiCPLsValidateResponse ��Ϣ����
		
	/************************************************* 
    Function   �� ParseMultiCPLsValidateResponse()
    Description�� Parse 'MultiCPLsValidateResponse'Auditorium Security Message 
    Input      �� ResponseBuf    :memory address of MultiCPLsValidateResponse
		          		ResponseLen    :length of MultiCPLsValidateResponse 		
    Output     �� RequestId,     :Request Message id of MultiCPLsValidateRequest
		          		CPLResultListHead           :the head of the list of CPLResult
        		  		ResponseStatus :General Response Elements
	          		
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseMultiCPLsValidateResponse(
		/*in */ UInt8   							*ResponseBuf,    			//���յ��Ļظ���Ϣ�Ĵ洢����ַ
		/*in */ UInt32   							 ResponseLen,    			//���յ��Ļظ���Ϣ����
		/*out*/ UInt32  							*RequestId,     			//������Ϣ����ϢID
//	/*out*/ CPLRESULT 					  **CPLResultListHead,   //�洢CPLResultList�������ͷָ�� //delete by huweihua 11/06/20
		/*out*/ UInt8  								*ResponseStatus); 		//ͨ�ûظ�״ֵ̬��ȡֵΪ0-3��������Ͳμ�Const.h

//delete by huweihua 11/06/20
//	/************************************************* 
//    Function   �� SetListMember() 
//    Description�� push each CPL Result into list 
//    Input      �� CPLID    					:CPL ID        
//                  CPLValidResult   			:Result of CPL Validation
//    Output     �� 	         
//    Return     �� error code, refer to Const.h
//    Others     :  The function is used to compose a list of CPL before FormatMultiCPLsValidateResponse,
//                  the memory been used by list was malloc inside Function and free inside the the function FormatMultiCPLsValidateResponse
//    *************************************************/
// 
//	UInt32 SetListMember(
//		/*in */ const  TEXT      			*CPLID,    				//CPL ID
//		/*in */ const  UInt32    			CPLValidResult);		//CPL ��֤���
//
//
//	/************************************************* 
//    Function   �� GetListMember()
//    Description�� get CPL Info from list 
//    Input      �� head     					:the head of list    
//    Output     �� CPLID    					:CPL ID        
//                  pCPLResult				:Result of CPL Validation
//    Return     �� error code, refer to Const.h
//    Others     :  the memory been used by list  was malloc and delete inside Function.
//                  application  call GetListMember() once gets one CPL Result
//    *************************************************/
//	UInt32 GetListMember(
//		/*in */ CPLRESULT 					**CPLResultListHead,    //�洢CPLInfo�������ͷָ��
//		/*out*/ TEXT            			*CPLID,      			//CPL ID
//		/*out*/ UInt32        				*pCPLResult);			//CPL ��֤�����ָ��
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
//	Function   :  SetCPLResult()
//	Description:  transform CPLResult to the message saved in memory
//	Input      :  KDMResult:			CPLResult want to set
//	Output     :  CPLResultBuf:			memory address of CPLResult message
//	Return     �� error code, refer to Const.h
//	Others     :        
//	 *************************************************/
//	UInt32 SetCPLResult(
//		/*in */ UInt32  CPLResult,
//		/*out*/ UInt8  *CPLResultBuf);
//
//	/*************************************************
//	Function   :  GetCPLResult()
//	Description:  transform the CPLResult message saved in memory to integer
//	Input      :  CPLResultBuf : memory address of CPLResult message	
//	Output     :  
//	Return     :  error code, refer to Const.h
//	Others     :
//	*************************************************/
//	UInt32 GetCPLResult(
//	/*in */ UInt8  *CPLResultBuf);

private:

//  CPLRESULT       *m_CPLResultListHead;		//CPL��֤����б�ͷָ��delete by huweihua 11/06/20
//  int              m_CPLResultListNum;		//�б��а�����CPL��֤����ĸ���delete by huweihua 11/06/20
	MessageULName    *MyMessageULName;			//��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;			//��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId;		//��ϢID��ָ��
};
#endif


