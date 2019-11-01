/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* * 文件名称：keymanager.h
* 摘    要：封装密钥管理的相关操作，主要是管理的密钥为以下几类：内容密钥、链路加密密钥及KEK。
* * 当前版本：1.0
* 作    者：yinlifang
** 取代版本：无
* 完成日期：2010年03月19日
*/

#ifndef _KEYMANAGER_H_
#define _KEYMANAGER_H_

#include "smsdk/errornumber.h" 
#include "crypto/arithmatic.h"
#include "crypto/arithtype.h"
//#include "drmsdk/SecurityEnviroment.h"
//#include "harddriver/mb.h" 					
//#include "harddriver/mbdriver_types.h" 		
//#include "harddriver/mbdriver_ioctl.h"		//deleted by sunpeng at 20121205
#include "harddriver/c_spi.h"					//added by sunpeng at 20131205
#include "smsdk/Ccspmanager.h" 


extern const unsigned int KEYTPYE_CONTENTKEY;
extern const unsigned int KEYTPYE_LINKKEY;
//add by yin 2010.7.27 start 
extern const unsigned int LEKEY_LEN; 				//LE密钥长度
extern const unsigned int LEKEY_ATTRIBUTE_LEN;		//LE密钥Attribute长度 add by sun at 2012.06.12
extern const unsigned int LEKEY_EXPIRETIME_VALUE; 	//LE密钥有效期  
extern const unsigned int KEK_LEN; 					//KEK长度
extern const unsigned int SLEEPTIME_VALUE; 			//硬件要求的连续两次访问存储区所需sleep的时间间隔
//add by yin 2010.7.27 end 


class CKeyManager
{
public:
	CKeyManager(struct cspinfo_st cspinfo, const int ldmpopenflag); 

	~CKeyManager();
		
	/****FUNCTION***************************************************
	* DESCRIPTION : 随机数生成
	*       INPUT : reqrandlen 要生成的随机数长度
	*      OUTPUT : rand 生成的随机数	
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int GenerateRand (unsigned int reqrandlen, unsigned char* rand);

	/****FUNCTION***************************************************
	* DESCRIPTION : 生成对称加密密钥，即KEK
	*       INPUT : arith 算法,只支持AES_CFB_Encrypt_128_128
	*      OUTPUT : key
	*             	keylen生成的密钥的长度
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int GenerateKEK (/*unsigned short arith,*/ unsigned char* key,unsigned int& keylen); 

	/****FUNCTION***************************************************
	* DESCRIPTION : 生成LE密钥，只支持生成AES_CTR算法的密钥
	*       INPUT : LEkeynum 需要生成的密钥个数
	*      OUTPUT : LEkeyinfo 多个LEkeyinfo
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int GenerateLEKey (unsigned int LEkeynum, vector<link_key>& LEkeyinfo); 

	/****FUNCTION***************************************************
	* DESCRIPTION : 生成内容解密密钥
	*       INPUT : arithID 算法
	*              	LEkeynum 需要生成的密钥个数
	*      OUTPUT : LEkeyinfo 多个LEkeyinfo
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL 注意，此函数可以不要，因为kdm解析调用set后，密钥管理直接可以load
	****************************************************************/
	int GenerateContentKey(vector<content_key>& Contentkeyinfo); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置内容解密密钥
	*       INPUT : Contentkeyinfo 内容密钥信息	
	*      OUTPUT : 无
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int SetContentKey(vector<content_key> Contentkeyinfo); 
	

	/****FUNCTION***************************************************
	* DESCRIPTION : 内容密钥载入
	*       INPUT : key 要载入的密钥
	*               keylen 载入的密钥长
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int loadContentKey(); 

	/****FUNCTION***************************************************
	* DESCRIPTION : 链接加密密钥载入到安全存储区，给LE
	*       INPUT : key 要载入的密钥
	*               keylen 载入的密钥长
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int loadLEKey(); 
	
#ifdef LEDEMO_TEST
	//add by yin 2010.5.10为测试LEdemo
	/****FUNCTION***************************************************
	* DESCRIPTION : 链接加密密钥载入到安全存储区，给LE
	*       INPUT : key 要载入的密钥
	*               keylen 载入的密钥长
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int loadLEKey(link_key linkkeyinfo); 
#endif

	/****FUNCTION***************************************************
	* DESCRIPTION : 链接解密密钥传给LD
	*       INPUT : 无
	*      OUTPUT : outlink_key 输出经过封装的输出给LD的密钥
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	* //新增－－－密钥load LD密钥－－该密钥是从加密模块输出，传给LD，按密钥输出输入要求，应对此密钥
	            //进行加密，而如何与LD协商该KEK，及LD能否解密需进一步明确。
	****************************************************************/
