/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogPlayout.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-11-14
Version    £ºv1.0
Description£ºDCI Security Log class definition on Playout event   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_PLAYOUT_H
#define DCI_LOG_PLAYOUT_H

#include "dcilogs/DciLogClsSecurity.h"

enum PlayoutEventSubType
{
	PLAYOUT_UNKNOWN = CDciLogClsSecurity::SEC_PLAYOUT + 1, //SEC_PLAYOUT + 1 is a base number of PlayoutEventSubType.
	FRAME_SEQUENCE_PLAYED,
	CPL_START,
	CPL_END,
	PLAYOUT_COMPLETE
};

class CDciLogPlayout :
	public CDciLogClsSecurity
{
public:
	CDciLogPlayout(PlayoutEventSubType eEvtSubType = PLAYOUT_UNKNOWN);
	virtual ~CDciLogPlayout();

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
	virtual bool AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL);
	
	/****FUNCTION***************************************************
	*		 NAME : AddReferencedID
	* DESCRIPTION : Add ReferencedID to the Xml file
	*       INPUT : strName : Referenced ID name
	*               strValue : Referenced ID value
	*               strNameScope : Referenced ID name scope
	*      OUTPUT : null
	*     RETURNS : success return true, fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual bool AddReferencedID(const char *strName, const char *strValue, const char *strNameScope = NULL);

private:
	PlayoutEventSubType m_eEvtSubType;

	bool m_IsContentIdSet;	// Content Id set successfully
	bool m_IsAuthIdSet;		// Author Id set successfully
	bool m_IsFirstFrameSet;	// First Frame set successfully
	bool m_IsLastFrameSet;	// Last Frame set successfully
	bool m_IsTrackFileIdSet;// Track File Id set successfully
	bool m_IsKeyDeliveryMessageIdSet;	// Key Delivery Message Id set successfully

};

#endif
