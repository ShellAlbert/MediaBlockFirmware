/*
* Copyright (c) 2007 �й�����
* All rights reserved.
* * �ļ����ƣ�Ccsp.h
* ժ    Ҫ���ؼ���ȫ�����࣬�ṩ�԰�ȫ���������ã����ʼ��������
* * ��ǰ�汾��3.0
* ��    �ߣ�yinlifang
** ȡ���汾����
* ԭ����  ��drm
* ������ڣ�2009��12��11��
* �޸����ڣ�2010��5��26�գ�2010��6��23�գ�2011��8��2��
*/

#ifndef _CCSPMANAGER_H_
#define _CCSPMANAGER_H_

#include "smsdk/errornumber.h" 
#include "crypto/arithmatic.h" 
#include "crypto/arithtype.h" 
//#include "harddriver/ldmp_key.h" 
#include "harddriver/Manage_MSP430_Status.h" 	//modify by yin 2011.7.28
#include "iniparse/IniFile.h" 					//add by yin 2010.6.23
//#define HAVE_PROJECT_CA_FILE 1				//modify by sun 2012.3.12

//modify by yin 2010.9.30 start
const unsigned int BUFMAXLINE= 256; 			//ini������
//const unsigned int CONTENTKEK_LEN= 16; 		//������Կ������Կ�ĳ��� //del by yin 2011.5.26
const unsigned int SEED_LEN= 16; 				//���ӵĳ���
const unsigned int SEEDKEY_LEN= 16; 			//������Կ�ĳ���
//const unsigned int IV_LEN= 16; 				//IV�ĳ���//del by yin 2011.5.26
const unsigned int FIRMWAREKEY_LEN= 16; 		//�̼�������Կ�ĳ���
const unsigned int HMACKEY_LEN= 16; 			//hmac��Կ�ĳ���
const unsigned int HMACSHA1_DIGEST_LEN= 20; 	//hmac(sha1)ֵ�ĳ���
//modify by yin 2010.9.30 end

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#define ssizeof(TYPE, MEMBER) (sizeof(((TYPE *)0)->MEMBER))

//add by yin 2011.7.28
typedef unsigned long long u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;
typedef signed   short i16;
typedef signed   char  i8;

struct user_info { 
	u8 userID[30];      //�û�ID 			//user ID 
	u8 password[14]; 	//����base���ֵ 	//password base64 value
	i32 role;      		//��ɫֵ			//role
};
 
struct csps_st{ 
	u8 csps_hmackey[40]; 			//hmac key ʵ��keyֵ����֧��32
	u8 csps_hmacvalue[32];			//hmac value �㷨�̶�hmac-sha1��ʵ�ʴ�СΪ20
	u8 csps_deviceprikey[2048];		//private key ˽Կ��һ��Ϊ1704
	u8 csps_randseed[40]; 			//rand seed
	u8 csps_seedkey[40];			//seed key	
	u8 csps_firmwarekey[24];		//key for firmware update
	struct user_info uinfo[2]; 		//user information
};


typedef struct cspinfo_st  			//csp��Ϣ�ṹ�� add by yin 2010.6.2
{
	u16 csps_hmackeylen;			//hmac��Կ����
	u8* csps_hmackey;				//hmac��Կֵ
		
	u16 csps_hmacvaluelen;			//hmacֵ����
	u8* csps_hmacvalue;				//hmacֵ���㷨�̶�hmac-sha1��ʵ�ʴ�СΪ20
	
	u16 csps_deviceprikeylen;		//˽Կ����
	u8* csps_deviceprikey;			//˽Կ��һ��Ϊ1704
	
	u16 csps_randseedlen;			//��������ӳ���
	u8* csps_randseed; 				//���������
	
	u16 csps_seedkeylen;			//������Կ����
	u8* csps_seedkey;				//������Կ
	
	//u16 csps_ivlen;				//iv����//del by yin 2011.5.26
	//u8* csps_iv;					//ivֵ//del by yin 2011.5.26
	
	//u16 csps_keklen;				//���ݼ�����Կ����//del by yin 2011.5.26
	//u8* csps_kek; 				//������Կ������Կ���㷨�̶� AES-128-CFB//del by yin 2011.5.26
	
	u16 csps_firmwarekeylen;		//�̼�������Կ����
	u8* csps_firmwarekey;			//�̼�������Կ
	
	//i32 csps_projectortimedvalue;	//sm��projector��ʱ���,����Ϊ��λ//del by yin 2011.5.26
	//i32 csps_smstimedvalue;		//sms��sm��ʱ������Ϊ��λ��������ʱ���������֤��һ����������(+-)6����//del by yin 2011.5.26
};

