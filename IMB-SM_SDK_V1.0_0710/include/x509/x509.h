/*
* Copyright (c) 2007 dadimedia.com
* All rights reserved.
* �ļ����ƣ�x509.h
* ժ    Ҫ������X509�ṹ��,֤����ز���
* ��ǰ�汾��1.0
* ��    �ߣ�yinlifang
* ������ڣ�2010��06��03��
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
	* DESCRIPTION : ��Ĭ�Ϲ��캯��
	*       INPUT : ��
	*    CAUTIONS : ��
	****************************************************************/
	CX509();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������
	*       INPUT : ��
	*    CAUTIONS : ��
	****************************************************************/
	~CX509();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���ļ�֤����x509�ṹ��֤��
	*       INPUT : a_pCertfile Ҫ������֤�飨·�����ļ�����
	*               a_iCertType ֤��������ͣ�֧��FORMAT_DER��FORMAT_PEM��
	*                           һ����FORMAT_PEM
	*      OUTPUT : pX509 x509�ṹ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/	
	int GetX509Cert(const char* a_pCertfile, const int a_iCertType,X509** pX509);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ֤���еĹ�Կ
	*       INPUT : pX509 Ҫ������֤��
	*      OUTPUT : a_pPubKey ��Կ
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ����ֵΪ���ɶ���Ϣ
	****************************************************************/
	int GetPubKey(X509* pX509,EVP_PKEY** a_pPubKey);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ֤��汾��
	*       INPUT : pX509 Ҫ������֤��               
	*      OUTPUT : a_iVersion �汾��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int GetVersion(X509* pX509,int* a_iVersion);

	//del by yin 2010.7.23
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ֤����Чʱ��
	*       INPUT : pX509 Ҫ������֤��
	*      OUTPUT : a_ppNotBeforeTime ��ʼ��Чʱ��
	*               a_ppNotAfterTime  ������Чʱ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ʱ���ʽ�ǿɶ����ַ���
	****************************************************************/
	//int GetValidityTime(X509* pX509,unsigned char** a_ppNotBeforeTime,unsigned char** a_ppNotAfterTime);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ֤��ǩ���㷨��ʽ
	*       INPUT : pX509 Ҫ������֤��
	*      OUTPUT : a_pSignType ǩ���㷨
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ����ֵ��һ��int���ͣ���openssl���к�������㷨��ʶ����Ӧ
	****************************************************************/
	int GetSignatrueType(X509* pX509,int* a_pSignType);

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ֤�����к�  ����־���ã�
	*       INPUT : pX509 Ҫ������֤��
	*      OUTPUT : a_ppSerialNum ֤�����к�
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/
	int GetSerialNum(X509* pX509,unsigned char* a_ppSerialNum);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ֤�鷢������Ϣ  ����־���ã�
	*       INPUT : pX509 Ҫ������֤��
	*      OUTPUT : a_pIssuerName ֤�鷢������Ϣ
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/
	int GetIssuerName(X509* pX509,unsigned char* a_pIssuerName);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ȡָ��֤���Ȩ����Կ��ʶ
	*       INPUT : pX509 Ҫ������֤��
	*      OUTPUT : a_puchAuthouritykeyId ��ȡ����֤��Ȩ����Կ��ʶ
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/
	//int GetAuthorityKeyIdFromCert(X509* pX509,unsigned char* a_puchAuthouritykeyId); 
	//del by yin 2010.6.18 ��ʱû���õ�
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ȡ֤��ָ��                             
	*       INPUT : pX509 ָ����֤��					        
	*      OUTPUT : a_puchthumbprint ��ȡ����֤��ָ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/
	static int GetCertthumbprintFromCert(X509* pX509, unsigned char* a_puchthumbprint);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��X509��ʽ֤���л�ȡ֤����Чʱ��
	*       INPUT : pCert X509��ʽ֤��
	*      OUTPUT : puchTimeNotBefore ��Ч��ʼʱ��
	*               puchTimeNotAfter  ��Ч����ʱ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int GetX509ValidityTime(X509* pCert, unsigned char* puchTimeNotBefore, unsigned char* puchTimeNotAfter);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ȡ֤�������е�dnq
	*       INPUT : pX509 ָ����֤��				        
	*      OUTPUT : a_puchDnq ��ȡ���ĸ�֤������dnq
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : a_puchDnq�Ŀռ�����57���ֽڴ�С��28*2+1��
	****************************************************************/
	static int GetDnqFromCert(X509* pX509,unsigned char* a_puchDnq);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȥ֤���ɫ��
	*       INPUT : pX509 X509֤��
	*      OUTPUT : pchRolName ��ɫ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int get_role(X509* pX509, char* pchRolName);   	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ָ����֤��ת�����ַ���
	*       INPUT : a_pInputCert ָ����֤��
	*      OUTPUT : a_ppOut ��õ��ַ���
	*				        a_pOutLength ��ȡ�ַ����ĳ���
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : a_ppOut ����Ҫ�����ڴ棬openssl������䣬������Ҫfree�ڴ�
	****************************************************************/
	int CertStructToString(X509* a_pInputCert, unsigned char** a_ppOut, unsigned int* a_pOutLength);

	/****FUNCTION***************************************************
	* DESCRIPTION : ������ָ�����ַ���ת����֤��
	*       INPUT : a_pIn ָ�����ַ���
	*				        a_iInLength ָ���ַ�������
	*      OUTPUT : a_ppOutCert ��õ�֤��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : *a_ppOutCert���Բ������ڴ棬���Ǳ���Ҫ����X509��Դ
	****************************************************************/
	static int CertStringToStruct(X509** a_ppOutCert, const unsigned char* a_pIn, const unsigned int a_iInLength);
	
	//from x509-430	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����֤�鳷���б�
	*       INPUT : crlfile ֤�鳷���б�
	*               fileformat crl�ļ������ʽ��֧������FORMAT_DER��FORMAT_PEM
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int load_crlfile(const char* crlfile,int fileformat);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����֤����������֤�����е�֤�����������֤��֤���ã�
	*       INPUT : chainBuf ֤������pem��ʽ��buffer��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int load_chainfile(const char* chainBuf);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����֤����������֤�����е�֤������sm�˳�ʼ�����ã�
	*       INPUT : certfilename ֤�����ļ���֤������֤��ĺ�·�����ļ�����
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int load_chainfile(vector<unsigned char*> certfilename,int fileType);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����֤����������֤�����е�֤������kdm��cpl��pklǩ��֤����־ǩ����֤���ã�
	*       INPUT : chainBuf ֤������֤������֤�飺base64��֤��buffer��û��pemͷ��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int load_chainfile(vector<unsigned char*> chainBuf);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����֤������
	*       INPUT : iCertType ֤������	            
	*               ��ѡֵ��CERTTYPE_SMS;CERTTYPE_SM;CERTTYPE_USER;CERTTYPE_PROJECTOR;CERTTYPE_ENCODER; 
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��SingleCertVerify��do_certformatverify������ǰ�ú���
	****************************************************************/
	int SetCertType(int iCertType);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����֤��ĸ�ʽ��֤(DCI֤���ʽ��������֤)
	*       INPUT : pX509 X509��ʽ֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ǰ�ú�����SetCertType(int iCertType)
	****************************************************************/
	int SingleCertVerify(X509* cert);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ֤������֤��ĸ�ʽ��֤�Ƿ����SMPTE 430-2
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ǰ�ú���Ϊ��SetCertType(int iCertType)
	****************************************************************/
	int do_certformatverify();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ֤������֤
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ǰ�ú���Ϊ��do_certformatverify()
	****************************************************************/
	int do_chainverify();	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ������֤��
	*       INPUT : ��
	*      OUTPUT : X509�ṹ֤��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	//X509* get_root(); //ע����Ҫ��get_leaf�޸� 2010.6.13 del by yin 2010.7.23
	int get_root(X509** pcert); //add by yin  2010.7.23

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�����Ҷ��֤��
	*       INPUT : ��
	*      OUTPUT : X509�ṹ֤��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	//X509* get_leaf();	
	int get_leaf(X509** pcert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�����ȡ֤����
	*       INPUT : ��
	*      OUTPUT : X509�ṹ֤����
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int get_certlist(vector<X509*>& certlist); 	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : �ж��Ƿ���CA֤��
	*       INPUT : pX509 X509��ʽ֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int X509_check_ca(X509* pX509);		
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��֤ʹ��֤���ʱ������Чʱ����
	*       INPUT : pX509 X509֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
  	int X509_timeValidate_check(X509* pX509);
	
private:
	
	X509* m_root;					// Root certificate
	X509* m_leaf;					// Leaf certificate
	X509_CRL* m_crl;				// Certificate Revocation List
	vector<X509*> m_vecCert;       	// ����δ�������֤����
	vector<X509*> m_X509data_list; 	// �����ź����֤������root֤���ڵ�һ��Ԫ��λ�ã�
	STACK_OF(X509)* m_stackChain;  	// Certificate Chain stack
	int m_CertType;                	// ֤������
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����x509����չ��Ϣ
	*       INPUT : px509 ֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	void x509v3_cache_extensions(X509* px509);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��֤�����е�֤���������
	*       INPUT : vecCert ֤����
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int sort_certlist(vector<X509*> vecCert);	

	/****FUNCTION***************************************************
	* DESCRIPTION : �ж�commonName�ֶ��Ƿ���ڸ��еĽ�ɫ
	*       INPUT : ֤��commonName�ֶ�ֵ             
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	int is_hasrole(const char* commonname);

	/****FUNCTION***************************************************
	* DESCRIPTION : ��֤ʹ��֤���ʱ������Чʱ����
	*       INPUT : pX509 X509֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : ��
	****************************************************************/
	//int X509_timeValidate_check(X509* pX509);

	/****FUNCTION***************************************************
	* DESCRIPTION : ����x509�ṹ��Ĺ�Կ���㹫Կָ��
	*       INPUT : pX509 ֤��	
	*      OUTPUT : p_chDnq ��Կָ��
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/
	int CalculateDnq(X509* pX509,unsigned char* p_chDnq);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����RSA��Կת�ַ���
	*       INPUT : a_pRSAPubKey ��Կ	
	*      OUTPUT : a_ppOut ����ַ�����Կ
	*               a_pOutLength �ַ�����Կ����
	*     RETURNS : 0�ɹ� ��0Ϊ������
	*    CAUTIONS : 
	****************************************************************/
	int PubKeyInToString(RSA* a_pRSAPubKey, unsigned char** a_ppOut, unsigned int* a_pOutLength);
};

#endif
