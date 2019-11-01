/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：DciLogRecord.h
* 摘    要：安全日志生成基础类库,日志生成类
* * 当前版本：1.0
* 作    者：马静山
* 取代版本：无
*/
#ifndef DCI_LOG_RECORD_H
#define DCI_LOG_RECORD_H
#include "dcilogbase/DciLogRecordHeader.h"
#include "dcilogbase/DciLogRecordBody.h"
#include "dcilogbase/DciLogRecordSignature.h"
class CDciLogRecord
{
public:
	typedef enum{SingleRecord, ElementRecord}RecordType;
public:
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] modified by chenjingdong, 2013-05-17 start 
	/* CDciLogRecord(const char * str = NULL); */

	CDciLogRecord(const char * str = NULL, \
		CDciLogRecordHeader::LogOutputMode eOutputMod = CDciLogRecordHeader::DCI_LOG_NORMAL);
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	~CDciLogRecord(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetRecordHeader
	* DESCRIPTION : 获取日志Header
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 返回日志Header指针
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordHeader *GetRecordHeader(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetRecordBody
	* DESCRIPTION : 获取日志Body
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 返回日志Body指针
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordBody *GetRecordBody(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetRecordSingature
	* DESCRIPTION : 获取日志Singature
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 返回日志Singature指针
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordSignature *GetRecordSignature(void);
	/****FUNCTION***************************************************
	*		 		 NAME : ValidateHeader
	* DESCRIPTION : 验证日志Header有效性
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	bool ValidateHeader(void);
	/****FUNCTION***************************************************
	*		 		 NAME : ValidateBody
	* DESCRIPTION : 验证日志Body有效性
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	bool ValidateBody(void);
	/****FUNCTION***************************************************
	*		 		 NAME : ValidateSignature
	* DESCRIPTION : 验证日志Signature有效性
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	bool ValidateSignature(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetXmlString
	* DESCRIPTION : 获取日志XML字符串
	*       INPUT : type 日志类型(SingleRecord - 独立日志, ElementRecord - 日志元素)
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	const char * GetXmlString(RecordType type = SingleRecord);
	/****FUNCTION***************************************************
	*		 		 NAME : RemoveSignature
	* DESCRIPTION : 移除日志签名
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 
	****************************************************************/
	void RemoveSignature(void);

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	/****FUNCTION***************************************************
	*		 		 NAME : GetOutputModeByHeader
	* DESCRIPTION : obtains output mode from the record header
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordHeader::LogOutputMode GetOutputModeByHeader() const 
	{
		return m_LogRecordHeader ? m_LogRecordHeader->GetOutputMode() : CDciLogRecordHeader::DCI_LOG_NORMAL; 
	};

	/****FUNCTION***************************************************
	*		 		 NAME : GetOutputModeByBody
	* DESCRIPTION : obtains output mode from the record body
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : 
	****************************************************************/
	//CDciLogRecordHeader::LogOutputMode GetOutputModeByBody() const 
	//{
	//	return m_LogRecordBody ? m_LogRecordBody->GetOutputMode() : CDciLogRecordHeader::DCI_LOG_NORMAL;
	//};
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

protected:
	CDciLogRecordHeader		*m_LogRecordHeader;
	//日志Header指针
	CDciLogRecordBody		*m_LogRecordBody;
	//日志Body指针
	CDciLogRecordSignature	*m_LogRecordSignature;
	//日志Signature指针
	char *	m_XmlBuf;
	//XML字符串缓冲区
};

#endif
