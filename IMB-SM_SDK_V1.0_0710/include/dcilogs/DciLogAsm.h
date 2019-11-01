/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DciLogAsm.h
* ժ    Ҫ��DCI Security Log 
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
*/
#ifndef DCI_LOG_ASM_H
#define DCI_LOG_ASM_H

//[DC_security_terminal] modified by chenjingdong, 2013-03-09 start 
/* #include "dcilogs/DciLog.h"
class CDciLogAsm : public CDciLog */

#include "dcilogs/DciLogClsSecurity.h"

enum AsmEventSubType
{
	ASM_UNKNOWN = CDciLogClsSecurity::SEC_ASM + 1, //SEC_ASM + 1 is a base number of AsmEventSubType.
	LINK_OPENED,
	LINK_CLOSED,
	LINK_EXCEPTION,
	LOG_TRANSFER,
	KEY_TRANSFER
};

class CDciLogAsm :
	public CDciLogClsSecurity
//[DC_security_terminal] end
{
public:
	//[DC_security_terminal] modified by chenjingdong, 2013-11-14 start
	/* CDciLogAsm(void); */

	CDciLogAsm(AsmEventSubType eEvtSubType = ASM_UNKNOWN);
	virtual ~CDciLogAsm();

	/****FUNCTION***************************************************************
	*		 NAME : Validate
	* DESCRIPTION : validate log parameter 
	*       INPUT : null
	*      OUTPUT : null
	*     RETURNS : success return DCI_LOG_SUCCESS, fail return error number
	*    CAUTIONS : 
	****************************************************************************/
	virtual int Validate(void);
	
	/****FUNCTION***************************************************************
	*		 NAME : AddParameter
	* DESCRIPTION : Add Parameter to the Xml file
	*       INPUT : strName : Parameter name
	*               strValue : Parameter value
	*               strNameScope : Parameter name scope
	*               strValueAttrName : Parameter value attribute name
	*               strValueAttrVal : Parameter value attribute value
	*      OUTPUT : null
	*     RETURNS : success return true, fail return false
	*    CAUTIONS : 
	****************************************************************************/
	virtual bool AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, \
										const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL);

private:
	AsmEventSubType m_eEvtSubType;
	bool m_bIsParamAdded; //true : add all valid parameters successfully.
	//[DC_security_terminal] end
};

#endif
