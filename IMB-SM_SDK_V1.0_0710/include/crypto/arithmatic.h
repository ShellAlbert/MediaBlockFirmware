/*
* Copyright (c) 2007 dadimedia
* All rights reserved.
* 文件名称：arithmatic.h
* 摘    要：算法核心类:提供以下接口：
*                      非对称加解密、签名及验证；
*                      对称加解密;
*                      hash计算、CRC32计算;
*                      生成随机数;
*                      生成密钥ID;
*                      base64编解码。
* 当前版本：1.0
* 作    者：sm
* 完成日期：2010.6.3
*/

#ifndef _ARITHMATIC_H_
#define _ARITHMATIC_H_

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#include <openssl/engine.h>
#include <openssl/ssl.h>
#include <openssl/aes.h> 
#include <openssl/fips.h>
#include <openssl/fips_rand.h>
#include <openssl/bn.h>
#include "crypto/arithtype.h"
#include "smsdk/errornumber.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
#define SHA_DIGEST_LENGTH 20
extern const unsigned char* SYMMETRIC_IV;
extern unsigned int m_LEkeyid; 
extern unsigned long crc32_table[256];

//算法核心类
class CArithMatic
{
public:
	
	//rsa公钥字符串转RSA结构体
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数将指定的字符串转换成公钥
	*       INPUT : a_ppRSAPubKey 获得的公钥
	*				a_pIn 指定的字符串
	*				a_iInLength 指定字符串长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : a_ppRSAPubKey 不需要在外部分配内存，但需要释放资源
	*				当将rsa写入evpkey中则不需要释放资源
	****************************************************************/
	static int PubKeyStringToIn(RSA** a_ppRSAPubKey, const unsigned char* a_pIn, const unsigned int a_iInLength);
	
	//rsa私钥字符串转RSA结构体
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数将指定的字符串转换成私钥
	*       INPUT : a_ppRSAPriKey 获得的私钥
	*				a_pIn 指定的字符串
	*				a_iInLength 指定字符串长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : a_ppRSAPriKey 不需要在外部分配内存，但需要释放资源
	*				当将rsa写入evpkey中则不需要释放资源
	****************************************************************/
	static int PriKeyStringToIn(RSA** a_ppRSAPriKey, const unsigned char* a_pIn, const unsigned int a_iInLength);

  
	/****FUNCTION***************************************************
	* DESCRIPTION : rsa公钥加密   
	*       INPUT : a_pInData 输入待加密的数据
	*				        a_iInDataLen 输入数据长度
	*				        pPubKey 公钥
	*               a_iInRSAPaddingMod 填充模式	
	*      OUTPUT : a_pOutData 输出加密后数据
	*				        a_pOutDataLen 输出数据长度
	*     RETURNS : 0成功，-1失败
	*    CAUTIONS : 该函数只为测试私钥解密之用，实际项目没有用该函数
	****************************************************************/
	static int ArithRSAPubKeyEnc(const unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, const EVP_PKEY* pPubKey,int a_iInRSAPaddingMod = RSA_PKCS1_PADDING);	

	
	/****FUNCTION***************************************************
	* DESCRIPTION : rsa私钥解密
	*       INPUT : a_pInData 输入待解密的数据
	*				        a_iInDataLen 输入数据长度
	*				        a_pPriKey 私钥	
	*				        a_iInRSAPaddingMod rsa填充模式
	*      OUTPUT : a_pOutData 输出解密后数据
	*				        a_pOutDataLen 输出数据长度
	*     RETURNS : 0成功，-1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithRSAPriKeyDec(const unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, const EVP_PKEY* pPriKey, int a_iInRSAPaddingMod = RSA_PKCS1_PADDING);	
	
		
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数对指定的数据作签名
	*       INPUT : a_pSourceData 需要作前签名的数据
	*				        a_iSourceDataLen 签名数据长度
	*				        a_iArithID 算法id
	*				        a_pPriKey 签名私钥			
	*      OUTPUT : a_pDesData 签名后数据
	*				        a_pDesDataLen 签名后数据长度
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithSign(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		unsigned char* a_pDesData, unsigned int* a_pDesDataLen, const unsigned int a_iArithID, EVP_PKEY* a_pPriKey);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数验证签名
	*       INPUT : a_pSourceData 被做签名的原始数据
	*				        a_iSourceDataLen 原始数据长度
	*				        a_iArithID 算法id
	*				        a_pPubKey 验证签名公钥		
	*      OUTPUT : a_pDesData 签名后数据
	*				        a_pDesDataLen 签名后数据长度
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithVerify(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		const unsigned char* a_pDesData, const unsigned int a_iDesDataLen, const unsigned int a_iArithID, EVP_PKEY* a_pPubKey);


  	/****FUNCTION***************************************************
	* DESCRIPTION : 函数实现对称加密的所有算法
	*       INPUT : a_pInData 被加密数据
	*				        a_iInDataLen 加密数据长度
	*				        a_pKey evp使用的对称加密密钥
	*				        a_pIV 对称加密使用的向量
	*				        a_iFlag 指示加密解密 1 加密 0解密	
	*				        a_pType 对称加密方式 
	*      OUTPUT : a_pOutData 加密后数据
	*				        a_pOutDataLen 加密后数据长度
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithSymmetric(const unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, int a_iFlag, const EVP_CIPHER* a_pType, const unsigned char* a_pKey, const unsigned char* a_pIV = SYMMETRIC_IV);
		

	/****FUNCTION***************************************************
	* DESCRIPTION : 函数实现hash运算
	*       INPUT : a_pInData 被处理数据
	*				        a_iInDataLen 处理数据长度
	*				        a_pMD hash运算方式
	*      OUTPUT : a_pOutData 处理后数据
	*				        a_pDesDataLen 处理后数据长度
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithHash(unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, const EVP_MD* a_pMD);
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数对数据作base64转码
	*       INPUT : a_pSourceData 被做编码的原始数据
	*				        a_iSourceDataLen 原始数据长度	
	*      OUTPUT : a_pDesData 编码后数据
	*				        a_pDesDataLen 编码后数据长度	
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithBase64Enc(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		unsigned char* a_pDesData, unsigned int* a_pDesDataLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数对数据作base64解码
	*       INPUT : a_pSourceData 被做解码的原始数据
	*				        a_iSourceDataLen 原始数据长度	
	*      OUTPUT : a_pDesData 解码后数据
	*				        a_pDesDataLen 解码后数据长度	
	*     RETURNS : 0成功 -1失败
	*    CAUTIONS : 
	****************************************************************/
	static int ArithBase64Dec(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		unsigned char* a_pDesData, unsigned int* a_pDesDataLen);
	

