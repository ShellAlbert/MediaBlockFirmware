/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* 文件名称：DciLogRecordSignature.h
* 摘    要：安全日志生成基础类库,日志Signature接口类
* 当前版本：1.0
* 作    者：马静山
* 取代版本：无
*/
#ifndef DCI_LOG_RECORD_SIGNATURE_H
#define DCI_LOG_RECORD_SIGNATURE_H
#include "dcilogbase/DsigSignature.h"
//CDciLogRecordHeader　接口类，具体实现请参见实体类CConcreteRecordheader
class CDciLogRecordSignature
{
public:
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
	*		 NAME : GetAuthData
	* DESCRIPTION : 返回AuthData节点字符串
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : NULL表示格式不正确或者Authdata节点不存在
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetAuthData(void) = 0;
	typedef enum{Start, Stop}HeaderPlacement;
	/****FUNCTION***************************************************
	*		 NAME : SetHeaderPlacement
	* DESCRIPTION : 设置HeaderPlacement 节点
	*       INPUT : headerPlacement 取值范围Start Stop
	*      OUTPUT : 无
	*     RETURNS : NULL表示格式不正确或者Authdata节点不存在
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetHeaderPlacement(HeaderPlacement headerPlacement) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetSequenceLength
	* DESCRIPTION : 设置SequenceLength 节点
	*       INPUT : iSequenceLength 
	*      OUTPUT : 无
	*     RETURNS : NULL表示格式不正确或者Authdata节点不存在
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetSequenceLength(int iSequenceLength) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetRecordAuthData
	* DESCRIPTION : RecordAuthData 节点
	*       INPUT : strHeaderHash
	*								strAuthDataID
	*								strX509IssuerName
	*								strX509SerialNumber
	*      OUTPUT : 无
	*     RETURNS : NULL表示格式不正确或者Authdata节点不存在
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool SetRecordAuthData(const char *strHeaderHash, const char *strAuthDataID, const char *strX509IssuerName, const char *strX509SerialNumber) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetDsigSignature
	* DESCRIPTION : 返回DsigSignature
	*				INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : DsigSignature对象
	*    CAUTIONS : 
	****************************************************************/
	virtual	CDsigSignature * GetDsigSignature(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : Validate
	* DESCRIPTION : 验证Signature格式是否正确
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : true 格式正确，false 格式不正确
	*    CAUTIONS : 
	****************************************************************/
	virtual bool Validate(void) = 0;
	virtual ~CDciLogRecordSignature(){};
};
#endif
