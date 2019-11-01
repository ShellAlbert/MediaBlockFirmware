/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DciLogRecordSequence.h
* ժ    Ҫ����ȫ��־���ɻ������,��־��������,��־֤���༰֤������
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
*/
#ifndef DCI_LOG_RECORD_SEQUENCE_H
#define DCI_LOG_RECORD_SEQUENCE_H
#include <stdio.h>
#include "dcilogbase/DciLogRecord.h"
//��־֤����Ϣ��
class CDciLogCertInfo
{ 
public:
	CDciLogCertInfo(const char * issuerName = NULL, const char *serialNumber = NULL, const char *certificate = NULL);
	~CDciLogCertInfo(void);
	/****FUNCTION***************************************************
	*		 		 NAME : SetIssuerName
	* DESCRIPTION : ����֤��䷢�߱�ʶ
	*       INPUT : issuerName - �䷢�߱�ʶ
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : 
	****************************************************************/
	void SetIssuerName(const char *issuerName);
	/****FUNCTION***************************************************
	*		 		 NAME : GetIssuerName
	* DESCRIPTION : ��ȡ֤��䷢�߱�ʶ
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : �䷢�߱�ʶ
	*    CAUTIONS : 
	****************************************************************/
	const char *GetIssuerName(void) const;
	/****FUNCTION***************************************************
	*		 		 NAME : SetSerialNumber
	* DESCRIPTION : ����֤�����к�
	*       INPUT : serialNumber - ֤�����к�
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : 
	****************************************************************/
	void SetSerialNumber(const char *serialNumber);
	/****FUNCTION***************************************************
	*		 		 NAME : GetSerialNumber
	* DESCRIPTION : ��ȡ֤�����к�
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ֤�����к�
	*    CAUTIONS : 
	****************************************************************/
	const char *GetSerialNumber(void) const;
	/****FUNCTION***************************************************
	*		 		 NAME : SetCertificate
	* DESCRIPTION : ����֤������
	*       INPUT : certificate - ֤������
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : 
	****************************************************************/
	void SetCertificate(const char *certificate);
	/****FUNCTION***************************************************
	*		 		 NAME : GetCertificate
	* DESCRIPTION : ��ȡ֤������
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ֤������
	*    CAUTIONS : 
	****************************************************************/
	const char *GetCertificate(void) const;
private:
	char * strIssuerName;
	//�䷢�߱�ʶ
	char * strSerialNumber;
	//֤�����к�
	char * strCertificate;
	//֤������
};
////��־֤������
class CDciLogCertChain
{
public:
	CDciLogCertChain(void);
	~CDciLogCertChain(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetCount
	* DESCRIPTION : ��ȡ֤������
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ֤������
	*    CAUTIONS : 
	****************************************************************/
	unsigned int GetCount(void) const;
	/****FUNCTION***************************************************
	*		 		 NAME : GetCert
	* DESCRIPTION : ��ȡָ��֤��
	*       INPUT : index - ֤������
	*      OUTPUT : ��
	*     RETURNS : ֤��ָ��, NULL��ʾ֤�鲻����
	*    CAUTIONS : 
	****************************************************************/
	CDciLogCertInfo * GetCert(unsigned int index);
	/****FUNCTION***************************************************
	*		 		 NAME : AddCert
	* DESCRIPTION : ���֤��
	*       INPUT : pCert - ֤��
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : 
	****************************************************************/
	void AddCert(CDciLogCertInfo &pCert);
private:
	CDciLogCertInfo **m_CertList;
	//֤���б�
	unsigned int	m_Size;
	//֤������
	unsigned int	m_MaxSize;
};
//��־����
class CDciLogRecordSequence
{
public:
	CDciLogRecordSequence( int count = 0, char *outfile = NULL, bool isAddSignature = false, const CDciLogCertInfo *pDeviceCert = NULL, CDciLogCertChain *deviceCertChain = NULL, void *evpPriKey = NULL, const char *signMethod = "RSA-SHA-256");
	~CDciLogRecordSequence(void);
	/****FUNCTION***************************************************
	*		 		 NAME : AddRecord
	* DESCRIPTION : �����־�ڵ�
	*       INPUT : pLogRecord - ��־
	*      OUTPUT : ��
	*     RETURNS : true - ��ӳɹ�, false - ���ʧ��
	*    CAUTIONS : 
	****************************************************************/
	bool AddRecord(CDciLogRecord *pLogRecord);
	/****FUNCTION***************************************************
	*		 		 NAME : GetXmlString
	* DESCRIPTION : ������־��XML�ַ���
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : XML��
	*    CAUTIONS : 
	****************************************************************/
	const char * GetXmlString();
private:
	CDciLogRecord **m_pRecordList;
	//��־�б�
	unsigned int	m_Size;
	//��־����
	unsigned int	m_MaxSize;
	char			*m_XmlString;
	//XML��������
	bool			m_IsSign;
	//ǩ�����
	CDciLogCertInfo		*m_DeviceCert;
	//ǩ��֤��
	CDciLogCertChain	*m_DeviceCertChain;
	//ǩ��֤����
	void			*m_PriKey;
	//ǩ��˽Կ
	unsigned int	m_signMethod;
	//ǩ���㷨
//tangquanfa add start
	char	prevHeaderStr[1000];
	int		m_count;
	FILE	*m_fp;
//tangquanfa add end
};
#endif
