/*
* Copyright (c) 2007 �й�����
* All rights reserved.
* * �ļ����ƣ�CAuthentication.h
* ժ    Ҫ�������֤����
* * ��ǰ�汾��3.0
* ��    �ߣ�yinlifang
** ȡ���汾����
* ԭ����  ��drm
* ������ڣ�2010��4��22��
* �޸����ڣ�2010��9��16�ա�2011��5��31��
*/

#ifndef _CAUTHENTICATION_H_
#define _CAUTHENTICATION_H_

//#define SMCLIENT
#include "smsdk/errornumber.h" 
#include "crypto/arithmatic.h" 
#include "crypto/arithtype.h" 
//��Ӱ�ȫ����ͷ�ļ�
#include "x509/x509.h" 
#ifndef  SMCLIENT
#include "harddriver/Manage_MSP430_Status.h" 	//add by yin 2011.8.9
#include "smsdk/Ccspmanager.h"  				//add by yin 2011.8.9
#endif

#include <iostream>
using namespace std;
extern const unsigned int USER_NUMBER;
extern const unsigned int USERID_LEN; 
extern const unsigned int USERNAME_LEN;
extern const unsigned int PASSWORD_LEN;

//Ȩ�޶���
extern const unsigned int EXECUTE_KDM_RIGHT;
extern const unsigned int SET_TIME_RIGHT;
extern const unsigned int ZEROIZE_RIGHT;
extern const unsigned int FIRMWARE_UPDATE_RIGHT;
//extern const unsigned int SET_CSPS_RIGHT;	  	//del by yin 2011.5.31
//extern const unsigned int RESET_CSPS_RIGHT;	//add by yin 2010.7.14 ����Ȩ�� //del by yin 2011.5.31
extern const unsigned int IMPORT_CERT_RIGHT;	//Import Cert right  //add by yin 2011.5.31
extern const unsigned int QUERY_CERT_RIGHT;	  	//Query Cert right   //add by yin 2011.5.31
extern const unsigned int GET_LOGINFO_RIGHT;	//add by yin 2010.9.19 ��ȡ��־Ȩ��
extern const unsigned int GET_AUDIT_RIGHT;		//add by yin 2010.9.19 ���Ȩ��

//��ɫ���� add by yin 2011.8.9
extern const unsigned int USER_ROLE;     		//�û���ɫ
extern const unsigned int OFFICER_ROLE;     	//��ȫ����Ա��ɫ 

//�����֤������Ϣ�ṹ��
struct requserinfo_st{
	unsigned char puserID[30];
	unsigned char pusername[18];	// modify by yin 2010.5.7 12-->18 ʵ����Ч�����16���仯ԭ�����base
	unsigned char password[14];		// modify by yin 2010.5.7 8-->14 ʵ����Ч�����12
	unsigned char role[16]; 		//add by yin 2011.5.31
	unsigned int signArith;
	unsigned int signvaluelen;
	unsigned char* signvalue;
  //unsigned char* certchainvalue;	//Ҷ��֤�鼴�ɣ�note by yin 2011.6.2  
                                    // add note by yin 2011.8.11Ϊ�պ�֧�ֶ���û��ɱ������ֶ� 
                                    //del by yin 2011.8.12
};

//�����֤��Ӧ��Ϣ�ṹ��
struct repuserinfo_st{
	unsigned char userID[30]; 		//modify by yin 2010.5.7 30-->58 
	int right;	
};

//Ȩ����Ϣ�ṹ��
struct rightinfo_st{	
	unsigned char onrightflag;		//no right
	unsigned char executeKDMflag;	//execute KDM right
	unsigned char setTimeflag;		//time adjust right
	unsigned char zeroizeflag;		//zeroize right
	unsigned char firmwareflag;     //firmware update right
	//unsigned char setcspsflag;	//set csps right     //del by yin 2011.5.31
	//unsigned char resetcspsflag;  //reset csps right   //del by yin 2011.5.31
	unsigned char ImportCertflag;	//Import Cert right  //add by yin 2011.5.31
	unsigned char QueryCertflag;	//Query Cert right   //add by yin 2011.5.31
	unsigned char getloginfoflag;   //get log info right  //add by yin 2010.9.19
	unsigned char auditflag;        //audit right  //add by yin 2010.9.19
};

class CAuthentication
{
public:	

