/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： MultiCPLsValidateRequest.h
Author     ： sunpeng@dadimedia.com
Date       ： 11/05/10
Version    ： v1.0
Description： Auditorium Security Message(SMS->SM)--MultiCPLsValidateRequest
Others     :  
History    ： 
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
    Function   ： FormatMultiCPLsValidateRequest()
    Description： format 'MultiCPLsValidateRequest' Auditorium Security Message 
    Input      ： UserID        :Certificate Thumbprint of uesr	
    Output     ： NewRequestBuf :memory address of MultiCPLsValidateRequest
		          		len           :length of MultiCPLsValidateRequest 
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/ 
	UInt32 FormatMultiCPLsValidateRequest(
		/*in */ TEXT     				*UserID,        				//操作用户的用户证书指纹
		/*out*/ UInt8    				*NewRequestBuf, 				//接收组装好的 MultiCPLsValidateRequest 请求消息的缓冲区地址 
		/*out*/ UInt32   				*len);
		
	/************************************************* 
    Function   ： ParseCPLValidateRequest()
    Description： Parse 'MultiCPLsValidateRequest'Auditorium Security Message 
    Input      ： RequestBuf     :memory address of MultiCPLsValidateRequest
		          		RequestLen     :length of MultiCPLsValidateRequest 		
    Output     ： RequestId,     :Request Message id of AuditRequest
		          		UserID         :Certificate Thumbprint of uesr
		          		CPLListHead    :the head of the list of CPLInfo
    Return     ： error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 ParseMultiCPLsValidateRequest(
		/*in */ UInt8   				*RequestBuf,    			//接收到的请求消息的存储区地址
		/*in */ UInt32   				 RequestLen,    			//接收到的请求消息长度
		/*out*/ UInt32  				*RequestId,     			//请求消息的消息ID
		/*out*/ TEXT    				*UserID,        			//操作用户的用户证书指纹
		/*out*/ UInt32          *CPLNumber,           //add by huweihua 11/06/27
		/*out*/ CPLINFO 			 **CPLListHead);       	//存储CPLInfo的链表的头指针

	/************************************************* 
    Function   ： SetListMember()
    Description： push each CPL Info into list 
    Input      ： CPLID    					:CPL ID        
				  CPLPreCheckResult			:CPL PreCheck Result
                  CPLContentLen     :length of CPL Content
                  CPLContent   			:CPL Content
    Output     ： 	         
    Return     ： error code, refer to Const.h
    Others     :  The function is used to compose a list of CPL before FormatMultiCPLsValidateRequest,
                  the memory been used by list was malloc inside Function and free inside the the function FormatMultiCPLsValidateRequest
    *************************************************/
	UInt32 SetListMember(
		/*in */ const  TEXT      	*CPLID,    			//CPL ID
		/*in */ const  UInt8      Index,    			//CPL index in list, add by huweihua  11/06/20	  
		/*in */ const  UInt32    	CPLPreCheckResult,	//CPL预验证结果
		/*in */ const  UInt32    	CPLContentLen,		//CPL内容的长度
		/*in */ const  TEXT     	*CPLContent);		//CPL内容

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
    Function   ： GetListMember()
    Description： get CPL Info from list 
    Input      ： CPLListHead				:the head of list    
    Output     ： CPLID    					:CPL ID        
				  pCPLPreCheckResult		:CPL PreCheck Result
                  pCPLContentLen    :length of CPL Content
                  CPLContent   			:CPL Content	         
    Return     ： error code, refer to Const.h
    Others     :  the memory been used by list  was malloc and delete inside Function.
                  application  call GetListMember() once gets one CPL Info, untill 
                  list is blank(i.e. head = NULL)
    *************************************************/
	UInt32 GetListMember(
		/*in */ CPLINFO 		 **CPLListHead,		//存储CPLInfo的链表的头指针
		/*out*/ TEXT          *CPLID,       		//CPL ID
		/*out*/ UInt8         *Index,         //CPL index in list, add by huweihua 11/06/20
		/*out*/ UInt32				*pCPLPreCheckResult,//存储预验证结果的指针
//  /*out*/ UInt32				*pCPLContentLen,	//存储CPL内容长度的指针 //delete by huweihua 11/06/23
		/*out*/ TEXT          *CPLContent);		//CPL内容

    /************************************************* 
    Function   ： ParseBufToLen()
    Description： transform the message saved in memory to integer
    Input      ： Buf       :memory address of message
    	          BufLen    :the length of message 	memory		      
    Output     ：
    Return     ： integer match along with message saved in memory
    Others     :        
    *************************************************/ 			
    UInt32 ParseBufToLen(
            /*in*/UInt8 *Buf, 
            /*in*/UInt32 BufLen);

    /************************************************* 
    Function   ： ParseLenToBuf()
    Description： transform integer to the message saved in memory 
    Input      ： IntNum       :integer want to transform	
             	  BufLen       :the length of message 	memory
    Output     ： Buf          :memory address of message
    Return     ： error code, refer to Const.h
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
	Return     ： error code, refer to Const.h
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
	
	CPLINFO          *m_CPLListHead;		  //CPL列表头指针
	int               m_nCPLListNum;			//CPL列表中包含的CPL个数
	MessageULName    *MyMessageULName;    //消息头（KEY in KLV struct）类指针
	MessageLength    *MyMessageLength;    //消息长度（Length in KLV struct）类指针
	MessageRequestId *MyMessageRequestId; //消息ID类指针
};
#endif


