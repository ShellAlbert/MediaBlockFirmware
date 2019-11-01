/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* �ļ����ƣ�DciLogRecordHeader.h
* ժ    Ҫ����ȫ��־���ɻ������,��־Header�ӿ���
* ��ǰ�汾��1.0
* ��    �ߣ���ɽ
* ȡ���汾����
*/
#ifndef DCI_LOG_RECORD_HEADER_H
#define DCI_LOG_RECORD_HEADER_H

//CDciLogRecordHeader���ӿ��࣬����ʵ����μ�ʵ����CConcreteRecordheader

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
	* DESCRIPTION : ����EVENT ID
	*       INPUT : strEventID - ID�ַ���
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventID(const char * strEventID) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetTimeStamp
	* DESCRIPTION : ����ʱ���
	*       INPUT : strTimeStamp - ʱ����ַ���
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetTimeStamp(const char *strTimeStamp) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetTimeStamp
	* DESCRIPTION : ����ʱ���
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ʱ����ַ�����NULL ��ʾʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	const char *	GetTimeStamp(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetEventSequence
	* DESCRIPTION : �������
	*       INPUT : strEventSequence - ����ַ���
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetEventSequence(const char *strEventSequence) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetPrimaryDeviceSourceID
	* DESCRIPTION : ����������ԴID
	*       INPUT : strDeviceSourceID -		�豸ID
	*				strDeviceSourceIDType - �豸����
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetPrimaryDeviceSourceID(const char *strDeviceSourceID, const char * strDeviceSourceIDType) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetSecondaryDeviceSourceID
	* DESCRIPTION : ���ô�����ԴID
	*       INPUT : strDeviceSourceID -		�豸ID
	*				strDeviceSourceIDType - �豸����
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetSecondaryDeviceSourceID(const char *strDeviceSourceID, const char * strDeviceSourceIDType) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetEventType
	* DESCRIPTION : ���ð�ȫ�¼�����
	*       INPUT : strEventType -	�¼�����
	*				strEventScope - ȡֵ��Χ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetEventType(const char *strEventType, const char *strEventScope) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetContentID
	* DESCRIPTION : ��������ID
	*       INPUT : strContentID -	����ID
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
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
	* DESCRIPTION : ����ǰһ�ڵ�ͷժҪ
	*       INPUT : strHash -	ժҪֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetPreviousHeaderHash(const char *strHash) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetPreviousHeaderHash
	* DESCRIPTION : ����ǰһ�ڵ�ͷժҪ
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ժҪ�ַ���,NULL ��ʾ�޴˽ڵ���߻�ȡժҪֵʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual const char *	GetPreviousHeaderHash(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : SetRecordBodyHash
	* DESCRIPTION : ������־BODYժҪ
	*       INPUT : strHash -	ժҪֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetRecordBodyHash(const char *strHash) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetRecordBodyHash
	* DESCRIPTION : ������־BODYժҪ
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ժҪ�ַ���,NULL ��ʾ�޴˽ڵ���߻�ȡժҪֵʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual const char *	GetRecordBodyHash(void) = 0;
	/****FUNCTION***************************************************
	*		 NAME : GetXmlString
	* DESCRIPTION : ����XML��ʽHeader�ַ���
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : NULL��ʾHeader��ʽ����ȷ
	*    CAUTIONS : 
	****************************************************************/
	virtual const char * GetXmlString() = 0;
	/****FUNCTION***************************************************
	*		 NAME : Validate
	* DESCRIPTION : ��֤Header��ʽ�Ƿ���ȷ
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true ��ʽ��ȷ��false ��ʽ����ȷ
	*    CAUTIONS : 
	****************************************************************/
	virtual bool Validate(void) = 0;

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	virtual CDciLogRecordHeader::LogOutputMode GetOutputMode() const = 0;
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	virtual ~CDciLogRecordHeader(){};
};

#endif
