/*
* Copyright (c) 2010 dadimedia.com
* All rights reserved.
* FileName：SMSSecurityEnviroment.h
* Digest  ：sms的安全环境类，主要提供初始化和获取安全信息相关接口操作。
* Version ：1.0
* Author  ：sm
* Date    ：2010.6.4
* Modify  ：2010.9.16 zhangliang 代码走查 详见该模块代码走查表
* Modify  : 2010.9.19 yinlifang 根据代码走查意见，进行了适当修改。
*/

#ifndef _SECURITYENVIROMENT_H_
#define _SECURITYENVIROMENT_H_

#include "x509/x509.h"
#include "p12/pkcs12info.h"
#include "drmsdk/UserContext.h" 

#define MAX_NODE_LEN 4096
extern const char* USER_CERT;
extern const char* DEVICE_CERT;

typedef struct SecInfo_st
{
	EVP_PKEY*      m_pEVPPriKey;	//EVP格式的私钥		
	X509*          m_pleafX509;	  //实体证书		
	vector<X509*>  m_VecCertchain;//证书链 	
};

class CSMSSecEnviroment
{	
public:			
	/****FUNCTION***************************************************
	* DESCRIPTION : constructor
	*       INPUT : a_UserCtx	-	user info
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : none
	****************************************************************/
	//CSMSSecEnviroment(const CUserContext& a_UserCtx);	del by yin 2010.7.29
	
	//add by yin 2010.7.29
	/****FUNCTION***************************************************
	* DESCRIPTION : constructor
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : none
	****************************************************************/
	CSMSSecEnviroment();	
	
	/****FUNCTION***************************************************
	* DESCRIPTION :destructor
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : none
	****************************************************************/
	~CSMSSecEnviroment();    
	/****FUNCTION***************************************************
	* DESCRIPTION : initialize security environment
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/	
	//int Initialize();		//DEL by yin 2010.7.29
	
	//add by yin 2010.7.29 start 
	/****FUNCTION***************************************************
	* DESCRIPTION : initialize device security environment
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/	
	int DeviceSecInitialize(const CUserContext& a_DeviceCtx);		
	
	/****FUNCTION***************************************************
	* DESCRIPTION : initialize user security environment
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/	
	int UserSecInitialize(const CUserContext& a_UserCtx);
	//add by yin 2010.7.29 end 		
	
	/****FUNCTION***************************************************
	* DESCRIPTION : get leaf certificate by type
	*       INPUT : a_pPuchType	-	certificate type (USER_CERT|DEVICE_CERT)
	*      OUTPUT : a_ppCert	-	certificate pointer
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int GetCertificateByType(const unsigned char* a_pPuchType, X509** a_ppCert)const;		
	/****FUNCTION***************************************************
	* DESCRIPTION : get CA list by type
	*       INPUT : a_pPuchType	-	certificate type (USER_CERT|DEVICE_CERT)
	*      OUTPUT : VecCertList	-	CA list
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int GetCertListByType(const unsigned char* a_pPuchType , vector<X509*>& VecCertList)const;
	/****FUNCTION***************************************************
	* DESCRIPTION : get private key by type 
	*       INPUT : a_pPuchType	-	certificate type (USER_CERT|DEVICE_CERT)
	*      OUTPUT : a_ppKey		-	private key pointer
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int GetPrivateKeyByType(const unsigned char* a_pPuchType , EVP_PKEY** a_ppKey)const;
	/****FUNCTION***************************************************
	* DESCRIPTION : get trusted CA list
	*       INPUT : none
	*      OUTPUT : pvectrustcachain	-	CA list
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int Gettrustcachain(vector<X509*>& pvectrustcachain);	 //获取受信任链,即sm的证书链
	
private:	
		
	vector<X509*> m_trustcachain_sm;     //sm受信任链，即sm证书链		
			
	SecInfo_st  m_userSecInfo;  //用户证书及私钥信息 
	SecInfo_st  m_deviceSecInfo;  //设备证书及私钥信息
	 
	 //del by yin 2010.7.29
	//const CUserContext m_UserContext;		//配置信息 
	
	CPKCS12Info* m_pUserP12Info;			//用户p12信息	
	CPKCS12Info* m_pDeviceP12Info;			//设备p12信息	
	CPKCS12Info* m_pTLStruastP12Info;			//tls信任链p12信息				 
	/****FUNCTION***************************************************
	* DESCRIPTION : parse user p12 file and set m_userSecInfo
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int CreatUserSecurityInfo(const CUserContext& a_UserCtx);
	/****FUNCTION***************************************************
	* DESCRIPTION : parse devide p12 file and set m_deviceSecInfo
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int CreatDeviceSecurityInfo(const CUserContext& a_DeviceCtx);	
	/****FUNCTION***************************************************
	* DESCRIPTION : parse trusted CA P12 file and set m_trustcachain_sm
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/
	int CreatTLStruastSecurityInfo(const CUserContext& a_DeviceCtx);	 //tls对端的信任链
	  		
};

#endif

