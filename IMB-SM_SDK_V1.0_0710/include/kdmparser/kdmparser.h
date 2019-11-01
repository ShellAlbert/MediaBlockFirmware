/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* �ļ����ƣ�kdmparser.h
* ժ    Ҫ��KDM�����࣬��Ҫ�ṩKDM���������ǩ����֤���ڵ�ֵ��������֤����ȡ������Կ�Ƚӿڡ�
* ��ǰ�汾��1.0
* ��    �ߣ�����
* ȡ���汾����
* ˵������Ҫ�ο�CTP_test,S430_1(KDM),S430_3(ETM)�ĵ�
* ������ڣ�2010��01��20��
*/
#ifndef _KDM_PARSER_H_
#define _KDM_PARSER_H_
//#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
//#include "harddriver/ldmp_key.h" 		
//#include "harddriver/mbdriver_ioctl.h"		//deleted by sunpeng at 20121205
#include "harddriver/data_types.h"					//added by sunpeng at 20131213

#include "xml/XmlCollections.h"
#include "xml/XmlDocument.h"
#include "x509/x509.h"
//#define KDM_NOSIGN
#define MAX_NODE_LEN 4096

XERCES_CPP_NAMESPACE_USE
using namespace xercesc;

class KDMParser
{
public:	
	//�ڲ��࣬��Ҫ����KDM��xml�ڵ����
	class KDMNode
	{
	public:
		KDMNode();
		CXmlResultSet* pxmlMessageId;
		CXmlResultSet* pxmlSignature;
		CXmlResultSet* pxmlKDMRequiredExtensions;
		CXmlResultSet* pxmlX509cert;
		CXmlResultSet* pxmlSignerName;
		CXmlResultSet* pxmlX509IssuerName;
		CXmlResultSet* pxmlIssueDate;
		CXmlResultSet* pxmlContentKeysNotValidBefore;
		CXmlResultSet* pxmlContentKeysNotValidAfter;
		CXmlResultSet* pxmlKeyInfoX509IssuerName;

		CXmlResultSet* pxmlEncryptionMethod;
		CXmlResultSet* pxmlAnnotationText;
		CXmlResultSet* pxmlCanonicalizationMethod;
		CXmlResultSet* pxmlReference;
		CXmlResultSet* pxmlAuthenticatedPublic;
		CXmlResultSet* pxmlAuthenticatedPrivate;
		CXmlResultSet* pxmlSignatureMethod;
		CXmlResultSet* pxmlRefDigestMethod;
		CXmlResultSet* pxmlMessageType;
		CXmlResultSet* pxmlSubjectName;
		CXmlResultSet* pxmlContentAuthenticator;
		CXmlResultSet* pxmlReferenceList;
		CXmlResultSet* pxmlForensicMarFlagList;
		CXmlResultSet* pxmlEncryptedData;
		CXmlResultSet* pxmlKeyInfo;
		CXmlResultSet* pxmlDeviceListDescription;
		CXmlResultSet* pxmlTypeKeyID;
		CXmlResultSet* pxmlEncryptionMethodForKey;
		CXmlResultSet* pxmlNonCriticalExtensions;
		CXmlResultSet* pxmlCipherValue;
		CXmlResultSet* pxmlX509IssuerNameOfRecipient;
		CXmlResultSet* pxmlX509SerialNumberOfRecipient;
		CXmlResultSet* pxmlX509IssuerNameOfX509Data;
		CXmlResultSet* pxmlX509SerialNumberOfX509Data;

		CXmlResultSet* pxmlCompositionPlaylistId;
		CXmlResultSet* pxmlTypedKeyId;//add by zhangliang 2010.8.18
		CXmlResultSet* pxmlKeyId;
		CXmlResultSet* pxmlKeyType;
		CXmlResultSet* pxmlSignerX509IssuerName;

		CXmlResultSet* pxmlTDLCertificateThumbprint;
		CXmlResultSet* pxmlDeviceList;		
	};

	KDMParser(void);
	~KDMParser(void);

