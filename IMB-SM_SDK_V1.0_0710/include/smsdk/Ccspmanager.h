/*
* Copyright (c) 2007 中国数码
* All rights reserved.
* * 文件名称：Ccsp.h
* 摘    要：关键安全参数类，提供对安全参数的设置，访问及清除操作
* * 当前版本：3.0
* 作    者：yinlifang
** 取代版本：无
* 原作者  ：drm
* 完成日期：2009年12月11日
* 修改日期：2010年5月26日；2010年6月23日；2011年8月2日
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
const unsigned int BUFMAXLINE= 256; 			//ini解析用
//const unsigned int CONTENTKEK_LEN= 16; 		//内容密钥加密密钥的长度 //del by yin 2011.5.26
const unsigned int SEED_LEN= 16; 				//种子的长度
const unsigned int SEEDKEY_LEN= 16; 			//种子密钥的长度
//const unsigned int IV_LEN= 16; 				//IV的长度//del by yin 2011.5.26
const unsigned int FIRMWAREKEY_LEN= 16; 		//固件升级密钥的长度
const unsigned int HMACKEY_LEN= 16; 			//hmac密钥的长度
const unsigned int HMACSHA1_DIGEST_LEN= 20; 	//hmac(sha1)值的长度
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
	u8 userID[30];      //用户ID 			//user ID 
	u8 password[14]; 	//口令base后的值 	//password base64 value
	i32 role;      		//角色值			//role
};
 
struct csps_st{ 
	u8 csps_hmackey[40]; 			//hmac key 实际key值最大可支持32
	u8 csps_hmacvalue[32];			//hmac value 算法固定hmac-sha1，实际大小为20
	u8 csps_deviceprikey[2048];		//private key 私钥，一般为1704
	u8 csps_randseed[40]; 			//rand seed
	u8 csps_seedkey[40];			//seed key	
	u8 csps_firmwarekey[24];		//key for firmware update
	struct user_info uinfo[2]; 		//user information
};


typedef struct cspinfo_st  			//csp信息结构体 add by yin 2010.6.2
{
	u16 csps_hmackeylen;			//hmac密钥长度
	u8* csps_hmackey;				//hmac密钥值
		
	u16 csps_hmacvaluelen;			//hmac值长度
	u8* csps_hmacvalue;				//hmac值，算法固定hmac-sha1，实际大小为20
	
	u16 csps_deviceprikeylen;		//私钥长度
	u8* csps_deviceprikey;			//私钥，一般为1704
	
	u16 csps_randseedlen;			//随机数种子长度
	u8* csps_randseed; 				//随机数种子
	
	u16 csps_seedkeylen;			//种子密钥长度
	u8* csps_seedkey;				//种子密钥
	
	//u16 csps_ivlen;				//iv长度//del by yin 2011.5.26
	//u8* csps_iv;					//iv值//del by yin 2011.5.26
	
	//u16 csps_keklen;				//内容加密密钥长度//del by yin 2011.5.26
	//u8* csps_kek; 				//内容密钥加密密钥，算法固定 AES-128-CFB//del by yin 2011.5.26
	
	u16 csps_firmwarekeylen;		//固件升级密钥长度
	u8* csps_firmwarekey;			//固件升级密钥
	
	//i32 csps_projectortimedvalue;	//sm与projector的时间差,以秒为单位//del by yin 2011.5.26
	//i32 csps_smstimedvalue;		//sms与sm的时间差，以秒为单位，用来做时间调整，保证在一个日历年内(+-)6分钟//del by yin 2011.5.26
};

class Ccspmanager
{
public:	

	Ccspmanager(const int ldmpopenflag=1); //用硬件内存保存csp add by yin 2010.4.7
	~Ccspmanager();	

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置设备私钥
	*       INPUT : Deviceprikey 设备私钥
	*				DeviceprikeyLen 设备私钥长度			
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	int setDeviceprikey(const unsigned char* Deviceprikey, const unsigned int DeviceprikeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取设备私钥
	*       INPUT : DeviceprikeybufLen	已准备的存储设备私钥的空间长度		
	*      OUTPUT : Deviceprikey 设备私钥
	*               DeviceprikeyLen 设备私钥长度
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getDeviceprikey(unsigned int DeviceprikeybufLen,unsigned char* Deviceprikey,  unsigned int& DeviceprikeyLen);	

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置随机数种子（将随机数种子保存在安全存储域）
	*       INPUT : randseed 随机数种子
	*				randseedLen 随机数种子长度		
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	int setRandseed(const unsigned char* randseed, const unsigned int randseedLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取随机数种子（将随机数种子从安全存储域读取出来）
	*       INPUT : randseedbufLen 已开辟的随机数种子空间长度			
	*      OUTPUT : Randseed 随机数种子
	*               randseedLen 随机数种子长度	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getRandseed(unsigned int randseedbufLen, unsigned char* randseed, unsigned int& randseedLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置种子密钥（将种子密钥保存在安全存储域）
	*       INPUT : seedkey 种子密钥
	*				seedkeyLen 种子密钥长度		
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	int setseedkey(const unsigned char* seedkey, const unsigned int seedkeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取种子密钥（将种子密钥从安全存储域读取出来）
	*       INPUT : seedkeybufLen 已开辟的种子密钥空间长度			
	*      OUTPUT : seedkey 种子密钥
	*               seedkeyLen 随机数种子长度	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getseedkey(unsigned int seedkeybufLen, unsigned char* seedkey, unsigned int& seedkeyLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置iv（将iv保存在安全存储域）
	*       INPUT : iv 初始化向量
	*				ivLen 初始化向量长度		
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	//int setIV(const unsigned char* iv, const unsigned int ivLen);//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取iv（将iv从安全存储域读取出来）
	*       INPUT : ivbufLen 已开辟的初始化向量空间长度			
	*      OUTPUT : iv 初始化向量
	*				ivLen 初始化向量长度	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	//int getIV(unsigned int ivbufLen, unsigned char* iv, unsigned int& ivLen);//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置HMAC密钥（将HMAC密钥保存在安全存储域）
	*       INPUT : HmacKey  HMAC密钥
	*				HmacKeyLen HMAC密钥的密钥长度			
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	int setHmacKey(const unsigned char* HmacKey, const unsigned int HmacKeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取HMAC密钥（将HMAC密钥从安全存储域读取出来）
	*       INPUT : 无			
	*      OUTPUT : HmacKey  HMAC密钥
	*               HmacKeyLen HMAC密钥的密钥长度
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getHmacKey(unsigned int HmacKeybufLen,unsigned char* HmacKey, unsigned int& HmacKeyLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置csps的HMAC值（将csps的HMAC值保存在安全存储域）
	*       INPUT : HmacValue  HMAC值
	*				HmacValueLen HMAC值长度			
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	int setHmacValue(const unsigned char* HmacValue, const unsigned int HmacValueLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取csps的HMAC值（将csps的HMAC值从安全存储域读取出来）
	*       INPUT : 无			
	*      OUTPUT : HmacValue  HMAC值
	*               HmacValueLen HMAC值长度
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getHmacValue(unsigned int HmacValuebufLen,unsigned char* HmacValue, unsigned int& HmacValueLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置固件影像解密密钥（将固件影像解密密钥保存在安全存储域）
	*       INPUT : FirmwareKey  固件影像解密密钥
	*				FirmwareKeyLen 固件影像解密密钥的密钥长度			
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	int setFirmwareKey(const unsigned char* FirmwareKey, const unsigned int FirmwareKeyLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取固件影像解密密钥（将固件影像解密密钥从安全存储域读取出来）
	*       INPUT : 无			
	*      OUTPUT : FirmwareKey  固件影像解密密钥
	*               FirmwareKeyLen 固件影像解密密钥的密钥长度
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getFirmwareKey(unsigned int FirmwareKeybufLen,unsigned char* FirmwareKey, unsigned int& FirmwareKeyLen);

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置与远程SPB的时间差（将与远程SPB的时间差保存在安全存储域）
	*       INPUT : Time  与远程SPB的时间差	
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	//int setprojectorTimevalue(int Timevalue); //modify by yin 2010.5.24//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取与远程SPB的时间差（将与远程SPB的时间差从安全存储域读取出来）
	*       INPUT : 无			
	*      OUTPUT : Time  与远程SPB的时间差	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	//int getprojectorTimevalue(int &Timevalue); //modify by yin 2010.5.24//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置本年内sms调节sm时间积累值（将该值保存在安全存储域）
	*       INPUT : Time  本年内sms调节sm时间积累值
	
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	//int setsmsTimevalue(int Timevalue); //add by yin 2010.5.24//del by yin 2011.5.26
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 读取本年内sms调节sm时间积累值（将本年内sms调节sm时间积累值从安全存储域读取出来）
	*       INPUT : 无			
	*      OUTPUT : Time  本年内sms调节sm时间积累值
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	//int getsmsTimevalue(int &Timevalue);//add by yin 2010.5.24//del by yin 2011.5.26

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置内容密钥的加密密钥（将内容密钥的加密密钥保存在安全存储域）
	*       INPUT : contentkek  内容密钥的加密密钥
	*				contentkekLen 内容密钥的加密密钥的密钥长度			
	*      OUTPUT :  无	
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	//int setContentKEK(const unsigned char* contentkek, const unsigned int contentkekLen);//del by yin 2011.5.26

	/****FUNCTION***************************************************
	* DESCRIPTION : 读取内容密钥的加密密钥（将内容密钥的加密密钥从安全存储域读取出来）
	*       INPUT : 无			
	*      OUTPUT : contentkek  内容密钥的加密密钥
	*               contentkekLen 内容密钥的加密密钥的密钥长度
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 执行前需已经执行了getCSPEncKey函数
	****************************************************************/
	//int getContentKEK(unsigned int contentkekbufLen,unsigned char* contentkek, unsigned int& contentkekLen);//del by yin 2011.5.26


	
	/****FUNCTION***************************************************
	* DESCRIPTION : 一次清空安全参数(sms调节sm时间差累积值不清空)
	*       INPUT : 无			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int clearAllCSPs();	

	/****FUNCTION***************************************************
	* DESCRIPTION : 设置全部安全参数。（x86下测试之用--yin 2011.7.20）
	*       INPUT : 无			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int SetAllCSPs(cspinfo_st* cspinfo); //modify by yin 2010.6.2 

	
	/****FUNCTION***************************************************
	* DESCRIPTION : 重置安全参数，即：重新将安全参数设置到出厂设置。（x86下测试之用--yin 2011.7.20）
	*       INPUT : 无			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int reSetAllCSPs();

	/****FUNCTION***************************************************
	* DESCRIPTION : 获取全部安全参数。
	*       INPUT : 无			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getAllCSPs(cspinfo_st* cspinfo); //modify by yin 2010.6.2 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 给cspinfo_st结构体分配空间。
	*       INPUT : cspinfo_st* cspinfo			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	static int newcspinfo_st(cspinfo_st* cspinfo); //modify by yin 2010.7.26 改为static函数
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 释放cspinfo_st结构体的空间。
	*       INPUT : cspinfo_st* cspinfo			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	static int deletecspinfo_st(cspinfo_st* cspinfo); //modify by yin 2010.7.26	改为static函数
	
	/****FUNCTION***************************************************
	* DESCRIPTION : get要校验的证书链文件列表。
	*       INPUT : filenamelist 文件名列表			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int getcachainfiletoverify(vector<string> &filenamelist); //add by yin 2010.6.23	
	
	//add by yin 2010.10.9 start
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的sm证书文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getsmcertfilename(string &filename); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的sm证书链文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getsmcachainfile(vector<string> &filenamelist); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的sms证书链文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getsmscachainfile(vector<string> &filenamelist); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的project证书链文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getprojectcachainfile(vector<string> &filenamelist);
	
	
 /****FUNCTION***************************************************
	* DESCRIPTION : 解析从配置文件中得到的证书链文件名
	*       INPUT : calistfile 要解析从配置文件中得到的证书链文件名
	*      OUTPUT : calistFileName 证书链上的证书文件名 
	*     RETURNS : 0表示成功，非0表示失败
	*    CAUTIONS : NULL
	****************************************************************/	
	int parsecalistfilename(const char* calistfile, vector<string>& calistFileName);
	//add by yin 2010.10.9 end 
	
	//add by yin 2011.6.14 start
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的user证书文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getusercertfilename(string &filename); 
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的officer证书文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getofficercertfilename(string &filename); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的user证书链文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getusercachainfile(vector<string> &filenamelist); 
	//add by yin 2011.6.14 end
		
	//add by yin 2011.7.20 start
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得配置文件中的officer证书链文件名。
	*       INPUT : filename 文件名			
	*      OUTPUT : 无
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 前置函数getcachainfiletoverify
	****************************************************************/
	int getofficercachainfile(vector<string> &filenamelist); 
	//add by yin 2011.7.20 end
 
