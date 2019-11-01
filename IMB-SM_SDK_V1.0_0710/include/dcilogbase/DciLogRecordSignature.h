/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* �ļ����ƣ�DciLogRecordSignature.h
* ժ    Ҫ����ȫ��־���ɻ������,��־Signature�ӿ���
* ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
*/
#ifndef DCI_LOG_RECORD_SIGNATURE_H
#define DCI_LOG_RECORD_SIGNATURE_H
#include "dcilogbase/DsigSignature.h"
//CDciLogRecordHeader���ӿ��࣬����ʵ����μ�ʵ����CConcreteRecordheader
class CDciLogRecordSignature
{
public:
	/****FUNCTION***************************************************
	*		 NAME : GetXmlString
	* DESCRIPTION : ����XML��ʽHeader�ַ���
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾHeader��ʽ����ȷ
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetXmlString() = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetAuthData
	* DESCRIPTION : ����AuthData�ڵ��ַ���
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾ��ʽ����ȷ����Authdata�ڵ㲻����
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetAuthData(void) = 0;
	typedef enum{Start, Stop}HeaderPlacement;
	/****FUNCTION***************************************************
	*		 NAME : SetHeaderPlacement
	* DESCRIPTION : ����HeaderPlacement �ڵ�
	*       INPUT : headerPlacement ȡֵ��ΧStart Stop
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾ��ʽ����ȷ����Authdata�ڵ㲻����
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetHeaderPlacement(HeaderPlacement headerPlacement) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetSequenceLength
	* DESCRIPTION : ����SequenceLength �ڵ�
	*       INPUT : iSequenceLength 
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾ��ʽ����ȷ����Authdata�ڵ㲻����
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetSequenceLength(int iSequenceLength) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetRecordAuthData
	* DESCRIPTION : RecordAuthData �ڵ�
	*       INPUT : strHeaderHash
	*								strAuthDataID
	*								strX509IssuerName
	*								strX509SerialNumber
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾ��ʽ����ȷ����Authdata�ڵ㲻����
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool SetRecordAuthData(const char *strHeaderHash, const char *strAuthDataID, const char *strX509IssuerName, const char *strX509SerialNumber) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetDsigSignature
	* DESCRIPTION : ����DsigSignature
	*				INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : DsigSignature����
	*    CAUTIONS : 
	****************************************************************/
	virtual	CDsigSignature * GetDsigSignature(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : Validate
	* DESCRIPTION : ��֤Signature��ʽ�Ƿ���ȷ
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true ��ʽ��ȷ��false ��ʽ����ȷ
	*    CAUTIONS : 
	****************************************************************/
	virtual bool Validate(void) = 0;
	virtual ~CDciLogRecordSignature(){};
};
#endif
