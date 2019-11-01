/*
* Copyright (c) 2007 dadimedia
* All rights reserved.
* �ļ����ƣ�arithmatic.h
* ժ    Ҫ���㷨������:�ṩ���½ӿڣ�
*                      �ǶԳƼӽ��ܡ�ǩ������֤��
*                      �ԳƼӽ���;
*                      hash���㡢CRC32����;
*                      ���������;
*                      ������ԿID;
*                      base64����롣
* ��ǰ�汾��1.0
* ��    �ߣ�sm
* ������ڣ�2010.6.3
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

//�㷨������
class CArithMatic
{
public:
	
	//rsa��Կ�ַ���תRSA�ṹ��
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ָ�����ַ���ת���ɹ�Կ
	*       INPUT : a_ppRSAPubKey ��õĹ�Կ
	*				a_pIn ָ�����ַ���
	*				a_iInLength ָ���ַ�������
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : a_ppRSAPubKey ����Ҫ���ⲿ�����ڴ棬����Ҫ�ͷ���Դ
	*				����rsaд��evpkey������Ҫ�ͷ���Դ
	****************************************************************/
	static int PubKeyStringToIn(RSA** a_ppRSAPubKey, const unsigned char* a_pIn, const unsigned int a_iInLength);
	
	//rsa˽Կ�ַ���תRSA�ṹ��
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ָ�����ַ���ת����˽Կ
	*       INPUT : a_ppRSAPriKey ��õ�˽Կ
	*				a_pIn ָ�����ַ���
	*				a_iInLength ָ���ַ�������
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : a_ppRSAPriKey ����Ҫ���ⲿ�����ڴ棬����Ҫ�ͷ���Դ
	*				����rsaд��evpkey������Ҫ�ͷ���Դ
	****************************************************************/
	static int PriKeyStringToIn(RSA** a_ppRSAPriKey, const unsigned char* a_pIn, const unsigned int a_iInLength);

  
	/****FUNCTION***************************************************
	* DESCRIPTION : rsa��Կ����   
	*       INPUT : a_pInData ��������ܵ�����
	*				        a_iInDataLen �������ݳ���
	*				        pPubKey ��Կ
	*               a_iInRSAPaddingMod ���ģʽ	
	*      OUTPUT : a_pOutData ������ܺ�����
	*				        a_pOutDataLen ������ݳ���
	*     RETURNS : 0�ɹ���-1ʧ��
	*    CAUTIONS : �ú���ֻΪ����˽Կ����֮�ã�ʵ����Ŀû���øú���
	****************************************************************/
	static int ArithRSAPubKeyEnc(const unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, const EVP_PKEY* pPubKey,int a_iInRSAPaddingMod = RSA_PKCS1_PADDING);	

	
	/****FUNCTION***************************************************
	* DESCRIPTION : rsa˽Կ����
	*       INPUT : a_pInData ��������ܵ�����
	*				        a_iInDataLen �������ݳ���
	*				        a_pPriKey ˽Կ	
	*				        a_iInRSAPaddingMod rsa���ģʽ
	*      OUTPUT : a_pOutData ������ܺ�����
	*				        a_pOutDataLen ������ݳ���
	*     RETURNS : 0�ɹ���-1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithRSAPriKeyDec(const unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, const EVP_PKEY* pPriKey, int a_iInRSAPaddingMod = RSA_PKCS1_PADDING);	
	
		
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ָ����������ǩ��
	*       INPUT : a_pSourceData ��Ҫ��ǰǩ��������
	*				        a_iSourceDataLen ǩ�����ݳ���
	*				        a_iArithID �㷨id
	*				        a_pPriKey ǩ��˽Կ			
	*      OUTPUT : a_pDesData ǩ��������
	*				        a_pDesDataLen ǩ�������ݳ���
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithSign(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		unsigned char* a_pDesData, unsigned int* a_pDesDataLen, const unsigned int a_iArithID, EVP_PKEY* a_pPriKey);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������֤ǩ��
	*       INPUT : a_pSourceData ����ǩ����ԭʼ����
	*				        a_iSourceDataLen ԭʼ���ݳ���
	*				        a_iArithID �㷨id
	*				        a_pPubKey ��֤ǩ����Կ		
	*      OUTPUT : a_pDesData ǩ��������
	*				        a_pDesDataLen ǩ�������ݳ���
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithVerify(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		const unsigned char* a_pDesData, const unsigned int a_iDesDataLen, const unsigned int a_iArithID, EVP_PKEY* a_pPubKey);


  	/****FUNCTION***************************************************
	* DESCRIPTION : ����ʵ�ֶԳƼ��ܵ������㷨
	*       INPUT : a_pInData ����������
	*				        a_iInDataLen �������ݳ���
	*				        a_pKey evpʹ�õĶԳƼ�����Կ
	*				        a_pIV �ԳƼ���ʹ�õ�����
	*				        a_iFlag ָʾ���ܽ��� 1 ���� 0����	
	*				        a_pType �ԳƼ��ܷ�ʽ 
	*      OUTPUT : a_pOutData ���ܺ�����
	*				        a_pOutDataLen ���ܺ����ݳ���
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithSymmetric(const unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, int a_iFlag, const EVP_CIPHER* a_pType, const unsigned char* a_pKey, const unsigned char* a_pIV = SYMMETRIC_IV);
		

	/****FUNCTION***************************************************
	* DESCRIPTION : ����ʵ��hash����
	*       INPUT : a_pInData ����������
	*				        a_iInDataLen �������ݳ���
	*				        a_pMD hash���㷽ʽ
	*      OUTPUT : a_pOutData ���������
	*				        a_pDesDataLen ��������ݳ���
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithHash(unsigned char* a_pInData, const unsigned int a_iInDataLen,
		unsigned char* a_pOutData, unsigned int* a_pOutDataLen, const EVP_MD* a_pMD);
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������������base64ת��
	*       INPUT : a_pSourceData ���������ԭʼ����
	*				        a_iSourceDataLen ԭʼ���ݳ���	
	*      OUTPUT : a_pDesData ���������
	*				        a_pDesDataLen ��������ݳ���	
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithBase64Enc(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		unsigned char* a_pDesData, unsigned int* a_pDesDataLen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������������base64����
	*       INPUT : a_pSourceData ���������ԭʼ����
	*				        a_iSourceDataLen ԭʼ���ݳ���	
	*      OUTPUT : a_pDesData ���������
	*				        a_pDesDataLen ��������ݳ���	
	*     RETURNS : 0�ɹ� -1ʧ��
	*    CAUTIONS : 
	****************************************************************/
	static int ArithBase64Dec(const unsigned char* a_pSourceData, const unsigned int a_iSourceDataLen,
		unsigned char* a_pDesData, unsigned int* a_pDesDataLen);
	

	/****FUNCTION***************************************************
	* DESCRIPTION : ��Կ��������
	*       INPUT : a_iArithID �㷨��ʶ
	*				        a_pInData ��������
	*				        a_iInDataLen �������ݳ���
	*				        a_pKey key����
	*				        a_iKeyLen key���ݳ���
	*      OUTPUT : a_pPuchOut �������
	*				        a_puiOutLen ������ݳ���
	*     RETURNS : 0�ɹ� 1ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	static int Arith(const unsigned int a_iArithID, const unsigned char* a_pInData, const unsigned int a_iInDataLen, 
		unsigned char* a_pOutData, unsigned int* a_pOutLen,
		const unsigned char* a_pKey = NULL, const unsigned int a_iKeyLen = 0);

	
	//����fips_rand.h�����������㷨��aes��
	/****FUNCTION***************************************************	
	* DESCRIPTION : ��������ɣ������ṩ�����Ӻ�������Կ����ָ�����ȵ������
	*       INPUT : seed ����
	*				        seedlen�����ӳ���
	*				        seedkey��������Կ
	*				        seedkeylen��������Կ����
	*				        randlen��Ҫ���ɵ�rand����
	*      OUTPUT : rand ���ɵ������
	*     RETURNS : 0�ɹ� 1ʧ��
	*    CAUTIONS : ��
	**************************************/
	static int GenRand(unsigned char* seed,int seedlen,unsigned char* seedkey,int seedkeylen,unsigned int randlen, unsigned char* rand);


  	/****FUNCTION***************************************************
	* DESCRIPTION : ������ԿID���ṩLEkey����ԿID��
	*      OUTPUT : KeyID ���ɵ�KeyID�ַ���	
	*     RETURNS : 0��ʾ�ɹ�����0Ϊ������
	*    CAUTIONS : ���ֵΪ4096
	**************************************/
	static int GenerateKeyID(unsigned int* KeyID);
	

	/****FUNCTION***************************************************
	* DESCRIPTION : crc32����
	*       INPUT : buffer Ҫ����crc32��buf
	*               bufferlen buffer�ĳ���	
	*      OUTPUT : �� 
	*     RETURNS : crcУ����
	*    CAUTIONS : NULL
	****************************************************************/
 	static unsigned long crc32(const char* buffer, const unsigned long bufferlen);
 
 	/****FUNCTION***************************************************
	* DESCRIPTION : hmac���㣨hmac��sha1��128���Ա�csp��ʱ��ֵ�������Լ���
	*       INPUT : a_pMD ժҪ�㷨,֧��sha1
	*               Key hmac��Կ
	*               Keylen hmac��Կ����
	*               Msg Ҫ����ժҪ���������
	*	              Msglen Ҫ����ժҪ��������ݵ��ֽڳ���
	*      OUTPUT : HMACvalue �������hmacֵ
	*               HMACvaluelen �������hmacֵ�ĳ��� 
	*     RETURNS : crcУ����
	*    CAUTIONS : NULL
	****************************************************************/
 	static unsigned int ArithHMAC(const EVP_MD* a_pMD, const unsigned char* Key, unsigned int Keylen, 
                               const unsigned char* Msg, unsigned int Msglen, 
                               unsigned char* HMACvalue,	unsigned int& HMACvaluelen); 
                               
	/****FUNCTION***************************************************
	* DESCRIPTION : hmac���㣨hmac��sha1��128��
	*       INPUT : a_pMD ժҪ�㷨,֧��sha1
	*               Key hmac��Կ
	*               Keylen hmac��Կ����
	*               filenamelist Ҫ����ժҪ���ļ����б�
	*      OUTPUT : HMACvalue �������hmacֵ
	*               HMACvaluelen �������hmacֵ�ĳ��� 
	*     RETURNS : crcУ����
	*    CAUTIONS : NULL
	****************************************************************/
 	static unsigned int ArithHMAC(const EVP_MD* a_pMD, const unsigned char* Key, unsigned int Keylen, 
                               vector<string>& filenamelist, 
                               unsigned char* HMACvalue,	unsigned int& HMACvaluelen); 
 
  	/****FUNCTION***************************************************
	* DESCRIPTION : hmac key���ɼ���
	*       INPUT : key ����hmac key���õ���Կֵ
	*               keyLen ����hmac key���õ���Կֵ�ĳ���	
	*      OUTPUT : hmacKey ���ɳ���hmacKeyֵ���䳤��ΪhmacKeyֵ�ĳ���
	*     RETURNS : NULL
	*    CAUTIONS : NULL
	****************************************************************/                            
  	static void InitSMPTEHMACKey(const unsigned char* key, 
					             unsigned long keyLen,
					             unsigned char *hmacKey);

	/****FUNCTION***************************************************	
	* DESCRIPTION : RSA��Կ�����ɣ�����ָ���Ĺ�Կ����e����Կ���ȣ�����RSA��Կ��
	*       INPUT : bits: ������RSA��Կ�ĳ��ȣ���λΪ����
	*				pubExp����Կe��ֵ
	*      OUTPUT : privateKey ���ɵ�pem�����˽Կ
	*				pPrivateKeyLen ���ɵ�pem�����˽Կ�ĳ���
	*     RETURNS : 0�ɹ� 1ʧ��
	*    CAUTIONS : ��
	**************************************/
	static int GenRSAX931(const int bits,
							const unsigned long exp,
							unsigned char* privateKey,
							int* pPrivateKeyLen);

	/****FUNCTION***************************************************	
	* DESCRIPTION : ֤���������������ָ����RSA��Կ������֤������
	*       INPUT : privateKey: pem�����RSA��Կ
	*				privateKeyLen��RSA��Կ����
	*				deviceSN���豸���кţ��ַ���
	*      OUTPUT : certReq ���ɵ�pem�����֤������
	*				pCertReqLen ֤������ĳ���
	*     RETURNS : 0�ɹ� 1ʧ��
	*    CAUTIONS : ��
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