	CAuthentication(const unsigned int ldmpopenflag = 1/*,SecInfo_st SecurityInfo*/);//for sm	
	~CAuthentication();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���������֤����
	*       INPUT : userID �û�ID
	*               pusername �û���	              
	*				password �û�����,ע������м䲻��������ַ�/0��ĩβ���⡣			
	*      OUTPUT : req_userinfo	�����֤�����ֶ���Ϣ
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : req_userinfo�е�signvalue��certchainvalue�Ǻ����ڲ������ڴ棬�����ⲿ�ͷ�	
	****************************************************************/
	static int createAuthenticationRequestinfo(unsigned char* puserID,unsigned char* pusername,
	                                    unsigned char* password,unsigned char* prole,unsigned int signArith,
	                                    EVP_PKEY* pprivateKey,/* vector<X509*> vcertchain,*/
	                                    requserinfo_st& req_userinfo);	//modify by yin 2010.9.19 add static
	                                    //modify by yin 2011.5.31 add prole
	                                      //modify by yin 2011.8.12 del vcertchain
	                                      
	/****FUNCTION***************************************************
	* DESCRIPTION : ���ɵǳ������ǩ��ֵ
	*       INPUT : userID �û�ID
	*               prole  �û���ɫ
	*				signArith ǩ���㷨
	*               pprivateKey ǩ��˽Կ
	*      OUTPUT : signvaluelen ǩ��ֵ����
	*               signvalue ǩ��ֵ
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : signvalue Ϊ�ڲ������ڴ棬�ⲿ�ͷš�add by yin 2011.9.19
	****************************************************************/
	int creatLogoutRequestsignvalue(unsigned char* puserID,
	                        unsigned char* prole, 
	                        unsigned int signArith,
	                        EVP_PKEY* pprivateKey,
	                        unsigned int& signvaluelen,
	                        unsigned char** signvalue);	
	
#ifndef  SMCLIENT                                    
	/****FUNCTION***************************************************
	* DESCRIPTION : ���������֤����������Ӧ��Ϣ
	*       INPUT : req_userinfo	�����֤�����ֶ���Ϣ
	*      OUTPUT : rep_userinfo	�����֤��Ӧ�ֶ���Ϣ
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	
	int proessAuthenticationRequestinfo(requserinfo_st req_userinfo,repuserinfo_st& rep_userinfo);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���������֤��Ӧ
	*       INPUT : userID �û�ID
	*				password �û�����			
	*      OUTPUT : req_userinfo	�����֤�����ֶ���Ϣ
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int proessAuthenticationReponseinfo(repuserinfo_st rep_userinfo,rightinfo_st& right);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����ǳ�����
	*       INPUT : userID �û�ID
	*               prole  �û���ɫ
    *				signArith ǩ���㷨
	*               signvaluelen ǩ��ֵ����
	*               signvalue ǩ��ֵ
	*               certchainvalue ֤����ֵ������Ҷ�ӣ�		
	*      OUTPUT : NULL	��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	int proessLogoutRequest(unsigned char* puserID,
	                        unsigned char* prole, //add by yin 2011.8.12
	                        unsigned int signArith,
	                        unsigned int signvaluelen,
	                        unsigned char* signvalue/*,
	                        unsigned char* certchainvalue*/);		 //modify by yin 2011.8.12 del certchainvalue