private:	
  	/****FUNCTION***************************************************
	* DESCRIPTION : add crc head
	*       INPUT : puchIndata		
	*      OUTPUT : uchCRCOutData
	*     RETURNS : 0 succeed，or return errnumber。
	*    CAUTIONS : 
	****************************************************************/
	int addCRCHead(const unsigned char* puchIndata,const unsigned long uiIndataLen, unsigned char* uchCRCOutData,unsigned long* uiCRCOutDataLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : verify crc head
	*       INPUT : puchCRCIndata		
	*      OUTPUT : none
	*     RETURNS : 0 succeed，or return errnumber。
	*    CAUTIONS : 
	****************************************************************/
	int verifyCRCHead(const unsigned char* puchCRCIndata, const unsigned long uiCRCIndataLen);
	
	// add by yin 2011.8.2
	/****FUNCTION***************************************************
	* DESCRIPTION : component csp_st value
	*       INPUT : puchIndata CRC32值和数据值
	*             : uiIndataLen		CRC32值和数据值的总长度
	*      OUTPUT : uchOutData   按安全存储区csp值存储格式组装后的数据
	*   
	*     RETURNS : 0 succeed，or return errnumber。
	*    CAUTIONS : 安全存储区csp值的存储格式：长度（2个字节，指数据值的长度（CRC32值和数据值总长度）＋数据值（CRC32校验值（4个字节）＋数据值）
	****************************************************************/
	int componentcspvalue(const unsigned char* puchIndata, const unsigned int uiIndataLen,
	                      unsigned char* uchOutData);
	                      
	/****FUNCTION***************************************************
	* DESCRIPTION : parser csp_st value
	*       INPUT : puchIndata 从安全存储区得到csp值存储格式的数据
	*             : uiIndataLen		从安全存储区得到csp值存储格式的数据的长度
	*      OUTPUT : uchOutData  解析后得到的有效数据（指：CRC值+数据值，即有效值）
	*             : uiOutDataLen 解析后得到的有效数据长度
	*     RETURNS : 0 succeed，or return errnumber。
	*    CAUTIONS : 
	****************************************************************/
	int parsercspvalue(const unsigned char* puchIndata, const unsigned int uiIndataLen,
	                      unsigned char* uchOutData,unsigned int* uiOutDataLen);
 
	int m_ldmpopenflag; 					//硬件存储打开标识
	
	//add by yin 2010.10.9 start
	string m_smcertfilename; 				//sm 证书文件名
	vector<string> m_smcafilenamelist;  	//保存sm证书及证书链文件名
	vector<string> m_smscafilenamelist; 	//保存sms证书链文件名
	vector<string> m_projectcafilenamelist;	//保存project证书链文件名
	//add by yin 2010.10.9 end
	
	//add by yin 2011.6.14 start
	string m_usercertfilename; 				//user证书文件名
	string m_officercertfilename; 			//officer证书文件名
	vector<string> m_usercafilenamelist;	//保存user证书链文件名
	vector<string> m_officercafilenamelist;	//保存officer证书链文件名   //add by yin 2011.7.20
	//add by yin 2011.6.14 end
};

#endif
