/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogValidation.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-11-14
Version    £ºv1.0
Description£ºDCI Security Log class definition on Validation event   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_VALIDATION_H
#define DCI_LOG_VALIDATION_H

#include "dcilogs/DciLogClsSecurity.h"

enum ValidationEventSubType
{
	VALIDATION_UNKNOWN = CDciLogClsSecurity::SEC_VALIDATION + 1, //SEC_VALIDATION + 1 is a base number of ValidationEventSubType.
	CPL_CHECK
};

class CDciLogValidation :
	public CDciLogClsSecurity
{
public:
	CDciLogValidation(ValidationEventSubType eEvtSubType = VALIDATION_UNKNOWN);
	virtual ~CDciLogValidation();


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
	*		 NAME : SetContentID
	* DESCRIPTION : Set Content ID
	*       INPUT : strContentID : Content ID
	*      OUTPUT : null
	*     RETURNS : success return true, fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetContentID(const char *strContentID);

private:
	ValidationEventSubType m_eEvtSubType;

	bool m_IsContentIdSet;	// Content Id set successfully
};

#endif
