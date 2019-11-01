/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  P12 file parse
FileName   ： pkcs12info.h
Author     ： yinlifang@dadimedia.com
Date       ： 10/08/03
Version    ： v1.0
Description： P12 file parse
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
      huweihua@dadimedia.com     10/09/14            code walkthrough
********************************************/
#ifndef _PKCS12INFO_H_
#define _PKCS12INFO_H_

#include <iostream>
#include <vector>
using namespace std;

#include <openssl/err.h>
#include <openssl/pkcs12.h>
#include "smsdk/errornumber.h"

class CPKCS12Info
{
public:
	/****FUNCTION***************************************************
	* DESCRIPTION : 默认构造函数
	*       INPUT : a_pPass hash运算使用密码 
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	CPKCS12Info();

	/****FUNCTION***************************************************
	* DESCRIPTION : 构造函数
	*       INPUT : a_pPass hash运算使用密码
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	explicit CPKCS12Info(const char* a_pPass);

	/****FUNCTION***************************************************
	* DESCRIPTION : 析构函数
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	virtual ~CPKCS12Info();

	//del by yin 2009.5.18 end
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数在构建出类对象之后，必须调用的函数
	*       INPUT : a_pP12FileName p12文件名
	*				a_iEncodeType 加密数据的编码方式
	*      OUTPUT : 无
	*     RETURNS : 1 成功， 0 失败
	*    CAUTIONS : 无
	****************************************************************/	
	int ParseP12(const char* a_pP12FileName,bool tlsp12flag = false, const int a_iEncodeType = NID_pkcs7_data);	

	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数获取证书信任链数据
	*       INPUT : a_pVecCaCertList 证书信任链
	*      OUTPUT : 无
	*     RETURNS : 1 成功， 0 失败
	*    CAUTIONS : 无
	****************************************************************/		
	int GetCaCert(vector<X509*>* a_pVecCaCertList,bool tlsp12flag = false);
	

	/****FUNCTION***************************************************
	* DESCRIPTION : 函数获取实体证书
	*       INPUT : 无
	*      OUTPUT : a_ppSubCert 获取到的实体证书
	*     RETURNS : 1 成功， 0 失败
	*    CAUTIONS : 无
	****************************************************************/
	int GetSubCert(X509** a_ppSubCert);

	/****FUNCTION***************************************************
	* DESCRIPTION : 实体证书对应私钥
	*       INPUT : 无
	*      OUTPUT : a_ppSubKey 获取到的实体证书私钥
	*     RETURNS : 1 成功， 0 失败
	*    CAUTIONS : 无
	****************************************************************/
	int GetSubKey(EVP_PKEY** a_ppSubKey);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 函数设置hash运算使用的密码
	*       INPUT : a_pPassWord hash运算密码
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	void SetPassWord(const unsigned char* a_pPassWord);

private:
		
	EVP_PKEY* m_pKey;						//实体证书私钥信息
	X509* m_pCert;							//实体证书		
	vector<X509*> m_vecCaCertList;          //保存信任证书链数据
	vector<X509*> m_vecTlsP12CaCertList;	//保存用于tls建立的设备证书的信任证书链数据
	char m_pPass[1024];				        //p12密码
};

#endif
