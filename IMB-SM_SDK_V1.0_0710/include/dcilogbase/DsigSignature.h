/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DsigSignature.h
* ժ    Ҫ����ȫ��־���ɻ������,����ǩ���ӿ���
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
*/
#ifndef DSIG_SIGNATURE_H
#define DSIG_SIGNATURE_H
class CDsigSignature
{
public:
	/****FUNCTION***************************************************
	*		 		 NAME : SetSignedInfo
	* DESCRIPTION : ����ǩ����Ϣ
	*       INPUT : canonicalizationMethod - XML��ʽ��׼
	*								signatureMethod - ǩ���㷨
	*								referenceURI - ǩ���ڵ��ʶ
	*								digestMethod - ժҪ�㷨
	*								digestValue - ժҪֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetSignedInfo(const char *canonicalizationMethod, const char *signatureMethod, const char *referenceURI, const char *digestMethod, const char *digestValue) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetSignatureValue
	* DESCRIPTION : ����ǩ��ֵ
	*       INPUT : signatureValue - ǩ��ֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetSignatureValue(const char *signatureValue) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : AddCertificate
	* DESCRIPTION : ���֤��
	*       INPUT : strX509IssuerName - ֤��䷢�߱�ʶ
	*								strX509SerialNumber - ֤�����к�
	*								strX509Certificate - ֤������
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool AddCertificate(const char *strX509IssuerName, const char *strX509SerialNumber, const char *strX509Certificate) = 0;
	virtual ~CDsigSignature(){};
};
#endif
