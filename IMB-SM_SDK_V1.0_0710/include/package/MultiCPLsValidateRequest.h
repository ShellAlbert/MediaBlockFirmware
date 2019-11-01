/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MultiCPLsValidateRequest.h
Author     �� sunpeng@dadimedia.com
Date       �� 11/05/10
Version    �� v1.0
Description�� Auditorium Security Message(SMS->SM)--MultiCPLsValidateRequest
Others     :  
History    �� 
      < Author >    			< Date >             < Modification >
 huweihua@dadimedia.com   11/06/20           implement request according to new message struct
********************************************/
#ifndef MULTICPLSVALIDATEREQUEST_H
#define MULTICPLSVALIDATEREQUEST_H

#include "package/MessageULName.h"
#include "package/MessageLength.h"
#include "package/MessageRequestId.h"
#include "package/Const.h"

typedef struct CPLInfo
{
	//UInt8   CPLID[CPL_ID_MAX_LEN]; 	//CPLID
	TEXT    CPLID[CPL_ID_MAX_LEN]; 	  //CPLID  //modify by huweihua 11/06/20
	UInt8   Index; 	//CPL index in list. add by huweihua 11/06/20
	UInt32	CPLPreCheckResult;		//CPL PreCheck Result	
	UInt32  CPLContentLen;        	//length of CPL Content
	TEXT  	*CPLContent;     		//pointer of CPL Content
	struct 	CPLInfo* pNext;  		//next node
}CPLINFO;

class MultiCPLsValidateRequest
{
public:

	MultiCPLsValidateRequest();
	~MultiCPLsValidateRequest();
	
	/************************************************* 
    Function   �� FormatMultiCPLsValidateRequest()
    Description�� format 'MultiCPLsValidateRequest' Auditorium Security Message 
    Input      �� UserID        :Certificate Thumbprint of uesr	
    Output     �� NewRequestBuf :memory address of MultiCPLsValidateRequest
		          		len           :length of MultiCPLsValidateRequest 
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatMultiCPLsValidateRequest(
		/*in */ TEXT     				*UserID,        				//�����û����û�֤��ָ��
		/*out*/ UInt8    				*NewRequestBuf, 				//������װ�õ� MultiCPLsValidateRequest ������Ϣ�Ļ�������ַ 
		/*out*/ UInt32   				*len);
		
	/************************************************* 
    Function   �� ParseCPLValidateRequest()
    Description�� Parse 'MultiCPLsValidateRequest'Auditorium Security Message 
    Input      �� RequestBuf     :memory address of MultiCPLsValidateRequest
		          		RequestLen     :length of MultiCPLsValidateRequest 		
    Output     �� RequestId,     :Request Message id of AuditRequest
		          		UserID         :Certificate Thumbprint of uesr
		          		CPLListHead    :the head of the list of CPLInfo
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseMultiCPLsValidateRequest(
		/*in */ UInt8   				*RequestBuf,    			//���յ���������Ϣ�Ĵ洢����ַ
		/*in */ UInt32   				 RequestLen,    			//���յ���������Ϣ����
		/*out*/ UInt32  				*RequestId,     			//������Ϣ����ϢID
		/*out*/ TEXT    				*UserID,        			//�����û����û�֤��ָ��
		/*out*/ UInt32          *CPLNumber,           //add by huweihua 11/06/27
		/*out*/ CPLINFO 			 **CPLListHead);       	//�洢CPLInfo�������ͷָ��

	/************************************************* 
    Function   �� SetListMember()
    Description�� push each CPL Info into list 
    Input      �� CPLID    					:CPL ID        
				  CPLPreCheckResult			:CPL PreCheck Result
                  CPLContentLen     :length of CPL Content
                  CPLContent   			:CPL Content
    Output     �� 	         
    Return     �� error code, refer to Const.h
    Others     :  The function is used to compose a list of CPL before FormatMultiCPLsValidateRequest,
                  the memory been used by list was malloc inside Function and free inside the the function FormatMultiCPLsValidateRequest
    *************************************************/
	UInt32 SetListMember(
		/*in */ const  TEXT      	*CPLID,    			//CPL ID
		/*in */ const  UInt8      Index,    			//CPL index in list, add by huweihua  11/06/20	  
		/*in */ const  UInt32    	CPLPreCheckResult,	//CPLԤ��֤���
		/*in */ const  UInt32    	CPLContentLen,		//CPL���ݵĳ���
		/*in */ const  TEXT     	*CPLContent);		//CPL����

	/*************************************************
	Function   :  GetCurrentCPLlen()
	Description:  Get Current CPL len
	Input      :  CPLListHead	:the head of list 
	Output     :  
	Return     :  the length of the current CPL 
	Others     :  add by huweihua 11/06/23
	*************************************************/
	UInt32 GetCurrentCPLlen(const CPLINFO *&CPLListHead) const;
	
	
	/************************************************* 
    Function   �� GetListMember()
    Description�� get CPL Info from list 
    Input      �� CPLListHead				:the head of list    
    Output     �� CPLID    					:CPL ID        
				  pCPLPreCheckResult		:CPL PreCheck Result
                  pCPLContentLen    :length of CPL Content
                  CPLContent   			:CPL Content	         
    Return     �� error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.
                  application  call GetListMember() once gets one CPL Info, untill 
                  list is blank(i.e. head = NULL)
    *************************************************/
	UInt32 GetListMember(
		/*in */ CPLINFO 		 **CPLListHead,		//�洢CPLInfo�������ͷָ��
		/*out*/ TEXT          *CPLID,       		//CPL ID
		/*out*/ UInt8         *Index,         //CPL index in list, add by huweihua 11/06/20
		/*out*/ UInt32				*pCPLPreCheckResult,//�洢Ԥ��֤�����ָ��
//  /*out*/ UInt32				*pCPLContentLen,	//�洢CPL���ݳ��ȵ�ָ�� //delete by huweihua 11/06/23
		/*out*/ TEXT          *CPLContent);		//CPL����

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
	Function   :  SetCPLResult()
	Description:  transform CPLResult to the message saved in memory
	Input      :  KDMResult:			CPLResult want to set
	Output     :  CPLResultBuf:			memory address of CPLResult message
	Return     �� error code, refer to Const.h
	Others     :        
	 *************************************************/
	UInt32 SetCPLPreCheckResult(
		/*in */ UInt32  CPLResult,
		/*out*/ UInt8  *CPLResultBuf);

	/*************************************************
	Function   :  GetCPLResult()
	Description:  transform the CPLResult message saved in memory to integer
	Input      :  CPLResultBuf : memory address of CPLResult message	
	Output     :  
	Return     :  error code, refer to Const.h
	Others     :
	*************************************************/
	UInt32 GetCPLPreCheckResult(
	/*in */ UInt8  *CPLResultBuf);

private:	
	
	enum {MAXCPLNUM = 10};                //add by huweihua 11/06/20
	
	CPLINFO          *m_CPLListHead;		  //CPL�б�ͷָ��
	int               m_nCPLListNum;			//CPL�б��а�����CPL����
	MessageULName    *MyMessageULName;    //��Ϣͷ��KEY in KLV struct����ָ��
	MessageLength    *MyMessageLength;    //��Ϣ���ȣ�Length in KLV struct����ָ��
	MessageRequestId *MyMessageRequestId; //��ϢID��ָ��
};
#endif


