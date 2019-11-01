/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogKey.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-11-14
Version    £º v1.0
Description£ºDCI Security Log class definition on Key event   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_KEY_H
#define DCI_LOG_KEY_H

#include "dcilogs/DciLogClsSecurity.h"

enum KeyEventSubType
{
	KEY_UNKNOWN = CDciLogClsSecurity::SEC_KEY + 1, //SEC_KEY + 1 is a base number of KeyEventSubType.
	KDM_KEYS_RECEIVED,
	KDM_DELETED
};

class CDciLogKey :
	public CDciLogClsSecurity
{
public:
	CDciLogKey(KeyEventSubType eEvtSubType = KEY_UNKNOWN);
	virtual ~CDciLogKey();

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

	/****FUNCTION***************************************************
	*		 NAME : AddReferencedID
	* DESCRIPTION : Add Referenced ID to the Xml file
	*       INPUT : strName : Referenced ID name
	*               strValue : Referenced ID value
	*               strNameScope : Referenced ID name scope
	*      OUTPUT : null
	*     RETURNS : success return true, fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual bool AddReferencedID(const char *strName, const char *strValue, const char *strNameScope = NULL);

private:
	KeyEventSubType m_eEvtSubType;

	bool m_IsContentIdSet;				// Is Content ID Set:true
	bool m_IsKeyDeliveryMessageIdSet;	//	Is Key Delivery Message Id set:true
};

#endif
