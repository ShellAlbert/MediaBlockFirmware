/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DciLogReport.h
* ժ    Ҫ����ȫ��־���ɻ������,����ǩ���ӿ���
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
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
	* DESCRIPTION : ������־����XML��
	*       INPUT : filter - ��־����(δʵ��,��Ҫ���ݾ�������ȷ��)
	*								recordHeaderOnly - ���ɵı�������־�ڵ�ֻ����HEADER�ڵ�
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾ����ʧ��
	*    CAUTIONS : 
	****************************************************************/
	const char * GetReportString(const char * filter = NULL, bool recordHeaderOnly = false);
	/****FUNCTION***************************************************
	*		 		 NAME : SetReportDate
	* DESCRIPTION : ����ReportDate�ڵ�
	*       INPUT : strReportDate - ����ֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	bool SetReportDate(const char *strReportDate);
	/****FUNCTION***************************************************
	*		 		 NAME : AddLogSequence
	* DESCRIPTION : �����־��
	*       INPUT : pLogRecordSequence - ��־��
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	void AddLogSequence(CDciLogRecordSequence *pLogRecordSequence);
	/****FUNCTION***************************************************
	*		 		 NAME : GetReportingDevice
	* DESCRIPTION : ��ȡ��־���������豸
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : �豸��Ϣ�ṹ��
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
	//��־���б�
	unsigned int	m_SeqSize;
	//��־������
	unsigned int	m_SeqMaxSize;
	//��־������������
	CXmlNode		*m_RootNode;
	//��־����XML�������
	CXmlDocument	*m_XmlDoc;
	//��־����XML��
	CXmlNode		*m_DeviceDescription;
	//��־����XML���豸�����ڵ�
	CXmlNode        *m_ReportDate;
	CDciDeviceDescription *m_ReportingDevice;
	//��־�����豸����
};
#endif
