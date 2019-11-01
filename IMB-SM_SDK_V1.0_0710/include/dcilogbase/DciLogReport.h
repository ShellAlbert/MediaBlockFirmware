/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：DciLogReport.h
* 摘    要：安全日志生成基础类库,数字签名接口类
* * 当前版本：1.0
* 作    者：马静山
* 取代版本：无
*/
#ifndef DCI_LOG_REPORT_H
#define DCI_LOG_REPORT_H
#include "dcilogbase/DciLogRecord.h"
#include "dcilogbase/DciLogRecordSequence.h"
#include "dcilogbase/DciDeviceDescription.h"
#include "dcilogbase/DciLogReportValidator.h" //[CSTSM_v1.0_DCEventLog_v2.0] added by chenjingdong, 2013-07-15
#include "xml/XmlDocument.h"

class CDciLogReport
{
public:
	CDciLogReport(void);
	~CDciLogReport(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetReportString
	* DESCRIPTION : 生成日志报表XML串
	*       INPUT : filter - 日志过虑(未实现,需要根据具体需求确定)
	*								recordHeaderOnly - 生成的报表中日志节点只包含HEADER节点
	*      OUTPUT : 无
	*     RETURNS : NULL表示生成失败
	*    CAUTIONS : 
	****************************************************************/
	const char * GetReportString(const char * filter = NULL, bool recordHeaderOnly = false);
	/****FUNCTION***************************************************
	*		 		 NAME : SetReportDate
	* DESCRIPTION : 设置ReportDate节点
	*       INPUT : strReportDate - 日期值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	bool SetReportDate(const char *strReportDate);
	/****FUNCTION***************************************************
	*		 		 NAME : AddLogSequence
	* DESCRIPTION : 添加日志链
	*       INPUT : pLogRecordSequence - 日志链
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	void AddLogSequence(CDciLogRecordSequence *pLogRecordSequence);
	/****FUNCTION***************************************************
	*		 		 NAME : GetReportingDevice
	* DESCRIPTION : 获取日志报表生成设备
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 设备信息结构体
	*    CAUTIONS : 
	****************************************************************/
	CDciDeviceDescription *GetReportingDevice(void);
	
	//[CSTSM_v1.0_DCEventLog_v2.0] added by chenjingdong, 2013-07-15 start
	bool ValidateReportByDom(const char * pReport, ValidResultOfReport& rValidResult, ValidMode eValMod = MOD_FILE, \
								Running_Mode eRunMod = EXIT_ON_ERR, bool bIsVerbose = true);
	//[CSTSM_v1.0_DCEventLog_v2.0] end
		
private:
	CDciLogRecordSequence m_RecordList;
	CDciLogRecordSequence **m_SequenceList;
	//日志链列表
	unsigned int	m_SeqSize;
	//日志链数量
	unsigned int	m_SeqMaxSize;
	//日志链缓冲区容量
	CXmlNode		*m_RootNode;
	//日志报表XML树根结点
	CXmlDocument	*m_XmlDoc;
	//日志报表XML树
	CXmlNode		*m_DeviceDescription;
	//日志报表XML树设备描述节点
	CXmlNode        *m_ReportDate;
	CDciDeviceDescription *m_ReportingDevice;
	//日志报表设备描述
};
#endif