	/****FUNCTION***************************************************
	* DESCRIPTION : 公钥解密数据
	*       INPUT : a_iArithID 算法标识
	*				        a_pInData 输入数据
	*				        a_iInDataLen 输入数据长度
	*				        a_pKey key数据
	*				        a_iKeyLen key数据长度
	*      OUTPUT : a_pPuchOut 输出数据
	*				        a_puiOutLen 输出数据长度
	*     RETURNS : 0成功 1失败
	*    CAUTIONS : 无
	****************************************************************/
	static int Arith(const unsigned int a_iArithID, const unsigned char* a_pInData, const unsigned int a_iInDataLen, 
		unsigned char* a_pOutData, unsigned int* a_pOutLen,
		const unsigned char* a_pKey = NULL, const unsigned int a_iKeyLen = 0);

	
	//调用fips_rand.h（核心生成算法是aes）
	/****FUNCTION***************************************************	
	* DESCRIPTION : 随机数生成：根据提供的种子和种子密钥生成指定长度的随机数
	*       INPUT : seed 种子
	*				        seedlen：种子长度
	*				        seedkey：种子密钥
	*				        seedkeylen：种子密钥长度
	*				        randlen：要生成的rand长度
	*      OUTPUT : rand 生成的随机数
	*     RETURNS : 0成功 1失败
	*    CAUTIONS : 无
	**************************************/
	static int GenRand(unsigned char* seed,int seedlen,unsigned char* seedkey,int seedkeylen,unsigned int randlen, unsigned char* rand);


  	/****FUNCTION***************************************************
	* DESCRIPTION : 生成密钥ID（提供LEkey的密钥ID）
	*      OUTPUT : KeyID 生成的KeyID字符串	
	*     RETURNS : 0表示成功，非0为错误码
	*    CAUTIONS : 最大值为4096
	**************************************/
	static int GenerateKeyID(unsigned int* KeyID);
	

