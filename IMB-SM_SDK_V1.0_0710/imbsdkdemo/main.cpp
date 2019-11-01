#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "p12/pkcs12info.h"

#include "imbsdk/mvc2api.h"

using namespace mvc2;

int main(int argc, char **argv)
{
	TMmRc ret = 0;
	int MMRC_OK = 0;
	{
		MvcDevice g_mvcDevice;

		//check the MvcDevice interface : getDeviceIndex().
		int nDevIndex = g_mvcDevice.getDeviceIndex(); 

		SecurityManager g_mvcSecManager; 
		SecurityManager secManager; // an empty SecurityManager object will be created
		if (secManager) // bool operator checks if the object is empty or not
		{
			printf("object is existing\n");
		}
		else
			printf("object is empty\n");

		// create a SecurityManager
		TMmRc resultPointer;

		secManager = SecurityManager(&resultPointer, g_mvcDevice); // assign a SecurityManager to the empty object
		if (MM_IS_ERROR(resultPointer))
		{
			printf("failed to create SecManager : %d\n",resultPointer);
			exit(0);
		}

		g_mvcSecManager = secManager; // save the securitymanager object in a global variable for later use

		g_mvcSecManager = SecurityManager(&resultPointer, g_mvcDevice, 480);

		secManager = SecurityManager(g_mvcSecManager); // assign a SecurityManager to the non-empty object

		if (secManager) // bool operator checks if the object is empty or not
		{
			printf("object is existing\n");
		}
		else
			printf("object is empty\n");


		//Start to test 26 SM APIs ...
		////interfaces : loadCertificateChainFile and addCertificate
		ret = secManager.loadCertificateChainFile("certchain.dat");
		if(MMRC_OK != ret)
		{
			printf("2_loadCertificateChainFile is error! \n");    
			printf("3_addCertificate is error! \n");    
		}
		else
		{
			printf("2_loadCertificateChainFile is Success \n");
			printf("3_addCertificate is Success \n");
		}
    
		////interfaces : loadPrivateKeyFile and usePrvateKey
		ret = secManager.loadPrivateKeyFile("SMStheLeafprikey.pem");   
		if(MMRC_OK != ret)
		{
			printf("4_loadPrivateKeyFile is error! \n");    
			printf("5_usePrvateKey is error");
		}
		else
		{
			printf("4_loadPrivateKeyFile is Success \n");
			printf("5_usePrivateKey is Success \n");
		}

		////interface : connect
		ret = secManager.connect();
		if(MMRC_OK != ret)
		{
			printf("6_connect is error! \n");   
		}
		else
		{
			printf("6_connect is Success \n");
		}

		CRYPTO_malloc_init();
		OpenSSL_add_all_algorithms();
		ERR_load_crypto_strings();

		////interface : startSuite
		ret = secManager.startSuite();
		if(MMRC_OK != ret)
		{
			printf("7_startSuite is error! \n");
		}
		else
		{
			printf("7_startSuite is Success! \n");
		}
     
		////interfaces : uploadCplFile and uploadCplBuffer
		//ret = secManager.uploadCplFile("CPL_50c19487-c434-41d8-bd36-8e77d1302b37.cpl.xml");
    ret = secManager.uploadCplFile("gansidui0320_e_cpl.cpl.xml");
		if(MMRC_OK != ret)
		{
			printf("8_uploadCplFile is error! \n");
			printf("9_uploadCplBuffer is error! \n");
		}
		else
		{
			printf("8_uploadCplFile is Success! \n");
			printf("9_uploadCplBuffer is Success! \n");
		}

		////interfaces : uploadKdmFile and uploadKdmBuffer
		//ret = secManager.uploadKdmFile("DisneyTestReel_v0.8fortest.kdm.xml");
	  ret = secManager.uploadKdmFile("GANSIDUI0320_KDM.xml");	
		if(MMRC_OK != ret)
		{
			printf("10_uploadKdmFile is error! \n");
			printf("11_uploadKdmBuffer is error! \n");
		}
		else
		{
			printf("10_uploadKdmFile is Success! \n");
			printf("11_uploadKdmBuffer is Success! \n");
		}

		////interface : checkShow
		unsigned char uuid_36[37] = {0};
		
		//后加的
		//FILE *newfp = fopen( "CPL_50c19487-c434-41d8-bd36-8e77d1302b37.cpl.xml","rb" );	
		FILE *newfp = fopen( "gansidui0320_e_cpl.cpl.xml","rb" );
		if( newfp == NULL )
		{
			printf( "[ERROR] Can not Open CPL File\n");
			return -1;
		}
		fseek(newfp, 0, SEEK_END);
		int CPLContentLen = ftell(newfp);
		unsigned char CPLContent[50*1024];
		fseek(newfp, 0, SEEK_SET);
		memset( CPLContent, 0 ,CPLContentLen );
		fread( CPLContent, CPLContentLen, 1, newfp );            	
		fclose(newfp); 
		char  *uuidoffset = NULL;
		char  *end = NULL;
		char  flagstring[] = "<Id>urn:uuid:";
		uuidoffset = strstr((char *)CPLContent, flagstring);
		if( !uuidoffset )
		{
			printf("[ERROR] Get CPL id error");
			return -1;
		}
		end = strchr(uuidoffset+strlen(flagstring), '<');
		unsigned char m_CPLId[128] = {0}; 
		memcpy( m_CPLId, uuidoffset+strlen(flagstring), end-(uuidoffset+strlen(flagstring)) );
		printf("[INFO]  CPLID[1]: %s\n", m_CPLId);
		//后加的
	
    sprintf( (char*)uuid_36, "%s", m_CPLId);

		UuidValue* cplUuidArray = new UuidValue((char*)uuid_36);

		/* uint64_t checkTime = 1;
		uint32_t array = 0;
		uint64_t check = 1;
		ret = secManager.checkShow( cplUuidArray, array, check, &checkTime );
		if( ret == 0 )
		{
			printf( "13_checkShow Successful\n" );
		}
		else
		{
			printf( "13_checkShow Failure\n" );
		} */

		////interface : playShow
		unsigned int arrayLen = 1;
		unsigned long long keyExpTime = 1;
   
		ret = secManager.playShow( "abc", cplUuidArray, arrayLen, &keyExpTime );
		if(MMRC_OK != ret)
		{
			printf("12_playShow is error! \n");
		}
		else
		{
			printf("12_playShow is Success! \n");
		}

		delete cplUuidArray;

		////interface : stopShow
		ret = secManager.stopShow( "abc" );
		if( ret == 0 )
		{
			printf( "14_stopShow Successful\n" );
		}
		else
		{
			printf( "14_stopShow Failure\n" );
		}

		////interface : adjustTime
#if 0
		int diff = 6;
		ret = secManager.adjustTime( "abc", diff );
		if( ret == 0 )
		{
			printf( "15_adjustTime Successful\n" );
		}
		else
		{
			printf( "15_adjustTime Failure\n" );
		}
#endif
		////interface : queryStatus
		SecurityManager::SM_OPERATION smOp;
		SecurityManager::SUITE_STATUS suiteStat;
		unsigned long long secureTime = 0;
		int32_t time_adjust = 0;
		ret = secManager.queryStatus( &smOp, &suiteStat, &secureTime, &time_adjust );
		if( ret == 0 )
		{
			printf( "16_queryStatus Successful\n" );
		}
		else
		{
			printf( "16_queryStatus Failure\n" );
		}

		////interface : initiateMarriage
		ret = secManager.initiateMarriage( "abc" );
		if( ret == 0 )
		{
				printf( "17_initiateMarriage Successful\n" );
		}
		else
		{
				printf( "17_initiateMarriage Failure\n" );
		}

		////interface : serviceDoorTamperTermination
		ret = secManager.serviceDoorTamperTermination( "abc" );
		if( ret == 0 )
		{
				printf( "18_serviceDoorTamperTermination Successful\n" );
		}
		else
		{
				printf( "18_serviceDoorTamperTermination Failure\n" );
		}

		////interface : getLogReport
#if 0
		struct tm _start_time,_end_time;
		char _tmp[32]="20140613-100000";
		strptime(_tmp,"%Y%m%d-%H%M%S",&_start_time);
		char tmp_[32]="20140616-090000";
		strptime(tmp_,"%Y%m%d-%H%M%S",&_end_time);

		time_t startTime = mktime(&_start_time);
		time_t endTime = mktime(&_end_time);
  
		uint8_t  buf[10]={0};
		uint32_t bufsize=0;
		uint64_t tmp=0;

		ret = secManager.getLogReport(buf, &bufsize, startTime, endTime, &tmp);
		if( ret == 0 )
		{
			printf( "19_getLogReport Successful\n" );
		}
		else
		{
			printf( "19_getLogReport Failure\n" );
		}

		sleep(3);
#endif
		////interface : getKeyMap
		//ret = secManager.getKeyMap()
		if(MMRC_OK != ret)
		{
			printf("20_getKeyMap is error! \n");
		}
		else
		{
			printf("20_getKeyMap is Success! \n");
		}

		////interface : getCplList
		//ret = secManager.getCplList();
		if(MMRC_OK != ret)
		{
			printf("21_getCplList is error! \n");
		}
		else
		{
			printf("21_getCplList is Success! \n");
		}

		////interface : getKdmList
		//ret = secManager.getKdmList();  
		if(MMRC_OK != ret)
		{
			printf("22_getKdmList is error! \n");
		}
		else
		{
			printf("22_getKdmList is Success! \n");
		}

		////interface : getCertficate
		//ret = secManager.getCertficate();
		if(MMRC_OK != ret)
		{
			printf("23_getCertficate is error! \n");
		}
		else
		{
			printf("23_getCertficate is Success! \n");
		}

		////interface : stopSuite
		ret = secManager.stopSuite(); 
		if(MMRC_OK != ret)
		{
			printf("24_stopSuite is error! \n");
		}
		else
		{
			printf("24_stopSuite is Success! \n");
		}

		////interface : purgeCpl
		//ret = secManager.purgeCpl();
		if(MMRC_OK != ret)
		{
			printf("25_purgeCpl is error! \n");
		}
		else
		{
			printf("25_prugeCpl is Success! \n");
		}
   
		////interface : zeroize
		secManager.zeroize( "abc" );
		if( ret == 0 )
		{
			printf( "26_zeroize Successful\n" );
		}
		else
		{
			printf( "26_zeroize Failure\n" );
		}

		//End to test 26 SM APIs
	}

	
	{//Start to test the class : UuidValue ...

		/* Version 4 UUIDs have the form: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx, 
		where x is any hexadecimal digit and y is one of 8, 9, A, or B. 
		e.g. f47ac10b-58cc-4372-a567-0e02b2c3d479. */

		/////////case1
		std::string strTmp = "298d198d-aa60-48af-a9f4-638f8f274afa";
		UuidValue uuid3(strTmp.c_str());
		if (uuid3)
			printf("uuid3 is OK!\n");
		else
			printf("uuid3 is NULL!\n");

		/////////case2
		uint8_t array[UuidValue::UUID_KEY_LEN] = {0};
		uuid3.toArray(array);

		/////////case3
		UuidValue uuid1(array);

		/////////case4
		UuidValue uuid0;
		if (uuid0)
			printf("uuid0 is OK!\n");
		else
			printf("uuid0 is NULL!\n");

		/////////case5
		UuidValue uuid2(uuid1);

		/////////case6
		char UUIDString[UuidValue::UUID_KEY_LEN*2 + 4 + 1] = {'\0'};

		/////////case7
		uuid2.toString(UUIDString);

		/////////case8
		uint8_t nTmp1 = uuid2[1];
		uint8_t nTmp15 = uuid2[15];

		/////////case9
		UuidValue uuid4(array[0], array[1], array[2], array[3]
							, array[4], array[5], array[6], array[7]
								, array[8], array[9], array[10], array[11]
									, array[12], array[13], array[14], array[15]);

		/////////case10
		if (uuid3 == uuid4)
			printf("uuid3 == uuid4\n");

		/////////case11
		if (uuid0 != uuid4)
			printf("uuid0 != uuid4\n");

		/////////case12
		uuid0 = uuid3;

		/////////case13
		if (uuid0 == uuid4)
			printf("uuid0 == uuid4\n");

	}//End to test the class : UuidValue

	return ret;
}
