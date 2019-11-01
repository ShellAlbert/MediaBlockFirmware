/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* 文件名称：DciLogRecordHeader.h
* 摘    要：安全日志生成基础类库,日志Header接口类
* 当前版本：1.0
* 作    者：马静山
* 取代版本：无
*/
#ifndef DCI_LOG_RECORD_HEADER_H
#define DCI_LOG_RECORD_HEADER_H

//CDciLogRecordHeader　接口类，具体实现请参见实体类CConcreteRecordheader

class CDciLogRecordHeader
{
public:
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	enum LogOutputMode
	{
		DCI_LOG_NORMAL,
		DCI_LOG_COMPACT	//to generate more smaller log record.
	};
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	/****FUNCTION***************************************************
	*		 NAME : SetEventID
	* DESCRIPTION : 设置EVENT ID
	*       INPUT : strEventID - ID字符串
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventID(const char * strEventID) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetTimeStamp
	* DESCRIPTION : 设置时间戳
	*       INPUT : strTimeStamp - 时间戳字符串
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetTimeStamp(const char *strTimeStamp) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetTimeStamp
	* DESCRIPTION : 返回时间戳
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 时间戳字符串，NULL 表示失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	const char *	GetTimeStamp(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetEventSequence
	* DESCRIPTION : 设置序号
	*       INPUT : strEventSequence - 序号字符串
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventSequence(const char *strEventSequence) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetPrimaryDeviceSourceID
	* DESCRIPTION : 设置主设置源ID
	*       INPUT : strDeviceSourceID -		设备ID
	*				strDeviceSourceIDType - 设备类型
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetPrimaryDeviceSourceID(const char *strDeviceSourceID, const char * strDeviceSourceIDType) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetSecondaryDeviceSourceID
	* DESCRIPTION : 设置从设置源ID
	*       INPUT : strDeviceSourceID -		设备ID
	*				strDeviceSourceIDType - 设备类型
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetSecondaryDeviceSourceID(const char *strDeviceSourceID, const char * strDeviceSourceIDType) = 0;
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
	/****FUNCTION***************************************************
	*		 NAME : SetContentID
	* DESCRIPTION : 设置内容ID
	*       INPUT : strContentID -	内容ID
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/

	//[SecTermSM_v1.0_DCEventLog] added by chenjingdong, 2013-03-15 start 
	/****FUNCTION***************************************************
	*		 NAME : SetEventClass
	* DESCRIPTION : Set event class in the record header.
	*       INPUT : strEvtCls - it is a URI string to specify event class. 
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventClass(const char *strEvtCls) = 0;
	//[SecTermSM_v1.0_DCEventLog] end

	virtual bool	SetContentID(const char *strContentID) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetPreviousHeaderHash
	* DESCRIPTION : 设置前一节点头摘要
	*       INPUT : strHash -	摘要值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetPreviousHeaderHash(const char *strHash) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetPreviousHeaderHash
	* DESCRIPTION : 设置前一节点头摘要
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 摘要字符串,NULL 表示无此节点或者获取摘要值失败
	*    CAUTIONS : 
	****************************************************************/
	virtual const char *	GetPreviousHeaderHash(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetRecordBodyHash
	* DESCRIPTION : 设置日志BODY摘要
	*       INPUT : strHash -	摘要值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetRecordBodyHash(const char *strHash) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetRecordBodyHash
	* DESCRIPTION : 设置日志BODY摘要
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 摘要字符串,NULL 表示无此节点或者获取摘要值失败
	*    CAUTIONS : 
	****************************************************************/
	virtual const char *	GetRecordBodyHash(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetXmlString
	* DESCRIPTION : 返回XML格式Header字符串
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : NULL表示Header格式不正确
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetXmlString() = 0;
	/****FUNCTION***************************************************
	*		 NAME : Validate
	* DESCRIPTION : 验证Header格式是否正确
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 格式正确，false 格式不正确
	*    CAUTIONS : 
	****************************************************************/
	virtual bool Validate(void) = 0;

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	virtual CDciLogRecordHeader::LogOutputMode GetOutputMode() const = 0;
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	virtual ~CDciLogRecordHeader(){};
};

#endif
