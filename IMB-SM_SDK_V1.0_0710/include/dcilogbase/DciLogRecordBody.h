/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DciLogRecordBody.h
* ժ    Ҫ����ȫ��־���ɻ������,��־Body�ӿ���
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
** ȡ���汾����
*/
#ifndef DCI_LOG_RECORD_BODY_H
#define DCI_LOG_RECORD_BODY_H
//#define	NULL 0
#include "dcilogbase/DciDeviceDescription.h"
/*
*	CDciLogRecordHeader���ӿ��࣬����ʵ����μ�ʵ����CConcreteRecordbody
*/
class CDciLogRecordBody
{
public:
	/****FUNCTION***************************************************
	*		 		NAME : SetEventID
	* DESCRIPTION : ����EVENT ID
	*       INPUT : strEventID - ID�ַ���
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventID(const char * strEventID) = 0;

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	/****FUNCTION***************************************************
	*		 NAME : SetEventType
	* DESCRIPTION : ���ð�ȫ�¼�����
	*       INPUT : strEventType -	�¼�����
	*				strEventScope - ȡֵ��Χ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetEventType(const char *strEventType, const char *strEventScope) = 0;
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	/****FUNCTION***************************************************
	*		 NAME : SetEventSubType
	* DESCRIPTION : ����EVENT SubType
	*       INPUT : strType 	- Type�ַ���
	*								strScope 	- SubTypeȡֵ��Χ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetEventSubType(const char *strType, const char *strScope) = 0;
	/****FUNCTION***************************************************
	*		 NAME : AddParameter
	* DESCRIPTION : ���һ��PARAMETER
	*       INPUT : strName 					- Parameter����
	*								strValue 					- Parameterֵ
	*								strNameScope 			- Parameter����ȡֵ��Χ
	*								strValueAttrName	- Parameter������
	*								strValueAttrVal		- Parameter����ֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL) = 0;
	/****FUNCTION***************************************************
	*		 NAME : AddException
	* DESCRIPTION : ���һ��Exception
	*       INPUT : strName 					- Exception����
	*								strValue 					- Exceptionֵ
	*								strNameScope 			- Exception����ȡֵ��Χ
	*								strValueAttrName	- Exception������
	*								strValueAttrVal		- Exception����ֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddException(const char *strName, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL) = 0;
	/****FUNCTION***************************************************
	*		 NAME : AddReferencedID
	* DESCRIPTION : ���һ��AddReferencedID
	*       INPUT : strName 					- AddReferencedID����
	*								strValue 					- AddReferencedIDֵ
	*								strNameScope 			- AddReferencedID����ȡֵ��Χ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddReferencedID(const char *strName, const char *strValue, const char *strNameScope = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : SetExtensionID
	* DESCRIPTION : ����SetExtensionID
	*       INPUT : strID - ID�ַ���
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetRecordExtensionID(const char * strID) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : SetRecordTextExtension
	* DESCRIPTION : ����SetRecordTextExtension
	*       INPUT : strTextID - ID�ַ���
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetRecordTextExtension(const char *strTextID, const char *strDescription, const char *strDescriptionLanguage = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : GetDciDeviceDescription
	* DESCRIPTION : ��ȡ���豸����
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual CDciDeviceDescription * GetDciDeviceDescription(void) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : GetXmlString
	* DESCRIPTION : ����XML��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : NULL ��ʾBODY�ڵ���Ч
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetXmlString() = 0;
	/****FUNCTION***************************************************
	*		 		NAME : Validate
	* DESCRIPTION : ��֤BODY�ڵ���Ч��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true �ڵ���Ч��false �ڵ���Ч
	*    CAUTIONS : 
	****************************************************************/
	virtual bool Validate(void) = 0;

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	virtual CDciLogRecordHeader::LogOutputMode GetOutputMode() const = 0;
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	virtual ~CDciLogRecordBody(){};
};

#endif
