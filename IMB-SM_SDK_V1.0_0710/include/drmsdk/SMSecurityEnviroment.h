/*
* Copyright (c) 2010 dadimedia.com
* All rights reserved.
* FileName��SMSecurityEnviroment.h
* Digest  ��sm�İ�ȫ�����࣬��Ҫ�ṩ��ʼ���ͻ�ȡ��ȫ��Ϣ��ؽӿڲ�����
* Version ��1.0
* Author  ��sm
* Date    ��2010.6.4
* Modify  ��2010.9.16 zhangliang �����߲� �����ģ������߲�� �����һ����ע��
* Modify  : 2010.9.19 yinlifang ���ݴ����߲�������������ʵ��޸ġ�
*/

#ifndef _SECURITYENVIROMENT_H_
#define _SECURITYENVIROMENT_H_

#include "x509/x509.h"
#include "smsdk/Ccspmanager.h"

#define MAX_NODE_LEN 4096
extern const unsigned int BUFMAXLINE; 		//ini������
extern const unsigned int SMS_CA_CHAIN;
extern const unsigned int PROJECT_CA_CHAIN;
extern const unsigned int USER_CA_CHAIN; 	//add by yin 2011.6.9
extern const unsigned int OFFICER_CA_CHAIN; //add by yin 2011.8.17

typedef struct SecInfo_st
{
	EVP_PKEY*      m_pEVPPriKey;			//private key of EVP format		
	X509*          m_pleafX509;	  			//device certifcate	
	vector<X509*>  m_VecCertchain;			//certificate chain
};


class CSMSecEnviroment
{	
public:	
	/****FUNCTION***************************************************
	* DESCRIPTION : constructor
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : none
	****************************************************************/	
	CSMSecEnviroment();	
	/****FUNCTION***************************************************
	* DESCRIPTION : destructor
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : none
	*    CAUTIONS : none
	****************************************************************/
	~CSMSecEnviroment();  	 
	/****FUNCTION***************************************************
	* DESCRIPTION : initialize security environment
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/	
	int Initialize();	
	
	//add by yin 2010.10.12 start for smconfig system
	/****FUNCTION***************************************************
	* DESCRIPTION : initialize PKI security environment
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/	
	int SecEnvInitialize();	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : initialize CSP security environment
	*       INPUT : none
	*      OUTPUT : none
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : none
	****************************************************************/	
	int CspInitialize();	
	//add by yin 2010.10.12 end
	
	/****FUNCTION***************************************************
	* DESCRIPTION : copy CSPs info to cspinfo
	*       INPUT : none
	*      OUTPUT : cspinfo
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : ǰ�ú���CspInitialize()��Initialize()
	****************************************************************/
	int GetCspInfo(cspinfo_st& cspinfo);	
	/****FUNCTION***************************************************
	* DESCRIPTION : load SM private key
	*       INPUT : none
	*      OUTPUT : pPrikey
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : pPrikey need to declare outside,but not need to new memeory for it 
	*             : ǰ�ú���SecEnvInitialize()��Initialize()
	****************************************************************/	
	int GetPrivatekey(EVP_PKEY** pPrikey);	
	/****FUNCTION***************************************************
	* DESCRIPTION : copy SM certificate
	*       INPUT : none
	*      OUTPUT : pcert
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : ǰ�ú���SecEnvInitialize()��Initialize()
	****************************************************************/
	int	Getleafcert(X509** pcert);
	/****FUNCTION***************************************************
	* DESCRIPTION : copy SM certificate chain
	*       INPUT : none
	*      OUTPUT : VecCertchain
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : ǰ�ú���SecEnvInitialize()��Initialize()
	****************************************************************/
	int Getcertchain(vector<X509*>& VecCertchain);	//�ź����֤������sm�豸�豸��֤����������Ҷ�ӣ�
	
	/****FUNCTION***************************************************
	* DESCRIPTION : copy SM trusted certificate chain
	*       INPUT :  trustca_Type: four type: SMS_CA_CHAIN the trusted certificate chain of SMS
	*                                         PROJECT_CA_CHAIN the trusted certificate chain of PROJECT
	*                                         USER_CA_CHAIN trusted certificate chain of USER
	*                                         OFFICER_CA_CHAIN  trusted certificate chain of OFFICER
	*      OUTPUT : vectrustcachain
					trustca_Type
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : ǰ�ú���SecEnvInitialize()��Initialize()
	*               modify by yin 2011.06.09 add user trust type
	****************************************************************/
	int Gettrustcachain(vector<X509*>& vectrustcachain, unsigned int trustca_Type);//��ȡָ�����͵�����֤����
	
	//add by yin 2011.06.09 start
	/****FUNCTION***************************************************
	* DESCRIPTION : copy MB user certificate
	*       INPUT : none
	*      OUTPUT : pcert
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : ǰ�ú���SecEnvInitialize()��Initialize()
	****************************************************************/
	int	GetUserleafcert(X509** pcert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : copy MB security officer certificate
	*       INPUT : none
	*      OUTPUT : pcert
	*     RETURNS : 0 - success, other - fail
	*    CAUTIONS : ǰ�ú���SecEnvInitialize()��Initialize()
	****************************************************************/
	int	GetOfficerleafcert(X509** pcert);
//add by yin 2011.06.09 end
	
private:	
				
	SecInfo_st    m_SecInfo;           		//informattion of certificate and private key
	cspinfo_st    m_cspinfo;           		//infomation of the csp
		
	vector<X509*> m_trustcachain_sms;     	//the trusted certificate chain of sms
	vector<X509*> m_trustcachain_project; 	//the trusted certificate chain of projiect
		
	//add by yin 2011.06.09 start		
	vector<X509*> m_trustcachain_user;     	//the trusted certificate chain of user 
	vector<X509*> m_trustcachain_officer;   //the trusted certificate chain of officer add by yin 2011.8.17
	X509* m_cert_user;                    	// the leaf cert of MB user
	X509* m_cert_officer;                 	// the leaf cert of MB security officer
	//add by yin 2011.06.09 end		
		
	int m_ldmpopenflag; 					//Ӳ���洢�򿪱�ʶ add by yin 2010.10.12
};
#endif