#endif
	/****FUNCTION***************************************************
	* DESCRIPTION : �����û�Ȩ��
	*       INPUT : roletype �û���ɫ���ͣ�OFFICER_ROLEΪ�ǰ�ȫ����Ա��USER_ROLEΪ��ͨ�û�			
	*      OUTPUT : right	Ȩ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	static int setuserright(int roletype,int& right);	//modify by yin 2010.9.19 add static
	
	//add by yin 2010.9.16 for officer authentication base on socket
	/****FUNCTION***************************************************
	* DESCRIPTION : ���ɻỰ����
	*       INPUT : puserID �û�ID
	*             : iuserIDlen �û�ID��		
	*      OUTPUT : pranda �����ah
	*             : irandalen �����a����
	*             : phashvalue �û�ID�������a��ժҪֵ
	*             : ihashvaluelen �û�ID�������a��ժҪֵ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	static int createSessionRequestinfo(unsigned char* puserid, unsigned int iuseridlen,
	                             unsigned char* pranda, unsigned int& irandalen,
	                             unsigned char* phashvalue, unsigned int& ihashvaluelen);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����Ự�������ɻỰ������Ӧ
	*       INPUT : puserID �û�ID
	*             : iuserIDlen �û�ID��		
	*             : pranda �����a
	*             : irandalen �����a����
	*             : phashvalue �û�ID���������ժҪֵ
	*             : ihashvaluelen �û�ID���������ժҪֵ��
	*      OUTPUT : prandb �����b
	*             : irandblen �����b����
	*             : phashvaluenew �û�ID�������a�������b��ժҪֵ
	*             : ihashvaluenewlen �û�ID�������a�������b��ժҪֵ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
	static int createSessionReponseinfo(unsigned char* puserid, unsigned int iuseridlen,
	                             unsigned char* pranda, unsigned int irandalen,
	                             unsigned char* phashvalue, unsigned int ihashvaluelen,
	                             unsigned char* prandb, unsigned int& irandblen,
	                             unsigned char* phashvaluenew, unsigned int& ihashvaluenewlen);	
	                             
	/****FUNCTION***************************************************
	* DESCRIPTION : ����Ự������Ӧ�����������֤����
	*       INPUT : pSessionReponseinfo �Ự��Ӧ��Ϣ
	*             : iSessionReponseinfolen �Ự��Ӧ��Ϣ��		
	*      OUTPUT : pAuthenRequestinfo �����֤������Ϣ
	*             : iAuthenRequestinfolen �����֤������Ϣ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : pAuthenRequestinfo���	
	****************************************************************/
	static int createAuthenRequestinfo(unsigned char* puserid, unsigned int iuseridlen,
	                             unsigned char* pranda, unsigned int irandalen,	                             
	                             unsigned char* prandb, unsigned int irandblen,
	                             unsigned char* phashvaluenew, unsigned int ihashvaluenewlen,
	                             unsigned char* pusername, unsigned int iusernamelen,
	                             unsigned char* password,unsigned int ipasswordlen,
	                             unsigned int signArith, EVP_PKEY* pprivateKey, vector<X509*> vcertchain,
	                             unsigned char* encpassword,unsigned int& iencpasswordlen,
	                             unsigned char* psignvalue,unsigned int& isignvaluelen,
	                             unsigned char* pcertchainvalue,unsigned int& icertchainvaluelen);		
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���������֤�������������֤��Ӧ
	*       INPUT : pAuthenRequestinfo �����֤������Ϣ
	*             : iAuthenRequestinfolen �����֤������Ϣ��		
	*      OUTPUT : pAuthenReponseinfo �����֤��Ӧ��Ϣ
	*             : iAuthenReponseinfolen �����֤��Ӧ��Ϣ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : pAuthenReponseinfo���	
	****************************************************************/
	static int createAuthenReponseinfo(unsigned char* puserid, unsigned int iuseridlen,
	                             unsigned char* pranda, unsigned int irandalen,	                             
	                             unsigned char* prandb, unsigned int irandblen,	                             
	                             unsigned char* pusername, unsigned int iusernamelen,
	                             unsigned char* encpassword,unsigned int iencpasswordlen,
	                             unsigned int signArith, 	                             
	                             unsigned char* psignvalue,unsigned int isignvaluelen,
	                             unsigned char* pcertchainvalue,unsigned int icertchainvaluelen,
	                             repuserinfo_st& rep_userinfo);				
	  
 private: 
 	
 	unsigned int m_ldmpopenflag; //Ӳ���洢�򿪱�ʶ
 	//SecInfo_st m_SecurityInfo; //��ȫ��Ϣ
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��֤�û���������֤�����Ȩ��
	*       INPUT : userID �û�ID
	*				password �û�����			
	*      OUTPUT : pright	�û�Ȩ��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : 
	****************************************************************/
#ifndef  SMCLIENT
	int verifyuser(unsigned char* puserID,unsigned char* password,unsigned char* role,int& iright);		
#endif
	
	//add by yin 2011.6.1
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ñ��ش洢���û�֤��Ĺ�Կ
	*       INPUT : certType ֤�����ͣ���ͨ�û�֤��/��ȫ����Ա֤��
	*      OUTPUT : pcert	�û�Ҷ��֤��
	*     RETURNS : 0�ɹ������򷵻ش����롣
	*    CAUTIONS : ��ȡ�����ļ������ָ�����͵�֤��
	****************************************************************/
#ifndef  SMCLIENT
	int getuserCert(unsigned int certType, X509** pcert);		
#endif

};

#endif
