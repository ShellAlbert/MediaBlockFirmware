/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  P12 file parse
FileName   �� pkcs12info.h
Author     �� yinlifang@dadimedia.com
Date       �� 10/08/03
Version    �� v1.0
Description�� P12 file parse
Others     :  
History    �� 
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
	* DESCRIPTION : Ĭ�Ϲ��캯��
	*       INPUT : a_pPass hash����ʹ������ 
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	CPKCS12Info();

	/****FUNCTION***************************************************
	* DESCRIPTION : ���캯��
	*       INPUT : a_pPass hash����ʹ������
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	explicit CPKCS12Info(const char* a_pPass);

	/****FUNCTION***************************************************
	* DESCRIPTION : ��������
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	virtual ~CPKCS12Info();

	//del by yin 2009.5.18 end
	/****FUNCTION***************************************************
	* DESCRIPTION : �����ڹ����������֮�󣬱�����õĺ���
	*       INPUT : a_pP12FileName p12�ļ���
	*				a_iEncodeType �������ݵı��뷽ʽ
	*      OUTPUT : ��
	*     RETURNS : 1 �ɹ��� 0 ʧ��
	*    CAUTIONS : ��
	****************************************************************/	
	int ParseP12(const char* a_pP12FileName,bool tlsp12flag = false, const int a_iEncodeType = NID_pkcs7_data);	

	
	/****FUNCTION***************************************************
	* DESCRIPTION : ������ȡ֤������������
	*       INPUT : a_pVecCaCertList ֤��������
	*      OUTPUT : ��
	*     RETURNS : 1 �ɹ��� 0 ʧ��
	*    CAUTIONS : ��
	****************************************************************/		
	int GetCaCert(vector<X509*>* a_pVecCaCertList,bool tlsp12flag = false);
	

	/****FUNCTION***************************************************
	* DESCRIPTION : ������ȡʵ��֤��
	*       INPUT : ��
	*      OUTPUT : a_ppSubCert ��ȡ����ʵ��֤��
	*     RETURNS : 1 �ɹ��� 0 ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int GetSubCert(X509** a_ppSubCert);

	/****FUNCTION***************************************************
	* DESCRIPTION : ʵ��֤���Ӧ˽Կ
	*       INPUT : ��
	*      OUTPUT : a_ppSubKey ��ȡ����ʵ��֤��˽Կ
	*     RETURNS : 1 �ɹ��� 0 ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int GetSubKey(EVP_PKEY** a_ppSubKey);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��������hash����ʹ�õ�����
	*       INPUT : a_pPassWord hash��������
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	void SetPassWord(const unsigned char* a_pPassWord);

private:
		
	EVP_PKEY* m_pKey;						//ʵ��֤��˽Կ��Ϣ
	X509* m_pCert;							//ʵ��֤��		
	vector<X509*> m_vecCaCertList;          //��������֤��������
	vector<X509*> m_vecTlsP12CaCertList;	//��������tls�������豸֤�������֤��������
	char m_pPass[1024];				        //p12����
};

#endif
