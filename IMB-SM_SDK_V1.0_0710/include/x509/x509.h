/*
* Copyright (c) 2007 dadimedia.com
* All rights reserved.
* 文件名称：x509.h
* 摘    要：解析X509结构体,证书相关操作
* 当前版本：1.0
* 作    者：yinlifang
* 完成日期：2010年06月03日
*/

#ifndef _X509_H_
#define _X509_H_

#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "smsdk/errornumber.h"
#include "crypto/arithmatic.h"

#define Exponent 65537
#define arraylen 512

extern const int FORMAT_DER;
extern const int FORMAT_PEM;

extern const int CERTTYPE_SMS;
extern const int CERTTYPE_SM;
extern const int CERTTYPE_USER;
extern const int CERTTYPE_PROJECTOR;
extern const int CERTTYPE_ENCODER;

using namespace std;

class CX509
{
public:
	/****FUNCTION***************************************************
	* DESCRIPTION : 类默认构造函数
	*       INPUT : 无
	*    CAUTIONS : 无
	****************************************************************/
	CX509();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 析构函数
	*       INPUT : 无
	*    CAUTIONS : 无
	****************************************************************/
	~CX509();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 由文件证书获得x509结构体证书
	*       INPUT : a_pCertfile 要解析的证书（路径及文件名）
	*               a_iCertType 证书编码类型：支持FORMAT_DER及FORMAT_PEM，
	*                           一般用FORMAT_PEM
	*      OUTPUT : pX509 x509结构体
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/	
	int GetX509Cert(const char* a_pCertfile, const int a_iCertType,X509** pX509);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取证书中的公钥
	*       INPUT : pX509 要解析的证书
	*      OUTPUT : a_pPubKey 公钥
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 返回值为不可读信息
	****************************************************************/
	int GetPubKey(X509* pX509,EVP_PKEY** a_pPubKey);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取证书版本号
	*       INPUT : pX509 要解析的证书               
	*      OUTPUT : a_iVersion 版本号
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int GetVersion(X509* pX509,int* a_iVersion);

	//del by yin 2010.7.23
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取证书有效时间
	*       INPUT : pX509 要解析的证书
	*      OUTPUT : a_ppNotBeforeTime 开始有效时间
	*               a_ppNotAfterTime  结束有效时间
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 时间格式是可读的字符串
	****************************************************************/
	//int GetValidityTime(X509* pX509,unsigned char** a_ppNotBeforeTime,unsigned char** a_ppNotAfterTime);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取证书签名算法方式
	*       INPUT : pX509 要解析的证书
	*      OUTPUT : a_pSignType 签名算法
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 返回值是一个int类型，在openssl中有宏可以与算法标识符对应
	****************************************************************/
	int GetSignatrueType(X509* pX509,int* a_pSignType);

	/****FUNCTION***************************************************
	* DESCRIPTION : 获取证书序列号  （日志所用）
	*       INPUT : pX509 要解析的证书
	*      OUTPUT : a_ppSerialNum 证书序列号
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/
	int GetSerialNum(X509* pX509,unsigned char* a_ppSerialNum);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取证书发行者信息  （日志所用）
	*       INPUT : pX509 要解析的证书
	*      OUTPUT : a_pIssuerName 证书发行者信息
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/
	int GetIssuerName(X509* pX509,unsigned char* a_pIssuerName);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数获取指定证书的权威密钥标识
	*       INPUT : pX509 要解析的证书
	*      OUTPUT : a_puchAuthouritykeyId 获取到的证书权威密钥标识
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/
	//int GetAuthorityKeyIdFromCert(X509* pX509,unsigned char* a_puchAuthouritykeyId); 
	//del by yin 2010.6.18 暂时没有用到
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数获取证书指纹                             
	*       INPUT : pX509 指定的证书					        
	*      OUTPUT : a_puchthumbprint 获取到的证书指纹
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/
	static int GetCertthumbprintFromCert(X509* pX509, unsigned char* a_puchthumbprint);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 从X509格式证书中获取证书有效时间
	*       INPUT : pCert X509格式证书
	*      OUTPUT : puchTimeNotBefore 有效开始时间
	*               puchTimeNotAfter  有效结束时间
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int GetX509ValidityTime(X509* pCert, unsigned char* puchTimeNotBefore, unsigned char* puchTimeNotAfter);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数获取证书主题中的dnq
	*       INPUT : pX509 指定的证书				        
	*      OUTPUT : a_puchDnq 获取到的该证书主题dnq
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : a_puchDnq的空间至少57个字节大小（28*2+1）
	****************************************************************/
	static int GetDnqFromCert(X509* pX509,unsigned char* a_puchDnq);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获去证书角色名
	*       INPUT : pX509 X509证书
	*      OUTPUT : pchRolName 角色名
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int get_role(X509* pX509, char* pchRolName);   	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数将指定的证书转换成字符串
	*       INPUT : a_pInputCert 指定的证书
	*      OUTPUT : a_ppOut 获得的字符串
	*				        a_pOutLength 获取字符串的长度
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : a_ppOut 不需要分配内存，openssl负责分配，但是需要free内存
	****************************************************************/
	int CertStructToString(X509* a_pInputCert, unsigned char** a_ppOut, unsigned int* a_pOutLength);

