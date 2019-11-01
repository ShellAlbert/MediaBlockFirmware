/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName  : IMB-SM SDK
FileName    £ºSecurityManagerPrivate.h
Author      : chenjingdong@oristartech.com
Date        : 2014-06-30
Version     : v1.0
Description £ºA definition of the class : SecurityManagerPrivate.   
Others      : 
History     : 

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef _MVC2API_SECURITYMANAGERPRIVATE_H_
#define _MVC2API_SECURITYMANAGERPRIVATE_H_

#include <string>
#include <time.h>

#include "BaseClassPrivate.h" 
#include "../mvc2api_securitymanager.h"

class Inner_SecurityManager;

namespace mvc2
{

	#define __MODULUS__     9223372036854775807LL
	#define __MULTIPLER__   25214903917LL
	#define __MDM__         365790489LL
	#define __MMM__         2967330394LL

	template <typename T>
	class Random 
	{
	public:
		Random(void) : _seed(1) 
		{
			_seedUniquifier = time(0);
		}

		Random(T seed) : _seed(seed) 
		{
			_seedUniquifier = time(0);
		}

		virtual ~Random(void) {}

		Random(const Random& other) 
		{
			_seed = other._seed;
			_seedUniquifier = other._seedUniquifier;
		}

		Random& operator=(const Random& other) 
		{
			if (this != &other) 
			{
				_seed = other._seed;
				_seedUniquifier = other._seedUniquifier;
			}
			return *this;
		}

		void setSeed(T seed) 
		{
			_seed = seed;
		}

		T next(void) 
		{
			return (T)(nextSample() * _seed);
		}

		static const long long MAX_SEED = __MODULUS__;

	private:
		T _seed;
		long long _seedUniquifier;

		double nextSample(void) 
		{
			_seedUniquifier = __MULTIPLER__ * (_seedUniquifier % __MDM__) - __MMM__ * (_seedUniquifier / __MDM__);
			if (_seedUniquifier < 0)
				_seedUniquifier += __MODULUS__;
			return (double)(_seedUniquifier / (double)__MODULUS__);
		}
	};

	#pragma pack(push)
	#pragma pack(4)
	typedef union 
	{
		unsigned char data[32];
		struct 
		{
			unsigned char group1[8];
			unsigned char group2[4];
			unsigned char group3[4];
			unsigned char group4[4];
			unsigned char group5[12];
		} groups;
	} UUID_T;
	#pragma pack(pop)

	class UUID 
	{
	public:
		UUID(void);
		virtual ~UUID(void);
		UUID(const UUID&);
		explicit UUID(const std::string&);
		UUID& operator=(const UUID&);

		bool isNil(void) const;
		unsigned char getVersion(void) const;
		std::string toString(void) const;

		static std::string getRandomUUIDString(void);
		static uint8_t getHexByteFromStr(const char *str);
		static void getStrFromHexByte(const uint8_t nHexByte, unsigned char *str);
		static void getStrFromUUID(const unsigned char *uuid, unsigned char *str);
		static void encryptUUIDVal(uint8_t *key);
		static void decryptUUIDVal(uint8_t *key);

	private:
		UUID_T _data;

		void createRandomUUID(void);
	};

	class SecurityManagerPrivate : public BaseClassPrivate
	{
		virtual ~SecurityManagerPrivate();

		SecurityManagerPrivate();
		SecurityManagerPrivate(const SecurityManagerPrivate& other);


	public:
		SecurityManagerPrivate& operator=(const SecurityManagerPrivate& other);

		static SecurityManagerPrivate* newPrivateObj();

		///////////////////////////////////////////////////////
		TMmRc connect();

		TMmRc startSuite(SecurityManager::SpbIpAddress *spbList, uint32_t spbCount);

		TMmRc startSuite(const char *spbList = 0);

		TMmRc stopSuite();

		TMmRc uploadCplFile(const char *cplPath, \
								SecurityManager::CPL_ASSET_EXCEPTION assetExc = SecurityManager::CplException_None);

		TMmRc uploadCplBuffer(const uint8_t *cplBuffer, uint32_t bufferSize, \
									SecurityManager::CPL_ASSET_EXCEPTION assetExc = SecurityManager::CplException_None);

		TMmRc uploadKdmFile(const char *kdmPath, SecurityManager::AesKeyMap *subKeyArray = 0, \
																		uint32_t *numberOfEntries = 0);

		TMmRc uploadKdmBuffer(const uint8_t *kdmBuffer, uint32_t bufferSize, \
									SecurityManager::AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0);

		TMmRc purgeCpl(const UuidValue &cplUuid);

		TMmRc getCplList(UuidValue *cplUuidArray, uint32_t *arrayLen);

		TMmRc getKdmList(const UuidValue &cplUuid, UuidValue *kdmUuidArray, uint32_t *arrayLen);

		TMmRc playShow(const char *authId, const UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t *keyExpTime = 0);

		TMmRc stopShow(const char *authId);

		TMmRc checkShow(const UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0);

		TMmRc adjustTime(const char *authId, int32_t diff);

		TMmRc getCertificate(uint32_t which, uint8_t *buffer, uint32_t *buffersize);

		TMmRc queryStatus(SecurityManager::SM_OPERATION *smOp, SecurityManager::SUITE_STATUS *suiteStat, \
								uint64_t *secureTime, int32_t *time_adjust);

		TMmRc getLogReport(uint8_t *buffer, uint32_t *buffersize, uint64_t startTime, uint64_t endTime, \
								uint64_t *lastLogTime);

		TMmRc initiateMarriage(const char *authId);

		TMmRc serviceDoorTamperTermination(const char *authId);

		TMmRc getKeyMap(SecurityManager::KeyMap *keymapArray, uint32_t *numberOfEntries);

		TMmRc addCertificate(void *cert);

		TMmRc usePrivateKey(void *pkey);

		TMmRc loadCertificateChainFile(const char *filename);
		TMmRc loadPrivateKeyFile(const char *filename);

		TMmRc zeroize(const char *authId);

		//////////////////////////////////////////////////////
		void setTimeZoneOffset(int32_t timeZoneOffsetMins) { m_timeZoneOffsetMins = timeZoneOffsetMins; }; 

		virtual void testMvc2api();

	private:
		int32_t m_timeZoneOffsetMins;
		Inner_SecurityManager* m_pInnerSM;

	};
}

#endif