	/****FUNCTION***************************************************
	* DESCRIPTION : KDM������ʼ��,����xml�ڵ�
	*       INPUT : puchFilePath	KDM�ļ���������·����
	*				        pX509RecipientCert  KDM�������豸֤��(x509) 	
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_ParserInitial(const unsigned char* puchFilePath,X509* pX509RecipientCert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : KDM������ʼ��
	*       INPUT : strKDM	KDM�ַ���
	*				        pX509RecipientCert  KDM�������豸֤��(x509) 	
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_ParserInitial(const  char* strKDM, X509* pX509RecipientCert);

	/****FUNCTION***************************************************
	* DESCRIPTION : KDM������ʼ�� ȡ��������֤��ֻ��������Կ
	*       INPUT : strKDMKDM�ַ���	
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
#ifdef KDM_SIGN
	int KDM_ParserInitial(const  char* strKDM);
#endif
	
	/****FUNCTION***************************************************
	* DESCRIPTION : KDM֤��������֤
	*       INPUT : ��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_VerifyCerChain();

	/****FUNCTION***************************************************
	* DESCRIPTION : KDMǩ����֤
	*       INPUT : puchFilePath KDM�ļ���������·����
	*             : cert  KDM������֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_SignatureVerify(const unsigned char* puchFilePath,const char* cert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : KDMǩ����֤
	*       INPUT : strKDM KDM�ַ���
	*             : cert  KDM������֤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_SignatureVerify(const  char* strKDM,const char* cert);

	/****FUNCTION***************************************************
	* DESCRIPTION : KDM�Ǽ��ܽڵ�ֵ������ֵ����֤
	*       INPUT : pvcCPLCertThumbprint ��Ӧcpl֤����ָ��			
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_NodeValueAndAttributeVerify(vector<char*> pvcCPLCertThumbprint);

	/****FUNCTION***************************************************
	* DESCRIPTION : ��KDM�������ݽ��ܺ����֤
	*       INPUT : mapId2KeyId  �켣�ļ�Id��keyId��Ӧ��map�� 
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_DecDataVerify(map<string,string> mapId2KeyId);

	/****FUNCTION***************************************************
	* DESCRIPTION : ���KDM�е�������Կ
	*       INPUT : pEVPRecieptPrikey	������˽Կ				
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_GetDecryptedKey(const EVP_PKEY* pEVPRecieptPrikey);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����KDM,����KDMʱ����Ч�Ժ�TDL��֤
	*       INPUT : puchFilePath 				KDM�ļ���������·����
	*								pvcCPLCertThumbprint��Ӧ��CPL֤����ָ��
	*								pX509RecipientCert  KDM�������豸֤��(x509) 
	*								pEVPRecieptPrikey   KDM�����߽���˽Կ(EVP)
	*								pchNowTime		 			��ǰʱ��
	*               mapId2KeyId         CPL�е�trackId��KeyId�Ķ�Ӧmap��
	*								pchTDL			 				������֤��ָ��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_ParserFile(const unsigned char* puchFilePath, vector<char*> pvcCPLCertThumbprint, X509* pX509RecipientCert, EVP_PKEY* pEVPRecieptPrikey,const unsigned char* pchNowTime,const unsigned char* pchTDL,map<string,string> mapId2KeyId);

	/****FUNCTION***************************************************
	* DESCRIPTION : ����KDM,����KDMʱ����Ч�Ժ�TDL��֤
	*       INPUT : strKDM 							KDM�ַ���
	*								pvcCPLCertThumbprint��Ӧ��CPL֤����ָ��
	*								pX509RecipientCert  KDM�������豸֤��(x509) 
	*								pEVPRecieptPrikey   KDM�����߽���˽Կ(EVP)
	*								pchNowTime		 			��ǰʱ��
	*								pchTDL			 				������֤��ָ��
	*               mapId2KeyId         CPL�е�trackId��KeyId�Ķ�Ӧmap��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_ParserString(const char* strKDM, vector<char*> pvcCPLCertThumbprint, X509* pX509RecipientCert, EVP_PKEY* pEVPRecieptPrikey,const unsigned char* pchNowTime,const unsigned char* pchTDL,map<string,string> mapId2KeyId);

//tangquanfa add start
	/****FUNCTION***************************************************
	* DESCRIPTION : ����KDM
	*       INPUT : strKDM 				KDM�ַ���
	*				pX509RecipientCert  KDM�������豸֤��(x509) 
	*				pEVPRecieptPrikey   KDM�����߽���˽Կ(EVP)
	*				pchTDL			 	������֤��ָ��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_ParserString(const char* strKDM, X509* pX509RecipientCert, EVP_PKEY* pEVPRecieptPrikey, const unsigned char* pchTDL );
//tangquanfa add end

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ���ܺ��������Կ��Ϣ
	*       INPUT : ��
	*      OUTPUT : vecContentKey ��Կ��Ϣ
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��
	****************************************************************/
	int KDM_GetKeyInfo(vector<content_key>* vecContentKey);
  
