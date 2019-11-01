/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName  : IMB-SM SDK
FileName    £ºSecurityManagerPrivate.h
Author      : chenjingdong@oristartech.com
Date        : 2014-06-30
Version     : v1.0
Description £ºA implementation of the class : SecurityManagerPrivate.   
Others      : 
History     : 

< Author >    			< Date >             < Modification >

****************************************************************************/
#include <sstream>
#include <iostream>

#include "sm_sdk/inner_securitymanager.h"
#include "imbsdk/private/SecurityManagerPrivate.h" 

namespace mvc2
{
	//UUID implementation
	/* Version 4 UUIDs have the form: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx, 
	where x is any hexadecimal digit and y is one of 8, 9, A, or B. 
	e.g. f47ac10b-58cc-4372-a567-0e02b2c3d479. */

	#define __THIRTY_TWO_ZEROS__ "00000000000000000000000000000000"

	static const unsigned char _TABLE[4] = {'8', '9', 'a', 'b'};

	UUID::UUID(void) 
	{
		createRandomUUID();
	}

	UUID::~UUID(void) 
	{
	}

	UUID::UUID(const UUID& other) 
	{
		memcpy(_data.data, other._data.data, sizeof(_data));
	}

	UUID::UUID(const std::string& uuidString) 
	{
		std::stringstream stringStream(uuidString);
		std::string subString;
		unsigned int size = sizeof(_data.data), i = 0, j, loops;
		while(std::getline(stringStream, subString, '-')) 
		{
			loops = subString.length();
			for (j = 0; j < loops; j++) 
			{
				_data.data[i] = subString.at(j);
				i++;
				if (i == size) break;
			}
			if (i == size) break;
		}
	}

	UUID& UUID::operator=(const UUID& other) 
	{
		if (this != &other)
			memcpy(_data.data, other._data.data, sizeof(_data));
		return *this;
	}

	bool UUID::isNil(void) const 
	{
		unsigned int loops = sizeof(_data.data);
		for (unsigned int i = 0; i < loops; i++)
			if (_data.data[i] != '0') return false;
		return true;
	}

	unsigned char UUID::getVersion(void) const 
	{
		return _data.groups.group3[0];
	}

	std::string UUID::toString(void) const 
	{
		std::string result;
		std::stringstream stringStream;
		unsigned int loops = sizeof(_data.groups.group1), i;
		for (i = 0; i < loops; i++)
			stringStream << _data.groups.group1[i];
		stringStream << '-';
		loops = sizeof(_data.groups.group2);
		for (i = 0; i < loops; i++)
			stringStream << _data.groups.group2[i];
		stringStream << '-';
		loops = sizeof(_data.groups.group3);
		for (i = 0; i < loops; i++)
			stringStream << _data.groups.group3[i];
		stringStream << '-';
		loops = sizeof(_data.groups.group4);
		for (i = 0; i < loops; i++)
			stringStream << _data.groups.group4[i];
		stringStream << '-';
		loops = sizeof(_data.groups.group5);
		for (i = 0; i < loops; i++)
			stringStream << _data.groups.group5[i];
		stringStream >> result;
		return result;
	}

	std::string UUID::getRandomUUIDString(void) 
	{
		return UUID().toString();
	}

	uint8_t UUID::getHexByteFromStr(const char *str)
	{
		uint8_t nHexByte, nTmp;

		if (str[0] > '9')
			nTmp = str[0] - 'a' + 10;
		else
			nTmp = str[0] - '0';

		nHexByte = nTmp << 4;

		if (str[1] > '9')
			nTmp = str[1] - 'a' + 10;
		else
			nTmp = str[1] - '0';

		nHexByte |= nTmp;

		return nHexByte;
	}

	void UUID::getStrFromHexByte(const uint8_t nHexByte, unsigned char *str)
	{
		uint8_t nTmp = nHexByte;
		nTmp = ((nTmp & 0xf0) >> 4);
		if (nTmp > 9)
			str[0] = nTmp - 10 + 'a';
		else
			str[0] = nTmp + '0';

		nTmp = nHexByte;
		nTmp = nTmp & 0x0f;
		if (nTmp > 9)
			str[1] = nTmp - 10 + 'a';
		else
			str[1] = nTmp + '0';
	}

