/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogOperations.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-11-14
Version    £º v1.0
Description£ºDCI Security Log class definition on Operations event   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_OPERATIONS_H
#define DCI_LOG_OPERATIONS_H

#include "dcilogs/DciLogClsSecurity.h"

enum OperationsEventSubType
{
	OPERATIONS_UNKNOWN = CDciLogClsSecurity::SEC_OPERATIONS + 1, //SEC_OPERATIONS + 1 is a base number 
															 //of OperationsEventSubType.
	SPB_OPEN,
	SPB_CLOSE,
	SPB_MARRIAGE,
	SPB_DIVORCE,
	SPB_SHUTDOWN,
	SPB_STARTUP,
	SPB_CLOCK_ADJUST,
	SPB_SOFTWARE,
	SPB_SECURITY_ALERT
};

class CDciLogOperations :
	public CDciLogClsSecurity
{
public:
	CDciLogOperations(OperationsEventSubType eEvtSubType = OPERATIONS_UNKNOWN);
	virtual ~CDciLogOperations();

	/****FUNCTION***************************************************
	*		 NAME : Validate
	* DESCRIPTION : validate log parameter 
	*       INPUT : null
	*      OUTPUT : null
	*     RETURNS : success return DCI_LOG_SUCCESS, fail return error number
	*    CAUTIONS : 
	****************************************************************/
	virtual int Validate(void);

	/****FUNCTION***************************************************
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
	****************************************************************/
	virtual bool AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, \
										const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL);

private:
	OperationsEventSubType m_eEvtSubType;

	bool m_IsAuthIdSet;	// Is't Author ID set successfully
	bool m_IsTimeOffsetSet;	// Is't Time Off set successfully
	bool m_IsDeviceConnectedIdSet;	// Is't Device connected id set successfully
	bool m_IsSignerIdSet;  // Is't Signer ID set successfully
	bool m_IsSoftwareVersionSet;	// Is't Software Version set successfully
};

#endif
