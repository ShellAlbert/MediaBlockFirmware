/******************************************************************************
copyright (C), 2010-2020, OristarTech Co., Ltd.
ModuleName  :  SM SDK
FileName    :  inner_securitymanager.h
Author      :  wangwei@oristartech.com
Date        :  14/06/27
Version     :  v1.0
Description :  To implement SM SDK
Others      :  
History     : 
< Author >                        < Date >             < Modification > 
chenjingdong                      2014-07-03           add a UUID class

******************************************************************************/

#ifndef _INNER_SECURITYMANAGER_H
#define _INNER_SECURITYMANAGER_H

#include <tls/tlstranslateclient.h>
#include <smsdk/errornumber.h>
#include <crypto/arithmatic.h>
#include <crypto/arithtype.h>
#include <p12/pkcs12info.h>

//[IMBSM v1.0_SMSDK] deleted by chenjingdong, 2014-07-03 start
/* #include "CAuthentication.h"
#include "CLogOperation.h"
#include "ingestKDM.h" */
//[IMBSM v1.0_SMSDK] end

#include <vector>
using namespace std;

typedef int TMmRc;

//[IMBSM v1.0_SMSDK] deleted by chenjingdong, 2014-07-03 start
/* void uuid_add_separator( const unsigned char *uuid_16, unsigned char *uuid_36 );
void uuid_sub_separator( unsigned char *uuid_16, const unsigned char *uuid_36 );

typedef struct 
{
	unsigned char m_key[16];
} UuidValue; */
//[IMBSM v1.0_SMSDK] end

//[IMBSM v1.0_SMSDK] added by chenjingdong, 2014-07-03 start
namespace inner_sm
{
	///////////
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

	//////////

	class UuidValue
	{
	public:
		enum
		{
			UUID_KEY_LEN			= 16,
			//
			UUID_DASH_POSITION_1	= 3,
			UUID_DASH_POSITION_2	= 5,
			UUID_DASH_POSITION_3	= 7,
			UUID_DASH_POSITION_4	= 9
		};

		UuidValue(const uint8_t *key);
		UuidValue(uint8_t fill = 0);
		UuidValue(const UuidValue &inkey);
		UuidValue(uint8_t k0,uint8_t k1,uint8_t k2,uint8_t k3,
			uint8_t k4,uint8_t k5,uint8_t k6,uint8_t k7,
			uint8_t k8,uint8_t k9,uint8_t k10,uint8_t k11,
			uint8_t k12,uint8_t k13,uint8_t k14,uint8_t k15);
		UuidValue(const char *str);

		bool operator ==(const UuidValue &inkey) const;
		bool operator !=(const UuidValue &inkey) const;
		UuidValue &operator =(const UuidValue &inkey);

		uint8_t operator[](uint8_t index) const
		{
			return(m_key[index]);
		}

		uint8_t &operator[](uint8_t index)
		{
			return(m_key[index]);
		}

		operator bool() const;

		char *toString(char *stringBuffer) const;

		void toArray(uint8_t *array) const;

	protected:
		uint8_t m_key[UUID_KEY_LEN];
	};
}
//[IMBSM v1.0_SMSDK] end

typedef struct
{
	unsigned char b3;
	unsigned char b2;
	unsigned char b1;
	unsigned char b0;  /* as in b0.b1.b2.b3 */
} SpbIpAddress;

enum CPL_ASSET_EXCEPTION
{
	CplException_None		= 0,
	CplException_Hash		= 1,
	CplException_Missing	= 2
};
		
enum SM_OPERATION
{
	Operation_Unknown		= 0,
	Operation_NotPlaying	= 1,		// idle
	Operation_Playing		= 2
};

enum SUITE_STATUS
{
	Suite_Started		= 1,
	Suite_Stopped		= 2,
	Suite_Progress		= 3,
	Suite_Restarted		= 4,
	Suite_Lost			= 5,
	Suite_Error			= 6
};

typedef struct 
{
//[IMBSM v1.0_SMSDK] modified by chenjingdong, 2014-07-03 start
/*	UuidValue key_id;
	UuidValue kdm_id; */
	
	inner_sm::UuidValue key_id;
	inner_sm::UuidValue kdm_id;
//[IMBSM v1.0_SMSDK] end

	unsigned short key_index;
	unsigned char key_type;
} KeyMap;

