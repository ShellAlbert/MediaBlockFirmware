/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：DsigSignature.h
* 摘    要：安全日志生成基础类库,数字签名接口类
* * 当前版本：1.0
* 作    者：马静山
* 取代版本：无
*/
#ifndef DSIG_SIGNATURE_H
#define DSIG_SIGNATURE_H
class CDsigSignature
{
public:
	/****FUNCTION***************************************************
	*		 		 NAME : SetSignedInfo
	* DESCRIPTION : 设置签名信息
	*       INPUT : canonicalizationMethod - XML格式标准
	*								signatureMethod - 签名算法
	*								referenceURI - 签名节点标识
	*								digestMethod - 摘要算法
	*								digestValue - 摘要值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetSignedInfo(const char *canonicalizationMethod, const char *signatureMethod, const char *referenceURI, const char *digestMethod, const char *digestValue) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetSignatureValue
	* DESCRIPTION : 设置签名值
	*       INPUT : signatureValue - 签名值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetSignatureValue(const char *signatureValue) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : AddCertificate
	* DESCRIPTION : 添加证书
	*       INPUT : strX509IssuerName - 证书颁发者标识
	*								strX509SerialNumber - 证书序列号
	*								strX509Certificate - 证书内容
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool AddCertificate(const char *strX509IssuerName, const char *strX509SerialNumber, const char *strX509Certificate) = 0;
	virtual ~CDsigSignature(){};
};
#endif