  /****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ��ӦCPL��Id
	*       INPUT : ��     
	*      OUTPUT : puchCPLId ǩ����֤��ָ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��     
	****************************************************/
	int KDM_GetCPLId(unsigned char* puchCPLId);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : TDL��֤
	*       INPUT : puchTDL �����豸�б�    
	*      OUTPUT : 
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��                              
	****************************************************/                    
	int KDM_VerifyTDL(const unsigned char* puchTDL);                         

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�Ƿ������Ƶˮӡ��ʶ
	*       INPUT : ��     
	*      OUTPUT : ��
	*     RETURNS : true����� false�������
	*    CAUTIONS : ��                              
	****************************************************/                    
	bool KDM_GetImageFM();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡKDM��ID
	*       INPUT : ��     
	*      OUTPUT : puchKDMId KDM��ID
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��                              
	****************************************************/  
	int KDM_GetKDMId(unsigned char* puchKDMId); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�Ƿ������Ƶˮӡ��ʶ
	*       INPUT : ��     
	*      OUTPUT : ��
	*     RETURNS : true����� false�������
	*    CAUTIONS : ��                              
	****************************************************/                    
	bool KDM_GetAudioFM();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���ö�ӦCPL�Ƿ�ǩ����־
	*       INPUT : blCPLSigned  �Ƿ�ǩ����־      
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��                              
	****************************************************/                    
	int KDM_SetCPLSignedFlag(bool blCPLSigned);	
	                       
  /****FUNCTION***************************************************
	* DESCRIPTION : ��ȡKDMָ�ƣ�����kdm��־
	*       INPUT : ��     
	*      OUTPUT : puchSignerThumbprint ǩ����֤��ָ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��     
	****************************************************/
	int GetSignerThumbprint(unsigned char* puchSignerThumbprint);
	                       
  /****FUNCTION***************************************************
  * DESCRIPTION : KDM�н�����subjectName��SM֤���subjectName�Ƚ�
  *       INPUT : SubjectName       KDM�н�����subjectName
  *             ��pX509RecieptCert  ������֤�飺��SM֤�飨x509��ʽ��
  *      OUTPUT : ��
  *     RETURNS : 0��ͬ ��0��ͬ
  *    CAUTIONS : ��
  ****************************************************************/
  int SubjectNameCompare(const unsigned char* SubjectName, X509* pX509RecieptCert);
  
  /****FUNCTION***************************************************
	* DESCRIPTION : ��֤ʱ���Ƿ���UTC��ʽ
	*       INPUT : puchUTCTime ʱ���ַ���    
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : ��     
	****************************************************/
	int UTCTimeCheck(unsigned char* puchUTCTime);
  
  
  //add by huweihua 2011/07/16
  unsigned int GetContentKeysNotValidBefore();
  unsigned int GetContentKeysNotValidAfter();
  
	private:
		X509* m_recipientX509;//KDM�����ߵ�֤��
		X509* m_leafX509;//Ҷ��֤�飨ǩ��֤�飩
		KDMNode* m_pKDMNode;
		CXmlDocument* m_xmlDocument;//���ڽ���KDM��xml����
		vector<char*> m_vecKeyInfo;//KDM��Կ��Ϣ
		vector<content_key> m_vecContent_key;//KDM�н�������������Կ
		unsigned char* m_SignerThumbprint; //ǩ��֤��ָ�� add by zhangliang 2010.7.30
		bool m_ImageFM;//�������Ƶˮӡ��ʶ
		bool m_AudioFM;//�������Ƶˮӡ��ʶ
		bool m_CPLSigned;//��ӦCPL�Ƿ���ǩ�� ��ǩ��Ϊ��TRUE û��ǩ��Ϊ��FLASE add by zhangliang 2010.8.5
};
#endif