typedef struct 
{
//[IMBSM v1.0_SMSDK] modified by chenjingdong, 2014-07-03 start
/*	UuidValue key_id; */

	inner_sm::UuidValue key_id;
//[IMBSM v1.0_SMSDK] end

	unsigned char aes_key[16];
} AesKeyMap;

struct requserinfo_st{
	unsigned char puserID[30];
	unsigned char pusername[18];// 12-->18 实际有效长最大16，变化原因加了base
	unsigned char password[14];//8-->14 实际有效长最大12
	unsigned char role[16];
	unsigned int signArith;
	unsigned int signvaluelen;
	unsigned char* signvalue;
};

class Inner_SecurityManager
{
	public:

		Inner_SecurityManager( char* ip, int port );
		~Inner_SecurityManager();

		TMmRc connect();
		TMmRc startSuite( SpbIpAddress *spbList, uint32_t  spbCount );
		TMmRc startSuite( const char *spbList = 0 );
		TMmRc stopSuite();
		TMmRc uploadCplFile( const char *cplPath, CPL_ASSET_EXCEPTION assetExc = CplException_None );
		TMmRc uploadCplBuffer( const uint8_t *cplBuffer, uint32_t bufferSize, CPL_ASSET_EXCEPTION assetExc = CplException_None );
		TMmRc uploadKdmFile( const char *kdmPath, AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0 );
		TMmRc uploadKdmBuffer( const uint8_t *kdmBuffer, uint32_t bufferSize, AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0 );
//[IMBSM v1.0_SMSDK] modified by chenjingdong, 2014-07-03 start
/*		TMmRc purgeCpl( const UuidValue &cplUuid );
		TMmRc getCplList( UuidValue *cplUuidArray, uint32_t *arrayLen );
		TMmRc getKdmList( const UuidValue &cplUuid, UuidValue *kdmUuidArray, uint32_t *arrayLen );
		TMmRc playShow( const char *authId, const UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t *keyExpTime = 0 );
		TMmRc checkShow( const UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0 ); */
		
		TMmRc purgeCpl( const inner_sm::UuidValue &cplUuid );
		TMmRc getCplList( inner_sm::UuidValue *cplUuidArray, uint32_t *arrayLen );
		TMmRc getKdmList( const inner_sm::UuidValue &cplUuid, inner_sm::UuidValue *kdmUuidArray, uint32_t *arrayLen );
		TMmRc playShow( const char *authId, const inner_sm::UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t *keyExpTime = 0 );
		TMmRc checkShow( const inner_sm::UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0 );		
//[IMBSM v1.0_SMSDK] end	
	
		TMmRc stopShow( const char *authId );
		TMmRc adjustTime( const char *authId, uint32_t diff );
		TMmRc getCertificate( uint32_t which, uint8_t *buffer, uint32_t *buffersize );
		TMmRc queryStatus( SM_OPERATION *smOp, SUITE_STATUS *suiteStat, uint64_t *secureTime, int32_t *time_adjust );
		TMmRc getLogReport( uint8_t *buffer, uint32_t *buffersize, uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime );
		TMmRc initiateMarriage( const char *authId );
		TMmRc serviceDoorTamperTermination( const char *authId );
		TMmRc getKeyMap( KeyMap *keymapArray, uint32_t *numberOfEntries );
		TMmRc addCertificate( void *cert );
		TMmRc usePrivateKey( void *pkey );
		TMmRc loadCertificateChainFile( const char *filename );
		TMmRc loadPrivateKeyFile( const char *filename );
		TMmRc zeroize( const char *authId );

		//[IMBSM v1.0_DCEventLog] added by chenjingdong, 2014-05-30 start
#ifdef SM_LOG_DOWNLOAD_ON_TLS
		static CTLS_Translate_Client   *pLogTLS;
		static bool isLogConnectOk;
#endif
		//[IMBSM v1.0_DCEventLog] end
			
	private:
	
		int login( int user );
		int logout();

		//[IMBSM v1.0_DCEventLog] added by chenjingdong, 2014-05-30 start
		int	myport;
		char myip[30];
		//[IMBSM v1.0_DCEventLog] end
			
		bool isConnect;
		
		vector<X509 *> m_CaList;
		X509 m_SMSCert;
		bool ism_SMSCert;
		EVP_PKEY *m_SMSPKey;
		
		CTLS_Translate_Client *pTLS;
		
		EVP_PKEY* k;
		unsigned int signArith;
		requserinfo_st req_userinfotemp;
		
		bool isLogin;
	
};



#endif