class Ccspmanager
{
public:	

	Ccspmanager(const int ldmpopenflag=1); //��Ӳ���ڴ汣��csp add by yin 2010.4.7
	~Ccspmanager();	

	/****FUNCTION***************************************************
	* DESCRIPTION : �����豸˽Կ
	*       INPUT : Deviceprikey �豸˽Կ
	*				DeviceprikeyLen �豸˽Կ����			
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	int setDeviceprikey(const unsigned char* Deviceprikey, const unsigned int DeviceprikeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�豸˽Կ
	*       INPUT : DeviceprikeybufLen	��׼���Ĵ洢�豸˽Կ�Ŀռ䳤��		
	*      OUTPUT : Deviceprikey �豸˽Կ
	*               DeviceprikeyLen �豸˽Կ����
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getDeviceprikey(unsigned int DeviceprikeybufLen,unsigned char* Deviceprikey,  unsigned int& DeviceprikeyLen);	

	/****FUNCTION***************************************************
	* DESCRIPTION : ������������ӣ�����������ӱ����ڰ�ȫ�洢��
	*       INPUT : randseed ���������
	*				randseedLen ��������ӳ���		
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	int setRandseed(const unsigned char* randseed, const unsigned int randseedLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ��������ӣ�����������ӴӰ�ȫ�洢���ȡ������
	*       INPUT : randseedbufLen �ѿ��ٵ���������ӿռ䳤��			
	*      OUTPUT : Randseed ���������
	*               randseedLen ��������ӳ���	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getRandseed(unsigned int randseedbufLen, unsigned char* randseed, unsigned int& randseedLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : ����������Կ����������Կ�����ڰ�ȫ�洢��
	*       INPUT : seedkey ������Կ
	*				seedkeyLen ������Կ����		
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	int setseedkey(const unsigned char* seedkey, const unsigned int seedkeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ������Կ����������Կ�Ӱ�ȫ�洢���ȡ������
	*       INPUT : seedkeybufLen �ѿ��ٵ�������Կ�ռ䳤��			
	*      OUTPUT : seedkey ������Կ
	*               seedkeyLen ��������ӳ���	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getseedkey(unsigned int seedkeybufLen, unsigned char* seedkey, unsigned int& seedkeyLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : ����iv����iv�����ڰ�ȫ�洢��
	*       INPUT : iv ��ʼ������
	*				ivLen ��ʼ����������		
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	//int setIV(const unsigned char* iv, const unsigned int ivLen);//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡiv����iv�Ӱ�ȫ�洢���ȡ������
	*       INPUT : ivbufLen �ѿ��ٵĳ�ʼ�������ռ䳤��			
	*      OUTPUT : iv ��ʼ������
	*				ivLen ��ʼ����������	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	//int getIV(unsigned int ivbufLen, unsigned char* iv, unsigned int& ivLen);//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����HMAC��Կ����HMAC��Կ�����ڰ�ȫ�洢��
	*       INPUT : HmacKey  HMAC��Կ
	*				HmacKeyLen HMAC��Կ����Կ����			
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	int setHmacKey(const unsigned char* HmacKey, const unsigned int HmacKeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡHMAC��Կ����HMAC��Կ�Ӱ�ȫ�洢���ȡ������
	*       INPUT : ��			
	*      OUTPUT : HmacKey  HMAC��Կ
	*               HmacKeyLen HMAC��Կ����Կ����
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getHmacKey(unsigned int HmacKeybufLen,unsigned char* HmacKey, unsigned int& HmacKeyLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : ����csps��HMACֵ����csps��HMACֵ�����ڰ�ȫ�洢��
	*       INPUT : HmacValue  HMACֵ
	*				HmacValueLen HMACֵ����			
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	int setHmacValue(const unsigned char* HmacValue, const unsigned int HmacValueLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡcsps��HMACֵ����csps��HMACֵ�Ӱ�ȫ�洢���ȡ������
	*       INPUT : ��			
	*      OUTPUT : HmacValue  HMACֵ
	*               HmacValueLen HMACֵ����
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getHmacValue(unsigned int HmacValuebufLen,unsigned char* HmacValue, unsigned int& HmacValueLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : ���ù̼�Ӱ�������Կ�����̼�Ӱ�������Կ�����ڰ�ȫ�洢��
	*       INPUT : FirmwareKey  �̼�Ӱ�������Կ
	*				FirmwareKeyLen �̼�Ӱ�������Կ����Կ����			
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	int setFirmwareKey(const unsigned char* FirmwareKey, const unsigned int FirmwareKeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�̼�Ӱ�������Կ�����̼�Ӱ�������Կ�Ӱ�ȫ�洢���ȡ������
	*       INPUT : ��			
	*      OUTPUT : FirmwareKey  �̼�Ӱ�������Կ
	*               FirmwareKeyLen �̼�Ӱ�������Կ����Կ����
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getFirmwareKey(unsigned int FirmwareKeybufLen,unsigned char* FirmwareKey, unsigned int& FirmwareKeyLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : ������Զ��SPB��ʱ������Զ��SPB��ʱ�����ڰ�ȫ�洢��
	*       INPUT : Time  ��Զ��SPB��ʱ���	
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	//int setprojectorTimevalue(int Timevalue); //modify by yin 2010.5.24//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ��Զ��SPB��ʱ������Զ��SPB��ʱ���Ӱ�ȫ�洢���ȡ������
	*       INPUT : ��			
	*      OUTPUT : Time  ��Զ��SPB��ʱ���	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	//int getprojectorTimevalue(int &Timevalue); //modify by yin 2010.5.24//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���ñ�����sms����smʱ�����ֵ������ֵ�����ڰ�ȫ�洢��
	*       INPUT : Time  ������sms����smʱ�����ֵ
	
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	//int setsmsTimevalue(int Timevalue); //add by yin 2010.5.24//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ������sms����smʱ�����ֵ����������sms����smʱ�����ֵ�Ӱ�ȫ�洢���ȡ������
	*       INPUT : ��			
	*      OUTPUT : Time  ������sms����smʱ�����ֵ
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	//int getsmsTimevalue(int &Timevalue);//add by yin 2010.5.24//del by yin 2011.5.26

	/****FUNCTION***************************************************
	* DESCRIPTION : ����������Կ�ļ�����Կ����������Կ�ļ�����Կ�����ڰ�ȫ�洢��
	*       INPUT : contentkek  ������Կ�ļ�����Կ
	*				contentkekLen ������Կ�ļ�����Կ����Կ����			
	*      OUTPUT :  ��	
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	//int setContentKEK(const unsigned char* contentkek, const unsigned int contentkekLen);//del by yin 2011.5.26

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ������Կ�ļ�����Կ����������Կ�ļ�����Կ�Ӱ�ȫ�洢���ȡ������
	*       INPUT : ��			
	*      OUTPUT : contentkek  ������Կ�ļ�����Կ
	*               contentkekLen ������Կ�ļ�����Կ����Կ����
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ִ��ǰ���Ѿ�ִ����getCSPEncKey����
	****************************************************************/
	//int getContentKEK(unsigned int contentkekbufLen,unsigned char* contentkek, unsigned int& contentkekLen);//del by yin 2011.5.26


	
	/****FUNCTION***************************************************
	* DESCRIPTION : һ����հ�ȫ����(sms����smʱ����ۻ�ֵ�����)
	*       INPUT : ��			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int clearAllCSPs();	

	/****FUNCTION***************************************************
	* DESCRIPTION : ����ȫ����ȫ��������x86�²���֮��--yin 2011.7.20��
	*       INPUT : ��			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int SetAllCSPs(cspinfo_st* cspinfo); //modify by yin 2010.6.2 

	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���ð�ȫ�������������½���ȫ�������õ��������á���x86�²���֮��--yin 2011.7.20��
	*       INPUT : ��			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int reSetAllCSPs();

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡȫ����ȫ������
	*       INPUT : ��			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getAllCSPs(cspinfo_st* cspinfo); //modify by yin 2010.6.2 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��cspinfo_st�ṹ�����ռ䡣
	*       INPUT : cspinfo_st* cspinfo			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	static int newcspinfo_st(cspinfo_st* cspinfo); //modify by yin 2010.7.26 ��Ϊstatic����
	
	/****FUNCTION***************************************************
	* DESCRIPTION : �ͷ�cspinfo_st�ṹ��Ŀռ䡣
	*       INPUT : cspinfo_st* cspinfo			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	static int deletecspinfo_st(cspinfo_st* cspinfo); //modify by yin 2010.7.26	��Ϊstatic����
	
	/****FUNCTION***************************************************
	* DESCRIPTION : getҪУ���֤�����ļ��б�
	*       INPUT : filenamelist �ļ����б�			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int getcachainfiletoverify(vector<string> &filenamelist); //add by yin 2010.6.23	
	
	//add by yin 2010.10.9 start
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�sm֤���ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getsmcertfilename(string &filename); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�sm֤�����ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getsmcachainfile(vector<string> &filenamelist); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�sms֤�����ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getsmscachainfile(vector<string> &filenamelist); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�project֤�����ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getprojectcachainfile(vector<string> &filenamelist);
	
	
 /****FUNCTION***************************************************
	* DESCRIPTION : �����������ļ��еõ���֤�����ļ���
	*       INPUT : calistfile Ҫ�����������ļ��еõ���֤�����ļ���
	*      OUTPUT : calistFileName ֤�����ϵ�֤���ļ��� 
	*     RETURNS : 0��ʾ�ɹ�����0��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/	
	int parsecalistfilename(const char* calistfile, vector<string>& calistFileName);
	//add by yin 2010.10.9 end 
	
	//add by yin 2011.6.14 start
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�user֤���ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getusercertfilename(string &filename); 
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�officer֤���ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getofficercertfilename(string &filename); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�user֤�����ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getusercachainfile(vector<string> &filenamelist); 
	//add by yin 2011.6.14 end
		
	//add by yin 2011.7.20 start
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������ļ��е�officer֤�����ļ�����
	*       INPUT : filename �ļ���			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ǰ�ú���getcachainfiletoverify
	****************************************************************/
	int getofficercachainfile(vector<string> &filenamelist); 
	//add by yin 2011.7.20 end
 
private:	
  	/****FUNCTION***************************************************
	* DESCRIPTION : add crc head
	*       INPUT : puchIndata		
	*      OUTPUT : uchCRCOutData
	*     RETURNS : 0 succeed��or return errnumber��
	*    CAUTIONS : 
	****************************************************************/
	int addCRCHead(const unsigned char* puchIndata,const unsigned long uiIndataLen, unsigned char* uchCRCOutData,unsigned long* uiCRCOutDataLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : verify crc head
	*       INPUT : puchCRCIndata		
	*      OUTPUT : none
	*     RETURNS : 0 succeed��or return errnumber��
	*    CAUTIONS : 
	****************************************************************/
	int verifyCRCHead(const unsigned char* puchCRCIndata, const unsigned long uiCRCIndataLen);
	
	// add by yin 2011.8.2
	/****FUNCTION***************************************************
	* DESCRIPTION : component csp_st value
	*       INPUT : puchIndata CRC32ֵ������ֵ
	*             : uiIndataLen		CRC32ֵ������ֵ���ܳ���
	*      OUTPUT : uchOutData   ����ȫ�洢��cspֵ�洢��ʽ��װ�������
	*   
	*     RETURNS : 0 succeed��or return errnumber��
	*    CAUTIONS : ��ȫ�洢��cspֵ�Ĵ洢��ʽ�����ȣ�2���ֽڣ�ָ����ֵ�ĳ��ȣ�CRC32ֵ������ֵ�ܳ��ȣ�������ֵ��CRC32У��ֵ��4���ֽڣ�������ֵ��
	****************************************************************/
	int componentcspvalue(const unsigned char* puchIndata, const unsigned int uiIndataLen,
	                      unsigned char* uchOutData);
	                      
	/****FUNCTION***************************************************
	* DESCRIPTION : parser csp_st value
	*       INPUT : puchIndata �Ӱ�ȫ�洢���õ�cspֵ�洢��ʽ������
	*             : uiIndataLen		�Ӱ�ȫ�洢���õ�cspֵ�洢��ʽ�����ݵĳ���
	*      OUTPUT : uchOutData  ������õ�����Ч���ݣ�ָ��CRCֵ+����ֵ������Чֵ��
	*             : uiOutDataLen ������õ�����Ч���ݳ���
	*     RETURNS : 0 succeed��or return errnumber��
	*    CAUTIONS : 
	****************************************************************/
	int parsercspvalue(const unsigned char* puchIndata, const unsigned int uiIndataLen,
	                      unsigned char* uchOutData,unsigned int* uiOutDataLen);
 
	int m_ldmpopenflag; 					//Ӳ���洢�򿪱�ʶ
	
	//add by yin 2010.10.9 start
	string m_smcertfilename; 				//sm ֤���ļ���
	vector<string> m_smcafilenamelist;  	//����sm֤�鼰֤�����ļ���
	vector<string> m_smscafilenamelist; 	//����sms֤�����ļ���
	vector<string> m_projectcafilenamelist;	//����project֤�����ļ���
	//add by yin 2010.10.9 end
	
	//add by yin 2011.6.14 start
	string m_usercertfilename; 				//user֤���ļ���
	string m_officercertfilename; 			//officer֤���ļ���
	vector<string> m_usercafilenamelist;	//����user֤�����ļ���
	vector<string> m_officercafilenamelist;	//����officer֤�����ļ���   //add by yin 2011.7.20
	//add by yin 2011.6.14 end
};

#endif
