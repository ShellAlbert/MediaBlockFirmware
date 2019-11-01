/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：DciLogRecordBody.h
* 摘    要：安全日志生成基础类库,日志Body接口类
* * 当前版本：1.0
* 作    者：马静山
** 取代版本：无
*/
#ifndef DCI_LOG_RECORD_BODY_H
#define DCI_LOG_RECORD_BODY_H
//#define	NULL 0
#include "dcilogbase/DciDeviceDescription.h"
/*
*	CDciLogRecordHeader　接口类，具体实现请参见实体类CConcreteRecordbody
*/
class CDciLogRecordBody
{
public:
	/****FUNCTION***************************************************
	*		 		NAME : SetEventID
	* DESCRIPTION : 设置EVENT ID
	*       INPUT : strEventID - ID字符串
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventID(const char * strEventID) = 0;

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	/****FUNCTION***************************************************
	*		 NAME : SetEventType
	* DESCRIPTION : 设置安全事件类型
	*       INPUT : strEventType -	事件类型
	*				strEventScope - 取值范围
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetEventType(const char *strEventType, const char *strEventScope) = 0;
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	/****FUNCTION***************************************************
	*		 NAME : SetEventSubType
	* DESCRIPTION : 设置EVENT SubType
	*       INPUT : strType 	- Type字符串
	*								strScope 	- SubType取值范围
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetEventSubType(const char *strType, const char *strScope) = 0;
	/****FUNCTION***************************************************
	*		 NAME : AddParameter
	* DESCRIPTION : 添加一个PARAMETER
	*       INPUT : strName 					- Parameter名称
	*								strValue 					- Parameter值
	*								strNameScope 			- Parameter名称取值范围
	*								strValueAttrName	- Parameter属性名
	*								strValueAttrVal		- Parameter属性值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL) = 0;
	/****FUNCTION***************************************************
	*		 NAME : AddException
	* DESCRIPTION : 添加一个Exception
	*       INPUT : strName 					- Exception名称
	*								strValue 					- Exception值
	*								strNameScope 			- Exception名称取值范围
	*								strValueAttrName	- Exception属性名
	*								strValueAttrVal		- Exception属性值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddException(const char *strName, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL) = 0;
	/****FUNCTION***************************************************
	*		 NAME : AddReferencedID
	* DESCRIPTION : 添加一个AddReferencedID
	*       INPUT : strName 					- AddReferencedID名称
	*								strValue 					- AddReferencedID值
	*								strNameScope 			- AddReferencedID名称取值范围
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddReferencedID(const char *strName, const char *strValue, const char *strNameScope = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : SetExtensionID
	* DESCRIPTION : 设置SetExtensionID
	*       INPUT : strID - ID字符串
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetRecordExtensionID(const char * strID) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : SetRecordTextExtension
	* DESCRIPTION : 设置SetRecordTextExtension
	*       INPUT : strTextID - ID字符串
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetRecordTextExtension(const char *strTextID, const char *strDescription, const char *strDescriptionLanguage = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : GetDciDeviceDescription
	* DESCRIPTION : 获取当设备描述
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual CDciDeviceDescription * GetDciDeviceDescription(void) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : GetXmlString
	* DESCRIPTION : 生成XML串
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : NULL 表示BODY节点无效
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetXmlString() = 0;
	/****FUNCTION***************************************************
	*		 		NAME : Validate
	* DESCRIPTION : 验证BODY节点有效性
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 节点有效，false 节点无效
	*    CAUTIONS : 
	****************************************************************/
	virtual bool Validate(void) = 0;

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	virtual CDciLogRecordHeader::LogOutputMode GetOutputMode() const = 0;
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	virtual ~CDciLogRecordBody(){};
};

#endif
