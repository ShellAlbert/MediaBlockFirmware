/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：DciDeviceDescription.h
* 摘    要：安全日志生成基础类库,设备描述接口类
* * 当前版本：1.0
* 作    者：马静山
** 取代版本：无
*/
#ifndef DCI_DEVICE_DESCRIPTION_H
#define DCI_DEVICE_DESCRIPTION_H
#define NULL 0
//设备描述接口类，具体实现请参见实体类CConcreteDeviceDescription
class CDciDeviceDescription
{
public:
	typedef enum {CertThumbprint, DeviceUID} DeviceIdType;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceIdentifier
	* DESCRIPTION : 设置设备标识(ID)
	*       INPUT : idType - 设备类型(取值范围:CertThumbprint, DeviceUID)
	*								strID - 设备ID
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceIdentifier(DeviceIdType idType, const char *strID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceTypeID
	* DESCRIPTION : 设置设备类型ID
	*       INPUT : strType - 类型ID
	*								strScope - 取值范围
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceTypeID(const char *strType, const char *strScope = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceSerial
	* DESCRIPTION : 设置设备序列号
	*       INPUT : strSerial - 序列号
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetDeviceSerial(const char * strSerial) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : AddVersionInfo
	* DESCRIPTION : 添加版本信息
	*       INPUT : strVerName - 名
	*								strVerValue - 值
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddVersionInfo(const char *strVerName, const char *strVerValue) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceSubsystemTypeID
	* DESCRIPTION : 设置子系统类型
	*       INPUT : strType - 类型
	*								strScope - 取值范围
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceSubsystemTypeID(const char *strType, const char *strScope = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetAdditionalID
	* DESCRIPTION : 设置别名
	*       INPUT : strID - 别名
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetAdditionalID(const char *strID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetManufacturerID
	* DESCRIPTION : 设置生产厂商ID
	*       INPUT : strID - 厂商ID
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetManufacturerID(const char *strID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetManufacturerCertID
	* DESCRIPTION : 设置生产厂商证书ID
	*       INPUT : strCertID - 证书ID
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetManufacturerCertID(const char *strCertID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceCertID
	* DESCRIPTION : 设置设备证书ID
	*       INPUT : strCertID - 证书ID
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceCertID(const char *strCertID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetManufacturerName
	* DESCRIPTION : 设置生产厂商名称
	*       INPUT : strName - 厂商名称
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetManufacturerName(const char *strName) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceName
	* DESCRIPTION : 设置设备名称
	*       INPUT : strName - 设备名称
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceName(const char *strName) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetModelNumber
	* DESCRIPTION : 设置组件编号
	*       INPUT : strNumber - 组件编号
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetModelNumber(const char *strNumber) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceComment
	* DESCRIPTION : 设置设备注释
	*       INPUT : strComment - 注释内容
	*      OUTPUT : 无
	*     RETURNS : true 成功，false 失败
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceComment(const char *strComment) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : Validate
	* DESCRIPTION : 验证DciDeviceDescription节点有效性
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 节点有效，false 节点无效
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	Validate(void) = 0;
	virtual ~CDciDeviceDescription(){};
};

#endif
