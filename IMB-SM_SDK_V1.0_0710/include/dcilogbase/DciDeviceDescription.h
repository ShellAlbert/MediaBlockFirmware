/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�DciDeviceDescription.h
* ժ    Ҫ����ȫ��־���ɻ������,�豸�����ӿ���
* * ��ǰ�汾��1.0
* ��    �ߣ���ɽ
** ȡ���汾����
*/
#ifndef DCI_DEVICE_DESCRIPTION_H
#define DCI_DEVICE_DESCRIPTION_H
#define NULL 0
//�豸�����ӿ��࣬����ʵ����μ�ʵ����CConcreteDeviceDescription
class CDciDeviceDescription
{
public:
	typedef enum {CertThumbprint, DeviceUID} DeviceIdType;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceIdentifier
	* DESCRIPTION : �����豸��ʶ(ID)
	*       INPUT : idType - �豸����(ȡֵ��Χ:CertThumbprint, DeviceUID)
	*								strID - �豸ID
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceIdentifier(DeviceIdType idType, const char *strID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceTypeID
	* DESCRIPTION : �����豸����ID
	*       INPUT : strType - ����ID
	*								strScope - ȡֵ��Χ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceTypeID(const char *strType, const char *strScope = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceSerial
	* DESCRIPTION : �����豸���к�
	*       INPUT : strSerial - ���к�
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual	bool	SetDeviceSerial(const char * strSerial) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : AddVersionInfo
	* DESCRIPTION : ��Ӱ汾��Ϣ
	*       INPUT : strVerName - ��
	*								strVerValue - ֵ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	AddVersionInfo(const char *strVerName, const char *strVerValue) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceSubsystemTypeID
	* DESCRIPTION : ������ϵͳ����
	*       INPUT : strType - ����
	*								strScope - ȡֵ��Χ
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceSubsystemTypeID(const char *strType, const char *strScope = NULL) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetAdditionalID
	* DESCRIPTION : ���ñ���
	*       INPUT : strID - ����
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetAdditionalID(const char *strID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetManufacturerID
	* DESCRIPTION : ������������ID
	*       INPUT : strID - ����ID
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetManufacturerID(const char *strID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetManufacturerCertID
	* DESCRIPTION : ������������֤��ID
	*       INPUT : strCertID - ֤��ID
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetManufacturerCertID(const char *strCertID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceCertID
	* DESCRIPTION : �����豸֤��ID
	*       INPUT : strCertID - ֤��ID
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceCertID(const char *strCertID) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetManufacturerName
	* DESCRIPTION : ����������������
	*       INPUT : strName - ��������
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetManufacturerName(const char *strName) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceName
	* DESCRIPTION : �����豸����
	*       INPUT : strName - �豸����
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceName(const char *strName) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetModelNumber
	* DESCRIPTION : ����������
	*       INPUT : strNumber - ������
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetModelNumber(const char *strNumber) = 0;
	/****FUNCTION***************************************************
	*		 		 NAME : SetDeviceComment
	* DESCRIPTION : �����豸ע��
	*       INPUT : strComment - ע������
	*      OUTPUT : ��
	*     RETURNS : true �ɹ���false ʧ��
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	SetDeviceComment(const char *strComment) = 0;
	/****FUNCTION***************************************************
	*		 		NAME : Validate
	* DESCRIPTION : ��֤DciDeviceDescription�ڵ���Ч��
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : true �ڵ���Ч��false �ڵ���Ч
	*    CAUTIONS : 
	****************************************************************/
	virtual bool	Validate(void) = 0;
	virtual ~CDciDeviceDescription(){};
};

#endif
