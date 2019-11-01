/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogValidationFilter.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-07-12
Version    £ºv1.0
Description£ºa definition on the class CValidationFilter  
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_VALIDATION_FILTER_H
#define DCI_LOG_VALIDATION_FILTER_H

enum ValFilterID
{
	NO_FLT = 0,
	FLT_1,
	FLT_2,
	FLT_3,
	//
	MAX_FLT_NUMS,
};

struct ValFilterDesc
{
	ValFilterID eFltIndex;
	const char* pFltDesc;
};

static ValFilterDesc g_ValFltDescTable[MAX_FLT_NUMS] = \
{
	{NO_FLT, "No filter supported"},
	{FLT_1, "Validation filter1 ver1.0"},
	{FLT_2, "Validation filter2 ver1.0"},
	{FLT_3, "Validation filter3 ver1.0"}
};

class CValidationFilter;
class CXmlDocument;

typedef bool (CValidationFilter::*fnValidationFilter)(CXmlNode *);

struct ValFilter
{
	ValFilterID eFltIndex;	
	fnValidationFilter pFilter;	
};

//the class to implement all validation filters specified by FilterID
class CValidationFilter
{
	CValidationFilter(CXmlDocument	*pXmlDoc);
public:
	virtual ~CValidationFilter(void);

	/****FUNCTION***************************************************************
	 *		  NAME : Filter1
	 * DESCRIPTION : Validation Filter func1.
	 *       INPUT : CXmlNode* - the current node.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool Filter1(CXmlNode * pCurrentNode);

	/****FUNCTION***************************************************************
	 *		  NAME : Filter2
	 * DESCRIPTION : Validation Filter func2.
	 *       INPUT : CXmlNode* - the current node.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool Filter2(CXmlNode * pCurrentNode);

	/****FUNCTION***************************************************************
	 *		  NAME : Filter3
	 * DESCRIPTION : Validation Filter func3.
	 *       INPUT : CXmlNode* - the current node.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool Filter3(CXmlNode * pCurrentNode);

	/****FUNCTION***************************************************************
	 *		  NAME : Release
	 * DESCRIPTION : release filter, while reference is 0.
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void Release();

	/****FUNCTION***************************************************************
	 *		  NAME : GetValFltDesc
	 * DESCRIPTION : obtains a description on validation filter specified by ValFilterID.
	 *       INPUT : ValFilterID - a unique ID of the validation filter.
	 *      OUTPUT : none
	 *     RETURNS : const char* - a filter description.
	 *    CAUTIONS : 
	 ****************************************************************************/
	const char* GetValFltDesc(ValFilterID eValFltID) const;

	/****FUNCTION***************************************************************
	 *		  NAME : GetValFilter
	 * DESCRIPTION : obtains the validation filter specified by ValFilterID.
	 *       INPUT : ValFilterID - a unique ID of the validation filter.
	 *      OUTPUT : none
	 *     RETURNS : fnValidationFilter - a pointer o the filter function.
	 *    CAUTIONS : 
	 ****************************************************************************/
	fnValidationFilter GetValFilter(ValFilterID eValFltID) const;

	/****FUNCTION***************************************************************
	 *		  NAME : RegisterFilters
	 * DESCRIPTION : register all validation filters
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	static void RegisterFilters();

	/****FUNCTION***************************************************************
	 *		  NAME : UnRegisterFilters
	 * DESCRIPTION : unregister all validation filters
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	static void UnRegisterFilters();

	/****FUNCTION***************************************************************
	 *		  NAME : UnRegisterFilters
	 * DESCRIPTION : unregister all validation filters
	 *       INPUT : CXmlDocument - a pointer to the obj instance:CXmlDocument
	 *      OUTPUT : none
	 *     RETURNS : CValidationFilter - a instance of validation filter
	 *    CAUTIONS : 
	 ****************************************************************************/
	static CValidationFilter* GetInstance(CXmlDocument* pXmlDoc);

public:
	static ValFilter g_ValFilterSet[MAX_FLT_NUMS];
	static CValidationFilter* m_pValFilter;
	static unsigned int m_nRefNums;

private:
	CXmlNode		*m_pRootNode;
	CXmlDocument	*m_pXmlDoc;
};
#endif