	void UUID::getStrFromUUID(const unsigned char *uuid, unsigned char *str)
	{
		int j = 0;
		for (int i = 0; i < 36; i++)
		{
			if (uuid[i] == 0) break;
			if (uuid[i] != '-') str[j++] = uuid[i];
		}
	}

	void UUID::encryptUUIDVal(uint8_t *key)
	{//To encrypt the key array : key[UUID_KEY_LEN]

	}

	void UUID::decryptUUIDVal(uint8_t *key)
	{//To decrypt the key array : key[UUID_KEY_LEN]

	}

	void UUID::createRandomUUID(void) 
	{
		static Random<long long> _random_number(Random<long long>::MAX_SEED);
		static Random<unsigned char> _random_y(4);

		std::stringstream stringStream;
		std::string numberString;
		stringStream << std::hex << _random_number.next();
		stringStream << std::hex << _random_number.next();
		stringStream << __THIRTY_TWO_ZEROS__;
		stringStream >> numberString;
		unsigned int loops = sizeof(_data.data);
		numberString = numberString.substr(0, loops);

		for (unsigned int i = 0; i < loops; i++)
			_data.data[i] = numberString.at(i);
		_data.groups.group3[0] = '4'; //set to version 4
		_data.groups.group4[0] = _TABLE[_random_y.next()]; //set to _random_y
	}

	//SecurityManagerPrivate implementation
	SecurityManagerPrivate::~SecurityManagerPrivate()
	{
		if (m_pInnerSM)
			delete m_pInnerSM;
	}

	SecurityManagerPrivate::SecurityManagerPrivate()
		: BaseClassPrivate(), m_timeZoneOffsetMins(0), m_pInnerSM(NULL)
	{
		char ServerIP[30]="192.168.10.53"; //should be from a configuration obj.
		uint32_t ServerPort = 6002; //should be from a configuration obj.
		m_pInnerSM = new Inner_SecurityManager(ServerIP,ServerPort);
	}

	SecurityManagerPrivate::SecurityManagerPrivate(const SecurityManagerPrivate& other)
		: BaseClassPrivate(), m_timeZoneOffsetMins(0), m_pInnerSM(NULL)
	{
		//char ServerIP[30]="172.23.159.175";
		char ServerIP[30]="192.168.1.53";
		uint32_t ServerPort = 6002;
		m_pInnerSM = new Inner_SecurityManager(ServerIP,ServerPort);

		*this = other;
	}

	SecurityManagerPrivate& SecurityManagerPrivate::operator=(const SecurityManagerPrivate& other)
	{
		m_timeZoneOffsetMins = other.m_timeZoneOffsetMins;

		return *this;
	}

	SecurityManagerPrivate* SecurityManagerPrivate::newPrivateObj()
	{
		return (new SecurityManagerPrivate());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	TMmRc SecurityManagerPrivate::connect()
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->connect();
	}