//	int loadLDKey(vector<link_key>& outlink_key);

	/****FUNCTION***************************************************
	* DESCRIPTION : 密钥载入（载入内容密钥及链接加解密密钥），保留接口，为上述三个函数总和
	*       INPUT : key 要载入的密钥
	*               keylen 载入的密钥长
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int loadallkey (vector<link_key>& outlink_key); 

	/****FUNCTION***************************************************
	* DESCRIPTION : 销毁所有密钥：指所有内容密钥及LE密钥
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	*             : 销毁密钥应包括销毁内容密钥，LE密钥
	****************************************************************/
	int destroyallkey (); 

	/****FUNCTION***************************************************
	* DESCRIPTION : 销毁指定类型的密钥（LEKey或Contentkey）
	*       INPUT : KeyType 要销毁的密钥类型
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int destroyKeybyType (unsigned int KeyType); 	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 销毁指定类型的特定ID的Key
	*       INPUT : KeyType 要销毁的密钥类型
	*               KeyID 要销毁的密钥ID
	*      OUTPUT : NULL
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int destroyKeybyID (unsigned int KeyType, unsigned char* KeyID); 	

	
	/****FUNCTION***************************************************
	* DESCRIPTION : 查询某类型的指定id的密钥信息
	*       INPUT : KeyType 要查询的密钥类型
	*               pKeyID 要查询的密钥id	 
	*      OUTPUT : pKey 查询输出的密钥信息	
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int QueryKeybyID(unsigned int KeyType, unsigned char* pKeyID,unsigned char* pKey);

	/****FUNCTION***************************************************
	* DESCRIPTION : 查询指定类型的所有密钥信息
	*       INPUT : KeyType 要查询的密钥类型	
	*      OUTPUT : pKey 查询后输出的该类型密钥的所有信息	
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int QueryKeyallbyType(unsigned int KeyType,vector<unsigned char*> pKey);
	
	//add by yin 2010.5.10
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置链路加密
	*       INPUT : 无	
	*      OUTPUT : 无
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int setCinelinkEnable(void);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 取消链路加密，禁用cinelink
	*       INPUT : 无	
	*      OUTPUT : 无
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int setCinelinkDisable(void);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 水印生成
	*       INPUT : deviceID 4个字节（8个16进制数）
	*      OUTPUT : fmdata 生成的水印数据	
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int GenerateFMData(unsigned int ideviceID, unsigned char fmdata[5]);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 水印载入
	*       INPUT : fmdata 5个字节（40bit）
	*      OUTPUT : 无
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int LoadFMData (unsigned char fmdata[5]);
	
	
	//add by yin 2011.8.23
	/****FUNCTION***************************************************
	* DESCRIPTION : 水印密钥载入
	*       INPUT : fmkey 16个字节
	*      OUTPUT : 无
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int LoadFMKey (unsigned char fmkey[16]);
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置水印
	*       INPUT : NULL
	*      OUTPUT : BULL	
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int setFMEnable ();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 取消水印
	*       INPUT : NULL
	*      OUTPUT : BULL	
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
//	int setFMDisable ();
	
private:  	
	int m_ldmpopenflag; 						//硬件存储打开标识
	vector<content_key> m_Contentkey;			//存储内容解密密钥列表
//	vector<link_key> m_link_key;				//存储链路密钥信息列表
	cspinfo_st m_cspinfo;						//存储从硬件中获取的csp信息
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 密钥存储
	*       INPUT : key 要存储的密钥
	*               keylen 存储的密钥长
	*               keytype 要存储的密钥类型（根据密钥类型采用不同的存储策略）
	*      OUTPUT : enckey 存储处理后的密钥
	*               enckeylen 存储处理后的密钥长
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int storekey (unsigned char* key, unsigned int keylen); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 计算水印中的时间部分
	*       INPUT : NULL	
	*      OUTPUT : FMtimeData 计算出的水印中的时间值
	*     RETURNS : 0表示成功，-1表示失败
	*    CAUTIONS : NULL
	****************************************************************/
	int calculateFMtimeData(unsigned short& FMtimeData);
};

#endif
