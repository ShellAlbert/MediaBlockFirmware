/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName  : IMB-SM SDK
FileName    £ºmvc2api_securitymanager.cpp
Author      : chenjingdong@oristartech.com
Date        : 2014-06-30
Version     : v1.0
Description : implementation of classes : UuidValue and SecurityManager.   
Others      : 
History     : 

< Author >    			< Date >             < Modification >

****************************************************************************/
#include "imbsdk/mvc2api_securitymanager.h"
#include "imbsdk/private/SecurityManagerPrivate.h" 

namespace mvc2
{

	//UuidValue implementation
	UuidValue::UuidValue(const uint8_t *key)
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			m_key[i] = key[i];
	}

	UuidValue::UuidValue(uint8_t fill)
	{
		memset(m_key, fill, UUID_KEY_LEN);
	}

	UuidValue::UuidValue(const UuidValue &inkey)
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			m_key[i] = (inkey.m_key)[i];
	}

	UuidValue::UuidValue(uint8_t k0,uint8_t k1,uint8_t k2,uint8_t k3,
		uint8_t k4,uint8_t k5,uint8_t k6,uint8_t k7,
		uint8_t k8,uint8_t k9,uint8_t k10,uint8_t k11,
		uint8_t k12,uint8_t k13,uint8_t k14,uint8_t k15)
	{
		m_key[0] = k0;
		m_key[1] = k1;
		m_key[2] = k2;
		m_key[3] = k3;

		m_key[4] = k4;
		m_key[5] = k5;
		m_key[6] = k6;
		m_key[7] = k7;

		m_key[8] = k8;
		m_key[9] = k9;
		m_key[10] = k10;
		m_key[11] = k11;

		m_key[12] = k12;
		m_key[13] = k13;
		m_key[14] = k14;
		m_key[15] = k15;
	}

	UuidValue::UuidValue(const char *str)
	{
		char tmpStr[UUID_KEY_LEN*2 + 1] = {'\0'};
		UUID::getStrFromUUID((const unsigned char*)str, (unsigned char*)tmpStr);
		for (int i = 0; i < UUID_KEY_LEN; i++)
			m_key[i] = UUID::getHexByteFromStr(&(tmpStr[2*i]));

		UUID::encryptUUIDVal(m_key);
	}

	bool UuidValue::operator ==(const UuidValue &inkey) const
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			if (m_key[i] != (inkey.m_key)[i]) return false;

		return true;
	}

	bool UuidValue::operator !=(const UuidValue &inkey) const
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			if (m_key[i] != (inkey.m_key)[i]) return true;

		return false;
	}

	UuidValue &UuidValue::operator =(const UuidValue &inkey)
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			m_key[i] = (inkey.m_key)[i];

		return *this;
	}

	UuidValue::operator bool() const
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			if (m_key[i] != 0) return true;

		return false;
	}

	char *UuidValue::toString(char *stringBuffer) const
	{
		if (!stringBuffer)
			return NULL;

		uint8_t key[UUID_KEY_LEN];
		memcpy(key, m_key, UUID_KEY_LEN);

		UUID::decryptUUIDVal(key);

		int j = 0;
		for (int i = 0; i < UUID_KEY_LEN; i++)
		{ 
			UUID::getStrFromHexByte(key[i], (unsigned char*)(stringBuffer + 2*i + j));
			if (i == UUID_DASH_POSITION_1 || i == UUID_DASH_POSITION_2 
					|| i == UUID_DASH_POSITION_3 || i == UUID_DASH_POSITION_4) 
				stringBuffer[2*(i + 1) + (j++)] = '-';
		}
		return stringBuffer;
	}

	void UuidValue::toArray(uint8_t *array) const
	{
		for (int i = 0; i < UUID_KEY_LEN; i++)
			array[i] = m_key[i];
	}

	//SecurityManager implementation
	SecurityManager::~SecurityManager()
	{
		if (m_SMPrivate)
			m_SMPrivate->release();
	}

	SecurityManager::SecurityManager()
		: m_SMPrivate(NULL)
	{

	}

	SecurityManager::SecurityManager(TMmRc * resultPointer, const MvcDevice &mvcDevice)
		: m_SMPrivate(NULL)
	{
		TMmRc ret = 0;

		int nIdx = mvcDevice.getDeviceIndex();
		if (nIdx == 0)
			m_SMPrivate = SecurityManagerPrivate::newPrivateObj();
		else
			ret = -1;

		*resultPointer = ret;
	}

	SecurityManager::SecurityManager(TMmRc * resultPointer, const MvcDevice &mvcDevice, int32_t timeZoneOffsetMins)
		: m_SMPrivate(NULL)
	{
		*this = SecurityManager(resultPointer, mvcDevice);
		m_SMPrivate->setTimeZoneOffset(timeZoneOffsetMins); //unit : Minute
	}

	SecurityManager::SecurityManager(const SecurityManager& other)
		: m_SMPrivate(NULL)
	{
		*this = other;
	}

	SecurityManager& SecurityManager::operator=(const SecurityManager& other)
	{
		if (other.m_SMPrivate)
			other.m_SMPrivate->addRef();

		if (m_SMPrivate)
			m_SMPrivate->release();

		m_SMPrivate = other.m_SMPrivate;

		return *this;
	}

	SecurityManager::operator bool() const
	{
		return (m_SMPrivate ? true : false);
	}

	SecurityManagerPrivate *SecurityManager::getPrivate() const
	{
		return m_SMPrivate;
	}

	/////////////////////////////////////////////////////////
	TMmRc SecurityManager::connect()
	{
		return m_SMPrivate->connect();
	}

	TMmRc SecurityManager::startSuite(SpbIpAddress *spbList, uint32_t spbCount)
	{
		return m_SMPrivate->startSuite(spbList, spbCount);
	}

	TMmRc SecurityManager::startSuite(const char *spbList)
	{
		return m_SMPrivate->startSuite(spbList);
	}

	TMmRc SecurityManager::stopSuite()
	{
		return m_SMPrivate->stopSuite();
	}

	TMmRc SecurityManager::uploadCplFile(const char *cplPath, CPL_ASSET_EXCEPTION assetExc)
	{
		if (!cplPath)
			return -1;

		return m_SMPrivate->uploadCplFile(cplPath, assetExc);
	}

	TMmRc SecurityManager::uploadCplBuffer(const uint8_t *cplBuffer, uint32_t bufferSize, \
												CPL_ASSET_EXCEPTION assetExc)
	{
		if (!cplBuffer)
			return -1;

		return m_SMPrivate->uploadCplBuffer(cplBuffer, bufferSize, assetExc);
	}

	TMmRc SecurityManager::uploadKdmFile(const char *kdmPath, \
											AesKeyMap *subKeyArray, uint32_t *numberOfEntries)
	{
		if (!kdmPath)
			return -1;

		return m_SMPrivate->uploadKdmFile(kdmPath, subKeyArray, numberOfEntries);
	}

	TMmRc SecurityManager::uploadKdmBuffer(const uint8_t *kdmBuffer, uint32_t bufferSize, \
												AesKeyMap *subKeyArray, uint32_t *numberOfEntries)
	{
		if (!kdmBuffer)
			return -1;

		return m_SMPrivate->uploadKdmBuffer(kdmBuffer, bufferSize, subKeyArray, numberOfEntries);
	}

	TMmRc SecurityManager::purgeCpl(const UuidValue &cplUuid)
	{
		return m_SMPrivate->purgeCpl(cplUuid);
	}

	TMmRc SecurityManager::getCplList(UuidValue *cplUuidArray, uint32_t *arrayLen)
	{
		if (!cplUuidArray)
			return -1;

		return m_SMPrivate->getCplList(cplUuidArray, arrayLen);
	}

	TMmRc SecurityManager::getKdmList(const UuidValue &cplUuid, UuidValue *kdmUuidArray, uint32_t *arrayLen)
	{
		return m_SMPrivate->getKdmList(cplUuid, kdmUuidArray, arrayLen);
	}

	TMmRc SecurityManager::playShow(const char *authId, const UuidValue *cplUuidArray, \
														uint32_t arrayLen, uint64_t *keyExpTime)
	{
		if (!authId)
			return -1;

		return m_SMPrivate->playShow(authId, cplUuidArray, arrayLen, keyExpTime);
	}

	TMmRc SecurityManager::stopShow(const char *authId)
	{
		if (!authId)
			return -1;

		return m_SMPrivate->stopShow(authId);
	}

	TMmRc SecurityManager::checkShow(const UuidValue *cplUuidArray, uint32_t arrayLen, \
															uint64_t checkTime, uint64_t *keyExpTime)
	{
		if (!cplUuidArray)
			return -1;

		return m_SMPrivate->checkShow(cplUuidArray, arrayLen, checkTime, keyExpTime);
	}

	TMmRc SecurityManager::adjustTime(const char *authId, int32_t diff)
	{
		if (!authId)
			return -1;

		return m_SMPrivate->adjustTime(authId, diff);
	}

	TMmRc SecurityManager::getCertificate(uint32_t which, uint8_t *buffer, uint32_t *buffersize)
	{
		if (!buffer)
			return -1;

		return m_SMPrivate->getCertificate(which, buffer, buffersize);
	}

	TMmRc SecurityManager::queryStatus(SM_OPERATION *smOp, SUITE_STATUS *suiteStat, \
															uint64_t *secureTime, int32_t *time_adjust)
	{
		return m_SMPrivate->queryStatus(smOp, suiteStat, secureTime, time_adjust);
	}

	TMmRc SecurityManager::getLogReport(uint8_t *buffer, uint32_t *buffersize, \
												uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime)
	{
		if (!buffer)
			return -1;

		return m_SMPrivate->getLogReport(buffer, buffersize, startTime, endTime, lastLogTime);
	}

	TMmRc SecurityManager::initiateMarriage(const char *authId)
	{
		if (!authId)
			return -1;

		return m_SMPrivate->initiateMarriage(authId);
	}

	TMmRc SecurityManager::serviceDoorTamperTermination(const char *authId)
	{
		if (!authId)
			return -1;

		return m_SMPrivate->serviceDoorTamperTermination(authId);
	}

	TMmRc SecurityManager::getKeyMap(KeyMap *keymapArray, uint32_t *numberOfEntries)
	{
		return m_SMPrivate->getKeyMap(keymapArray, numberOfEntries);
	}

	TMmRc SecurityManager::addCertificate(void *cert)
	{
		if (!cert)
			return -1;

		return m_SMPrivate->addCertificate(cert);
	}

	TMmRc SecurityManager::usePrivateKey(void *pkey)
	{
		if (!pkey)
			return -1;

		return m_SMPrivate->usePrivateKey(pkey);
	}

	TMmRc SecurityManager::loadCertificateChainFile(const char *filename)
	{
		if (!filename)
			return -1;

		return m_SMPrivate->loadCertificateChainFile(filename);
	}

	TMmRc SecurityManager::loadPrivateKeyFile(const char *filename)
	{
		if (!filename)
			return -1;

		return m_SMPrivate->loadPrivateKeyFile(filename);
	}

	TMmRc SecurityManager::zeroize(const char *authId)
	{
		if (!authId)
			return -1;

		return m_SMPrivate->zeroize(authId);
	}

}
