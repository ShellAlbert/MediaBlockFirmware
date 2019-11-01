/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DciLogRecord.h
* ժ    Ҫ����ȫ��־���ɻ������,��־������
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
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
	* DESCRIPTION : ��ȡ��־Header
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ������־Headerָ��
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordHeader *GetRecordHeader(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetRecordBody
	* DESCRIPTION : ��ȡ��־Body
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ������־Bodyָ��
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordBody *GetRecordBody(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetRecordSingature
	* DESCRIPTION : ��ȡ��־Singature
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ������־Singatureָ��
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordSignature *GetRecordSignature(void);
	/****FUNCTION***************************************************
	*		 		 NAME : ValidateHeader
	* DESCRIPTION : ��֤��־Header��Ч��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	bool ValidateHeader(void);
	/****FUNCTION***************************************************
	*		 		 NAME : ValidateBody
	* DESCRIPTION : ��֤��־Body��Ч��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	bool ValidateBody(void);
	/****FUNCTION***************************************************
	*		 		 NAME : ValidateSignature
	* DESCRIPTION : ��֤��־Signature��Ч��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	bool ValidateSignature(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetXmlString
	* DESCRIPTION : ��ȡ��־XML�ַ���
	*       INPUT : type ��־����(SingleRecord - ������־, ElementRecord - ��־Ԫ��)
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	const char * GetXmlString(RecordType type = SingleRecord);
	/****FUNCTION***************************************************
	*		 		 NAME : RemoveSignature
	* DESCRIPTION : �Ƴ���־ǩ��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ��
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
	//��־Headerָ��
	CDciLogRecordBody		*m_LogRecordBody;
	//��־Bodyָ��
	CDciLogRecordSignature	*m_LogRecordSignature;
	//��־Signatureָ��
	char *	m_XmlBuf;
	//XML�ַ���������
};

#endif
