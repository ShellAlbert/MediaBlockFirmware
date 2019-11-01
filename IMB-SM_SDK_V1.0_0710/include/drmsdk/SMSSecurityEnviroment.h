/*
* Copyright (c) 2010 dadimedia.com
* All rights reserved.
* FileName��SMSSecurityEnviroment.h
* Digest  ��sms�İ�ȫ�����࣬��Ҫ�ṩ��ʼ���ͻ�ȡ��ȫ��Ϣ��ؽӿڲ�����
* Version ��1.0
* Author  ��sm
* Date    ��2010.6.4
* Modify  ��2010.9.16 zhangliang �����߲� �����ģ������߲��
* Modify  : 2010.9.19 yinlifang ���ݴ����߲�������������ʵ��޸ġ�
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
	EVP_PKEY*      m_pEVPPriKey;	//EVP��ʽ��˽Կ		
	X509*          m_pleafX509;	  //ʵ��֤��		
	vector<X509*>  m_VecCertchain;//֤���� 	
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
	int Gettrustcachain(vector<X509*>& pvectrustcachain);	 //��ȡ��������,��sm��֤����
	
private:	
		
	vector<X509*> m_trustcachain_sm;     //sm������������sm֤����		
			
	SecInfo_st  m_userSecInfo;  //�û�֤�鼰˽Կ��Ϣ 
	SecInfo_st  m_deviceSecInfo;  //�豸֤�鼰˽Կ��Ϣ
	 
	 //del by yin 2010.7.29
	//const CUserContext m_UserContext;		//������Ϣ 
	
	CPKCS12Info* m_pUserP12Info;			//�û�p12��Ϣ	
	CPKCS12Info* m_pDeviceP12Info;			//�豸p12��Ϣ	
	CPKCS12Info* m_pTLStruastP12Info;			//tls������p12��Ϣ				 
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
	int CreatTLStruastSecurityInfo(const CUserContext& a_DeviceCtx);	 //tls�Զ˵�������
	  		
};

#endif

