/*
* Copyright (c) 2010 中国数码
* All rights reserved.
* 文件名称：kdmparser.h
* 摘    要：KDM解析类，主要提供KDM解析所需的签名验证、节点值和属性认证、获取明文密钥等接口。
* 当前版本：1.0
* 作    者：张量
* 取代版本：无
* 说明：主要参考CTP_test,S430_1(KDM),S430_3(ETM)文档
* 完成日期：2010年01月20日
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
	//内部类，主要保存KDM的xml节点对象
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
	* DESCRIPTION : KDM解析初始化,解析xml节点
	*       INPUT : puchFilePath	KDM文件名（包含路径）
	*				        pX509RecipientCert  KDM接收者设备证书(x509) 	
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_ParserInitial(const unsigned char* puchFilePath,X509* pX509RecipientCert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : KDM解析初始化
	*       INPUT : strKDM	KDM字符流
	*				        pX509RecipientCert  KDM接收者设备证书(x509) 	
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_ParserInitial(const  char* strKDM, X509* pX509RecipientCert);

	/****FUNCTION***************************************************
	* DESCRIPTION : KDM解析初始化 取消所有验证，只解内容密钥
	*       INPUT : strKDMKDM字符流	
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
#ifdef KDM_SIGN
	int KDM_ParserInitial(const  char* strKDM);
#endif
	
	/****FUNCTION***************************************************
	* DESCRIPTION : KDM证书链的验证
	*       INPUT : 无
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_VerifyCerChain();

	/****FUNCTION***************************************************
	* DESCRIPTION : KDM签名验证
	*       INPUT : puchFilePath KDM文件名（包含路径）
	*             : cert  KDM接收者证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_SignatureVerify(const unsigned char* puchFilePath,const char* cert);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : KDM签名验证
	*       INPUT : strKDM KDM字符流
	*             : cert  KDM接收者证书
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_SignatureVerify(const  char* strKDM,const char* cert);

	/****FUNCTION***************************************************
	* DESCRIPTION : KDM非加密节点值和属性值的验证
	*       INPUT : pvcCPLCertThumbprint 对应cpl证书链指纹			
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_NodeValueAndAttributeVerify(vector<char*> pvcCPLCertThumbprint);

	/****FUNCTION***************************************************
	* DESCRIPTION : 对KDM加密内容解密后的验证
	*       INPUT : mapId2KeyId  轨迹文件Id和keyId对应的map表 
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_DecDataVerify(map<string,string> mapId2KeyId);

	/****FUNCTION***************************************************
	* DESCRIPTION : 获得KDM中的明文密钥
	*       INPUT : pEVPRecieptPrikey	接受者私钥				
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_GetDecryptedKey(const EVP_PKEY* pEVPRecieptPrikey);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 解析KDM,包括KDM时间有效性和TDL验证
	*       INPUT : puchFilePath 				KDM文件名（包含路径）
	*								pvcCPLCertThumbprint对应的CPL证书链指纹
	*								pX509RecipientCert  KDM接收者设备证书(x509) 
	*								pEVPRecieptPrikey   KDM接收者解密私钥(EVP)
	*								pchNowTime		 			当前时间
	*               mapId2KeyId         CPL中的trackId和KeyId的对应map表
	*								pchTDL			 				接收者证书指纹
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_ParserFile(const unsigned char* puchFilePath, vector<char*> pvcCPLCertThumbprint, X509* pX509RecipientCert, EVP_PKEY* pEVPRecieptPrikey,const unsigned char* pchNowTime,const unsigned char* pchTDL,map<string,string> mapId2KeyId);

	/****FUNCTION***************************************************
	* DESCRIPTION : 解析KDM,包括KDM时间有效性和TDL验证
	*       INPUT : strKDM 							KDM字符流
	*								pvcCPLCertThumbprint对应的CPL证书链指纹
	*								pX509RecipientCert  KDM接收者设备证书(x509) 
	*								pEVPRecieptPrikey   KDM接收者解密私钥(EVP)
	*								pchNowTime		 			当前时间
	*								pchTDL			 				接收者证书指纹
	*               mapId2KeyId         CPL中的trackId和KeyId的对应map表
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_ParserString(const char* strKDM, vector<char*> pvcCPLCertThumbprint, X509* pX509RecipientCert, EVP_PKEY* pEVPRecieptPrikey,const unsigned char* pchNowTime,const unsigned char* pchTDL,map<string,string> mapId2KeyId);

//tangquanfa add start
	/****FUNCTION***************************************************
	* DESCRIPTION : 解析KDM
	*       INPUT : strKDM 				KDM字符流
	*				pX509RecipientCert  KDM接收者设备证书(x509) 
	*				pEVPRecieptPrikey   KDM接收者解密私钥(EVP)
	*				pchTDL			 	接收者证书指纹
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_ParserString(const char* strKDM, X509* pX509RecipientCert, EVP_PKEY* pEVPRecieptPrikey, const unsigned char* pchTDL );
//tangquanfa add end

	/****FUNCTION***************************************************
	* DESCRIPTION : 获取解密后的内容密钥信息
	*       INPUT : 无
	*      OUTPUT : vecContentKey 密钥信息
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无
	****************************************************************/
	int KDM_GetKeyInfo(vector<content_key>* vecContentKey);
  
  /****FUNCTION***************************************************
	* DESCRIPTION : 获取对应CPL的Id
	*       INPUT : 无     
	*      OUTPUT : puchCPLId 签名者证书指纹
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无     
	****************************************************/
	int KDM_GetCPLId(unsigned char* puchCPLId);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : TDL验证
	*       INPUT : puchTDL 信任设备列表    
	*      OUTPUT : 
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无                              
	****************************************************/                    
	int KDM_VerifyTDL(const unsigned char* puchTDL);                         

	/****FUNCTION***************************************************
	* DESCRIPTION : 获取是否添加视频水印标识
	*       INPUT : 无     
	*      OUTPUT : 无
	*     RETURNS : true：添加 false：不添加
	*    CAUTIONS : 无                              
	****************************************************/                    
	bool KDM_GetImageFM();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取KDM的ID
	*       INPUT : 无     
	*      OUTPUT : puchKDMId KDM的ID
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无                              
	****************************************************/  
	int KDM_GetKDMId(unsigned char* puchKDMId); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取是否添加音频水印标识
	*       INPUT : 无     
	*      OUTPUT : 无
	*     RETURNS : true：添加 false：不添加
	*    CAUTIONS : 无                              
	****************************************************/                    
	bool KDM_GetAudioFM();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置对应CPL是否签名标志
	*       INPUT : blCPLSigned  是否签名标志      
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无                              
	****************************************************/                    
	int KDM_SetCPLSignedFlag(bool blCPLSigned);	
	                       
  /****FUNCTION***************************************************
	* DESCRIPTION : 获取KDM指纹，用于kdm日志
	*       INPUT : 无     
	*      OUTPUT : puchSignerThumbprint 签名者证书指纹
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无     
	****************************************************/
	int GetSignerThumbprint(unsigned char* puchSignerThumbprint);
	                       
  /****FUNCTION***************************************************
  * DESCRIPTION : KDM中接收者subjectName和SM证书的subjectName比较
  *       INPUT : SubjectName       KDM中接收者subjectName
  *             ：pX509RecieptCert  接受者证书：即SM证书（x509格式）
  *      OUTPUT : 无
  *     RETURNS : 0相同 非0不同
  *    CAUTIONS : 无
  ****************************************************************/
  int SubjectNameCompare(const unsigned char* SubjectName, X509* pX509RecieptCert);
  
  /****FUNCTION***************************************************
	* DESCRIPTION : 验证时间是否是UTC格式
	*       INPUT : puchUTCTime 时间字符串    
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 无     
	****************************************************/
	int UTCTimeCheck(unsigned char* puchUTCTime);
  
  
  //add by huweihua 2011/07/16
  unsigned int GetContentKeysNotValidBefore();
  unsigned int GetContentKeysNotValidAfter();
  
	private:
		X509* m_recipientX509;//KDM接收者的证书
		X509* m_leafX509;//叶子证书（签名证书）
		KDMNode* m_pKDMNode;
		CXmlDocument* m_xmlDocument;//用于解析KDM的xml对象
		vector<char*> m_vecKeyInfo;//KDM密钥信息
		vector<content_key> m_vecContent_key;//KDM中解析出的内容密钥
		unsigned char* m_SignerThumbprint; //签名证书指纹 add by zhangliang 2010.7.30
		bool m_ImageFM;//不添加视频水印标识
		bool m_AudioFM;//不添加音频水印标识
		bool m_CPLSigned;//对应CPL是否有签名 有签名为：TRUE 没有签名为：FLASE add by zhangliang 2010.8.5
};
#endif
