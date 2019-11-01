/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：DciLogRecordSequence.h
* 摘    要：安全日志生成基础类库,日志链生成类,日志证书类及证书链类
* * 当前版本：1.0
* 作    者：马静山
* 取代版本：无
*/
#ifndef DCI_LOG_RECORD_SEQUENCE_H
#define DCI_LOG_RECORD_SEQUENCE_H
#include <stdio.h>
#include "dcilogbase/DciLogRecord.h"
//日志证书信息类
class CDciLogCertInfo
{ 
public:
	CDciLogCertInfo(const char * issuerName = NULL, const char *serialNumber = NULL, const char *certificate = NULL);
	~CDciLogCertInfo(void);
	/****FUNCTION***************************************************
	*		 		 NAME : SetIssuerName
	* DESCRIPTION : 设置证书颁发者标识
	*       INPUT : issuerName - 颁发者标识
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 
	****************************************************************/
	void SetIssuerName(const char *issuerName);
	/****FUNCTION***************************************************
	*		 		 NAME : GetIssuerName
	* DESCRIPTION : 获取证书颁发者标识
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 颁发者标识
	*    CAUTIONS : 
	****************************************************************/
	const char *GetIssuerName(void) const;
	/****FUNCTION***************************************************
	*		 		 NAME : SetSerialNumber
	* DESCRIPTION : 设置证书序列号
	*       INPUT : serialNumber - 证书序列号
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 
	****************************************************************/
	void SetSerialNumber(const char *serialNumber);
	/****FUNCTION***************************************************
	*		 		 NAME : GetSerialNumber
	* DESCRIPTION : 获取证书序列号
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 证书序列号
	*    CAUTIONS : 
	****************************************************************/
	const char *GetSerialNumber(void) const;
	/****FUNCTION***************************************************
	*		 		 NAME : SetCertificate
	* DESCRIPTION : 设置证书内容
	*       INPUT : certificate - 证书内容
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 
	****************************************************************/
	void SetCertificate(const char *certificate);
	/****FUNCTION***************************************************
	*		 		 NAME : GetCertificate
	* DESCRIPTION : 获取证书内容
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 证书内容
	*    CAUTIONS : 
	****************************************************************/
	const char *GetCertificate(void) const;
private:
	char * strIssuerName;
	//颁发者标识
	char * strSerialNumber;
	//证书序列号
	char * strCertificate;
	//证书内容
};
////日志证书链类
class CDciLogCertChain
{
public:
	CDciLogCertChain(void);
	~CDciLogCertChain(void);
	/****FUNCTION***************************************************
	*		 		 NAME : GetCount
	* DESCRIPTION : 获取证书数量
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 证书数量
	*    CAUTIONS : 
	****************************************************************/
	unsigned int GetCount(void) const;
	/****FUNCTION***************************************************
	*		 		 NAME : GetCert
	* DESCRIPTION : 获取指定证书
	*       INPUT : index - 证书索引
	*      OUTPUT : 无
	*     RETURNS : 证书指针, NULL表示证书不存在
	*    CAUTIONS : 
	****************************************************************/
	CDciLogCertInfo * GetCert(unsigned int index);
	/****FUNCTION***************************************************
	*		 		 NAME : AddCert
	* DESCRIPTION : 添加证书
	*       INPUT : pCert - 证书
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 
	****************************************************************/
	void AddCert(CDciLogCertInfo &pCert);
private:
	CDciLogCertInfo **m_CertList;
	//证书列表
	unsigned int	m_Size;
	//证书数量
	unsigned int	m_MaxSize;
};
//日志链类
class CDciLogRecordSequence
{
public:
	CDciLogRecordSequence( int count = 0, char *outfile = NULL, bool isAddSignature = false, const CDciLogCertInfo *pDeviceCert = NULL, CDciLogCertChain *deviceCertChain = NULL, void *evpPriKey = NULL, const char *signMethod = "RSA-SHA-256");
	~CDciLogRecordSequence(void);
	/****FUNCTION***************************************************
	*		 		 NAME : AddRecord
	* DESCRIPTION : 添加日志节点
	*       INPUT : pLogRecord - 日志
	*      OUTPUT : 无
	*     RETURNS : true - 添加成功, false - 添加失败
	*    CAUTIONS : 
	****************************************************************/
	bool AddRecord(CDciLogRecord *pLogRecord);
	/****FUNCTION***************************************************
	*		 		 NAME : GetXmlString
	* DESCRIPTION : 生成日志链XML字符串
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : XML串
	*    CAUTIONS : 
	****************************************************************/
	const char * GetXmlString();
private:
	CDciLogRecord **m_pRecordList;
	//日志列表
	unsigned int	m_Size;
	//日志数量
	unsigned int	m_MaxSize;
	char			*m_XmlString;
	//XML串缓冲区
	bool			m_IsSign;
	//签名标记
	CDciLogCertInfo		*m_DeviceCert;
	//签名证书
	CDciLogCertChain	*m_DeviceCertChain;
	//签名证书链
	void			*m_PriKey;
	//签名私钥
	unsigned int	m_signMethod;
	//签名算法
//tangquanfa add start
	char	prevHeaderStr[1000];
	int		m_count;
	FILE	*m_fp;
//tangquanfa add end
};
#endif