	/****FUNCTION***************************************************
	* DESCRIPTION : crc32计算
	*       INPUT : buffer 要计算crc32的buf
	*               bufferlen buffer的长度	
	*      OUTPUT : 无 
	*     RETURNS : crc校验码
	*    CAUTIONS : NULL
	****************************************************************/
 	static unsigned long crc32(const char* buffer, const unsigned long bufferlen);
 
 	/****FUNCTION***************************************************
	* DESCRIPTION : hmac计算（hmac－sha1－128）以备csp中时间值的完整性计算
	*       INPUT : a_pMD 摘要算法,支持sha1
	*               Key hmac密钥
	*               Keylen hmac密钥长度
	*               Msg 要进行摘要计算的内容
	*	              Msglen 要进行摘要计算的内容的字节长度
	*      OUTPUT : HMACvalue 计算出的hmac值
	*               HMACvaluelen 计算出的hmac值的长度 
	*     RETURNS : crc校验码
	*    CAUTIONS : NULL
	****************************************************************/
 	static unsigned int ArithHMAC(const EVP_MD* a_pMD, const unsigned char* Key, unsigned int Keylen, 
                               const unsigned char* Msg, unsigned int Msglen, 
                               unsigned char* HMACvalue,	unsigned int& HMACvaluelen); 
                               
	/****FUNCTION***************************************************
	* DESCRIPTION : hmac计算（hmac－sha1－128）
	*       INPUT : a_pMD 摘要算法,支持sha1
	*               Key hmac密钥
	*               Keylen hmac密钥长度
	*               filenamelist 要计算摘要的文件名列表
	*      OUTPUT : HMACvalue 计算出的hmac值
	*               HMACvaluelen 计算出的hmac值的长度 
	*     RETURNS : crc校验码
	*    CAUTIONS : NULL
	****************************************************************/
 	static unsigned int ArithHMAC(const EVP_MD* a_pMD, const unsigned char* Key, unsigned int Keylen, 
                               vector<string>& filenamelist, 
                               unsigned char* HMACvalue,	unsigned int& HMACvaluelen); 
 
  	/****FUNCTION***************************************************
	* DESCRIPTION : hmac key生成计算
	*       INPUT : key 生成hmac key所用的密钥值
	*               keyLen 生成hmac key所用的密钥值的长度	
	*      OUTPUT : hmacKey 生成出的hmacKey值，其长度为hmacKey值的长度
	*     RETURNS : NULL
	*    CAUTIONS : NULL
	****************************************************************/                            
  	static void InitSMPTEHMACKey(const unsigned char* key, 
					             unsigned long keyLen,
					             unsigned char *hmacKey);

	/****FUNCTION***************************************************	
	* DESCRIPTION : RSA密钥对生成：根据指定的公钥参数e及密钥长度，生成RSA密钥对
	*       INPUT : bits: 产生的RSA密钥的长度，单位为比特
	*				pubExp：公钥e的值
	*      OUTPUT : privateKey 生成的pem编码的私钥
	*				pPrivateKeyLen 生成的pem编码的私钥的长度
	*     RETURNS : 0成功 1失败
	*    CAUTIONS : 无
	**************************************/
	static int GenRSAX931(const int bits,
							const unsigned long exp,
							unsigned char* privateKey,
							int* pPrivateKeyLen);

	/****FUNCTION***************************************************	
	* DESCRIPTION : 证书请求产生：根据指定的RSA密钥，产生证书请求
	*       INPUT : privateKey: pem编码的RSA密钥
	*				privateKeyLen：RSA密钥长度
	*				deviceSN：设备序列号，字符串
	*      OUTPUT : certReq 生成的pem编码的证书请求
	*				pCertReqLen 证书请求的长度
	*     RETURNS : 0成功 1失败
	*    CAUTIONS : 无
	**************************************/
	static int GenRsaCertReq(const unsigned char* privateKey,
								const int privateKeyLen,
								const char* deviceSN,
								unsigned char* certReq,
								int* pCertReqLen);
private:
  	static void Gen_FIPS_186_Value(const unsigned char* key, 
						             unsigned long key_size, 
						             unsigned char* out_buf, 
						             unsigned long out_buf_len);
						             
 	static unsigned long Swap4(unsigned long i);
 	
	static int genrsa_cb(int p, int n, BN_GENCB *cb);
};

#endif