	TMmRc SecurityManagerPrivate::startSuite(SecurityManager::SpbIpAddress *spbList, uint32_t spbCount)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->startSuite((SpbIpAddress *)spbList, spbCount);
	}

	TMmRc SecurityManagerPrivate::startSuite(const char *spbList)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->startSuite(spbList);
	}

	TMmRc SecurityManagerPrivate::stopSuite()
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->stopSuite();
	}

	TMmRc SecurityManagerPrivate::uploadCplFile(const char *cplPath, SecurityManager::CPL_ASSET_EXCEPTION assetExc)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->uploadCplFile(cplPath, (CPL_ASSET_EXCEPTION)assetExc);
	}

	TMmRc SecurityManagerPrivate::uploadCplBuffer(const uint8_t *cplBuffer, uint32_t bufferSize, \
															SecurityManager::CPL_ASSET_EXCEPTION assetExc)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->uploadCplBuffer(cplBuffer, bufferSize, (CPL_ASSET_EXCEPTION)assetExc);
	}

	TMmRc SecurityManagerPrivate::uploadKdmFile(const char *kdmPath, SecurityManager::AesKeyMap *subKeyArray, \
														uint32_t *numberOfEntries)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->uploadKdmFile(kdmPath, (AesKeyMap *)subKeyArray, numberOfEntries);
	}

	TMmRc SecurityManagerPrivate::uploadKdmBuffer(const uint8_t *kdmBuffer, uint32_t bufferSize, \
													SecurityManager::AesKeyMap *subKeyArray, uint32_t *numberOfEntries)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->uploadKdmBuffer(kdmBuffer, bufferSize, (AesKeyMap *)subKeyArray, numberOfEntries);
	}

	TMmRc SecurityManagerPrivate::purgeCpl(const UuidValue &cplUuid)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->purgeCpl((const inner_sm::UuidValue &)cplUuid);
	}

	TMmRc SecurityManagerPrivate::getCplList(UuidValue *cplUuidArray, uint32_t *arrayLen)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->getCplList((inner_sm::UuidValue *)cplUuidArray, arrayLen);
	}

	TMmRc SecurityManagerPrivate::getKdmList(const UuidValue &cplUuid, UuidValue *kdmUuidArray, uint32_t *arrayLen)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->getKdmList((const inner_sm::UuidValue &)cplUuid, (inner_sm::UuidValue *)kdmUuidArray, arrayLen);
	}

	TMmRc SecurityManagerPrivate::playShow(const char *authId, const UuidValue *cplUuidArray, \
															uint32_t arrayLen, uint64_t *keyExpTime)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->playShow(authId, (const inner_sm::UuidValue *)cplUuidArray, arrayLen, keyExpTime);
	}

	TMmRc SecurityManagerPrivate::stopShow(const char *authId)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->stopShow(authId);
	}

	TMmRc SecurityManagerPrivate::checkShow(const UuidValue *cplUuidArray, uint32_t arrayLen, \
															uint64_t checkTime, uint64_t *keyExpTime)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->checkShow((const inner_sm::UuidValue *)cplUuidArray, arrayLen, checkTime, keyExpTime);
	}

	TMmRc SecurityManagerPrivate::adjustTime(const char *authId, int32_t diff)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->adjustTime(authId, diff);
	}

	TMmRc SecurityManagerPrivate::getCertificate(uint32_t which, uint8_t *buffer, uint32_t *buffersize)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->getCertificate(which, buffer, buffersize);
	}

	TMmRc SecurityManagerPrivate::queryStatus(SecurityManager::SM_OPERATION *smOp, \
													SecurityManager::SUITE_STATUS *suiteStat, \
															uint64_t *secureTime, int32_t *time_adjust)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->queryStatus((SM_OPERATION *)smOp, (SUITE_STATUS *)suiteStat, secureTime, time_adjust);
	}

	TMmRc SecurityManagerPrivate::getLogReport(uint8_t *buffer, uint32_t *buffersize, \
													uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->getLogReport(buffer, buffersize, startTime, endTime, lastLogTime);
	}

	TMmRc SecurityManagerPrivate::initiateMarriage(const char *authId)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->initiateMarriage(authId);
	}

	TMmRc SecurityManagerPrivate::serviceDoorTamperTermination(const char *authId)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->serviceDoorTamperTermination(authId);
	}

	TMmRc SecurityManagerPrivate::getKeyMap(SecurityManager::KeyMap *keymapArray, uint32_t *numberOfEntries)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->getKeyMap((KeyMap *)keymapArray, numberOfEntries);
	}

	TMmRc SecurityManagerPrivate::addCertificate(void *cert)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->addCertificate(cert);
	}

	TMmRc SecurityManagerPrivate::usePrivateKey(void *pkey)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->usePrivateKey(pkey);
	}

	TMmRc SecurityManagerPrivate::loadCertificateChainFile(const char *filename)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->loadCertificateChainFile(filename);
	}

	TMmRc SecurityManagerPrivate::loadPrivateKeyFile(const char *filename)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->loadPrivateKeyFile(filename);
	}

	TMmRc SecurityManagerPrivate::zeroize(const char *authId)
	{
		if (!m_pInnerSM)
			return -1;

		return m_pInnerSM->zeroize(authId);
	}

	/////////////////////////////////////////////////////////////////
	void SecurityManagerPrivate::testMvc2api()
	{
		if (!m_pInnerSM)
			return;

#ifdef MVC2API_DEBUG
		printf("... Start to test the class : SecurityManagerPrivate ...\n");

		printf("... End to test the class : SecurityManagerPrivate ...\n");
#endif
	}
}