	/****FUNCTION***************************************************
	* DESCRIPTION : 函数将指定的字符串转换成证书
	*       INPUT : a_pIn 指定的字符串
	*				        a_iInLength 指定字符串长度
	*      OUTPUT : a_ppOutCert 获得的证书
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : *a_ppOutCert可以不分配内存，但是必须要回收X509资源
	****************************************************************/
	static int CertStringToStruct(X509** a_ppOutCert, const unsigned char* a_pIn, const unsigned int a_iInLength);
	
	//from x509-430	
	/****FUNCTION***************************************************
	* DESCRIPTION : 加载证书撤销列表
	*       INPUT : crlfile 证书撤销列表
	*               fileformat crl文件编码格式：支持两种FORMAT_DER；FORMAT_PEM
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int load_crlfile(const char* crlfile,int fileformat);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 加载证书链，并对证书链中的证书排序（身份认证验证调用）
	*       INPUT : chainBuf 证书链：pem格式的buffer串
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int load_chainfile(const char* chainBuf);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 加载证书链，并对证书链中的证书排序（sm端初始化调用）
	*       INPUT : certfilename 证书链文件（证书链上证书的含路径的文件名）
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int load_chainfile(vector<unsigned char*> certfilename,int fileType);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 加载证书链，并对证书链中的证书排序（kdm及cpl及pkl签验证、日志签名验证调用）
	*       INPUT : chainBuf 证书链（证书链上证书：base64的证书buffer，没有pem头）
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int load_chainfile(vector<unsigned char*> chainBuf);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置证书类型
	*       INPUT : iCertType 证书类型	            
	*               可选值：CERTTYPE_SMS;CERTTYPE_SM;CERTTYPE_USER;CERTTYPE_PROJECTOR;CERTTYPE_ENCODER; 
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 是SingleCertVerify和do_certformatverify函数的前置函数
	****************************************************************/
	int SetCertType(int iCertType);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 单个证书的格式验证(DCI证书格式符合性验证)
	*       INPUT : pX509 X509格式证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 前置函数：SetCertType(int iCertType)
	****************************************************************/
	int SingleCertVerify(X509* cert);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 证书链中证书的格式验证是否符合SMPTE 430-2
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 前置函数为：SetCertType(int iCertType)
	****************************************************************/
	int do_certformatverify();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 证书链验证
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 前置函数为：do_certformatverify()
	****************************************************************/
	int do_chainverify();	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取排序后根证书
	*       INPUT : 无
	*      OUTPUT : X509结构证书
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	//X509* get_root(); //注意需要按get_leaf修改 2010.6.13 del by yin 2010.7.23
	int get_root(X509** pcert); //add by yin  2010.7.23

	/****FUNCTION***************************************************
	* DESCRIPTION : 获取排序后叶子证书
	*       INPUT : 无
	*      OUTPUT : X509结构证书
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	//X509* get_leaf();	
	int get_leaf(X509** pcert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取排序后取证书链
	*       INPUT : 无
	*      OUTPUT : X509结构证书链
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int get_certlist(vector<X509*>& certlist); 	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 判断是否是CA证书
	*       INPUT : pX509 X509格式证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int X509_check_ca(X509* pX509);		
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 保证使用证书的时间在有效时间内
	*       INPUT : pX509 X509证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
  	int X509_timeValidate_check(X509* pX509);
	
private:
	
	X509* m_root;					// Root certificate
	X509* m_leaf;					// Leaf certificate
	X509_CRL* m_crl;				// Certificate Revocation List
	vector<X509*> m_vecCert;       	// 保存未经排序的证书链
	vector<X509*> m_X509data_list; 	// 保存排好序的证书链（root证书在第一个元素位置）
	STACK_OF(X509)* m_stackChain;  	// Certificate Chain stack
	int m_CertType;                	// 证书类型
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 处理x509的扩展信息
	*       INPUT : px509 证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	void x509v3_cache_extensions(X509* px509);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 对证书链中的证书进行排序
	*       INPUT : vecCert 证书链
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int sort_certlist(vector<X509*> vecCert);	

	/****FUNCTION***************************************************
	* DESCRIPTION : 判断commonName字段是否存在该有的角色
	*       INPUT : 证书commonName字段值             
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	int is_hasrole(const char* commonname);

	/****FUNCTION***************************************************
	* DESCRIPTION : 保证使用证书的时间在有效时间内
	*       INPUT : pX509 X509证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 无
	****************************************************************/
	//int X509_timeValidate_check(X509* pX509);

	/****FUNCTION***************************************************
	* DESCRIPTION : 根据x509结构体的公钥计算公钥指纹
	*       INPUT : pX509 证书	
	*      OUTPUT : p_chDnq 公钥指纹
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/
	int CalculateDnq(X509* pX509,unsigned char* p_chDnq);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 根据RSA公钥转字符串
	*       INPUT : a_pRSAPubKey 公钥	
	*      OUTPUT : a_ppOut 输出字符串公钥
	*               a_pOutLength 字符串公钥长度
	*     RETURNS : 0成功 非0为错误码
	*    CAUTIONS : 
	****************************************************************/
	int PubKeyInToString(RSA* a_pRSAPubKey, unsigned char** a_ppOut, unsigned int* a_pOutLength);
};

#endif
