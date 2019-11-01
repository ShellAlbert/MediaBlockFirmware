/*
* Copyright (c) 2007 中国数码
* All rights reserved.
* * 文件名称：CAuthentication.h
* 摘    要：身份认证操作
* * 当前版本：3.0
* 作    者：yinlifang
** 取代版本：无
* 原作者  ：drm
* 完成日期：2010年4月22日
* 修改日期：2010年9月16日、2011年5月31日
*/

#ifndef _CAUTHENTICATION_H_
#define _CAUTHENTICATION_H_

//#define SMCLIENT
#include "smsdk/errornumber.h" 
#include "crypto/arithmatic.h" 
#include "crypto/arithtype.h" 
//添加安全环境头文件
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

//权限定义
extern const unsigned int EXECUTE_KDM_RIGHT;
extern const unsigned int SET_TIME_RIGHT;
extern const unsigned int ZEROIZE_RIGHT;
extern const unsigned int FIRMWARE_UPDATE_RIGHT;
//extern const unsigned int SET_CSPS_RIGHT;	  	//del by yin 2011.5.31
//extern const unsigned int RESET_CSPS_RIGHT;	//add by yin 2010.7.14 重置权限 //del by yin 2011.5.31
extern const unsigned int IMPORT_CERT_RIGHT;	//Import Cert right  //add by yin 2011.5.31
extern const unsigned int QUERY_CERT_RIGHT;	  	//Query Cert right   //add by yin 2011.5.31
extern const unsigned int GET_LOGINFO_RIGHT;	//add by yin 2010.9.19 获取日志权限
extern const unsigned int GET_AUDIT_RIGHT;		//add by yin 2010.9.19 审计权限

//角色定义 add by yin 2011.8.9
extern const unsigned int USER_ROLE;     		//用户角色
extern const unsigned int OFFICER_ROLE;     	//安全管理员角色 

//身份认证请求信息结构体
struct requserinfo_st{
	unsigned char puserID[30];
	unsigned char pusername[18];	// modify by yin 2010.5.7 12-->18 实际有效长最大16，变化原因加了base
	unsigned char password[14];		// modify by yin 2010.5.7 8-->14 实际有效长最大12
	unsigned char role[16]; 		//add by yin 2011.5.31
	unsigned int signArith;
	unsigned int signvaluelen;
	unsigned char* signvalue;
  //unsigned char* certchainvalue;	//叶子证书即可，note by yin 2011.6.2  
                                    // add note by yin 2011.8.11为日后支持多个用户可保留此字段 
                                    //del by yin 2011.8.12
};

//身份认证响应信息结构体
struct repuserinfo_st{
	unsigned char userID[30]; 		//modify by yin 2010.5.7 30-->58 
	int right;	
};

//权限信息结构体
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
	* DESCRIPTION : 生成身份认证请求
	*       INPUT : userID 用户ID
	*               pusername 用户名	              
	*				password 用户口令,注意口令中间不允许出现字符/0，末尾除外。			
	*      OUTPUT : req_userinfo	身份认证请求字段信息
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : req_userinfo中的signvalue和certchainvalue是函数内部分配内存，但需外部释放	
	****************************************************************/
	static int createAuthenticationRequestinfo(unsigned char* puserID,unsigned char* pusername,
	                                    unsigned char* password,unsigned char* prole,unsigned int signArith,
	                                    EVP_PKEY* pprivateKey,/* vector<X509*> vcertchain,*/
	                                    requserinfo_st& req_userinfo);	//modify by yin 2010.9.19 add static
	                                    //modify by yin 2011.5.31 add prole
	                                      //modify by yin 2011.8.12 del vcertchain
	                                      
	/****FUNCTION***************************************************
	* DESCRIPTION : 生成登出请求的签名值
	*       INPUT : userID 用户ID
	*               prole  用户角色
	*				signArith 签名算法
	*               pprivateKey 签名私钥
	*      OUTPUT : signvaluelen 签名值长度
	*               signvalue 签名值
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : signvalue 为内部分配内存，外部释放。add by yin 2011.9.19
	****************************************************************/
	int creatLogoutRequestsignvalue(unsigned char* puserID,
	                        unsigned char* prole, 
	                        unsigned int signArith,
	                        EVP_PKEY* pprivateKey,
	                        unsigned int& signvaluelen,
	                        unsigned char** signvalue);	
	
#ifndef  SMCLIENT                                    
	/****FUNCTION***************************************************
	* DESCRIPTION : 处理身份认证请求并生成响应信息
	*       INPUT : req_userinfo	身份认证请求字段信息
	*      OUTPUT : rep_userinfo	身份认证响应字段信息
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	
	int proessAuthenticationRequestinfo(requserinfo_st req_userinfo,repuserinfo_st& rep_userinfo);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 解析身份认证响应
	*       INPUT : userID 用户ID
	*				password 用户口令			
	*      OUTPUT : req_userinfo	身份认证请求字段信息
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	int proessAuthenticationReponseinfo(repuserinfo_st rep_userinfo,rightinfo_st& right);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 处理登出请求
	*       INPUT : userID 用户ID
	*               prole  用户角色
    *				signArith 签名算法
	*               signvaluelen 签名值长度
	*               signvalue 签名值
	*               certchainvalue 证书链值（包含叶子）		
	*      OUTPUT : NULL	无
	*     RETURNS : 0成功，否则返回错误码。
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
	* DESCRIPTION : 设置用户权限
	*       INPUT : roletype 用户角色类型，OFFICER_ROLE为是安全管理员，USER_ROLE为普通用户			
	*      OUTPUT : right	权限
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	static int setuserright(int roletype,int& right);	//modify by yin 2010.9.19 add static
	
	//add by yin 2010.9.16 for officer authentication base on socket
	/****FUNCTION***************************************************
	* DESCRIPTION : 生成会话请求
	*       INPUT : puserID 用户ID
	*             : iuserIDlen 用户ID长		
	*      OUTPUT : pranda 随机数ah
	*             : irandalen 随机数a长度
	*             : phashvalue 用户ID与随机数a的摘要值
	*             : ihashvaluelen 用户ID与随机数a的摘要值长
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	static int createSessionRequestinfo(unsigned char* puserid, unsigned int iuseridlen,
	                             unsigned char* pranda, unsigned int& irandalen,
	                             unsigned char* phashvalue, unsigned int& ihashvaluelen);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 处理会话请求并生成会话请求响应
	*       INPUT : puserID 用户ID
	*             : iuserIDlen 用户ID长		
	*             : pranda 随机数a
	*             : irandalen 随机数a长度
	*             : phashvalue 用户ID与随机数的摘要值
	*             : ihashvaluelen 用户ID与随机数的摘要值长
	*      OUTPUT : prandb 随机数b
	*             : irandblen 随机数b长度
	*             : phashvaluenew 用户ID与随机数a、随机数b的摘要值
	*             : ihashvaluenewlen 用户ID与随机数a、随机数b的摘要值长
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
	static int createSessionReponseinfo(unsigned char* puserid, unsigned int iuseridlen,
	                             unsigned char* pranda, unsigned int irandalen,
	                             unsigned char* phashvalue, unsigned int ihashvaluelen,
	                             unsigned char* prandb, unsigned int& irandblen,
	                             unsigned char* phashvaluenew, unsigned int& ihashvaluenewlen);	
	                             
	/****FUNCTION***************************************************
	* DESCRIPTION : 处理会话请求响应并生成身份认证请求
	*       INPUT : pSessionReponseinfo 会话响应信息
	*             : iSessionReponseinfolen 会话响应信息长		
	*      OUTPUT : pAuthenRequestinfo 身份认证请求信息
	*             : iAuthenRequestinfolen 身份认证请求信息长
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : pAuthenRequestinfo最大长	
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
	* DESCRIPTION : 处理身份认证请求并生成身份认证响应
	*       INPUT : pAuthenRequestinfo 身份认证请求信息
	*             : iAuthenRequestinfolen 身份认证请求信息长		
	*      OUTPUT : pAuthenReponseinfo 身份认证响应信息
	*             : iAuthenReponseinfolen 身份认证响应信息长
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : pAuthenReponseinfo最大长	
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
 	
 	unsigned int m_ldmpopenflag; //硬件存储打开标识
 	//SecInfo_st m_SecurityInfo; //安全信息
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 验证用户并返回认证结果及权限
	*       INPUT : userID 用户ID
	*				password 用户口令			
	*      OUTPUT : pright	用户权限
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 
	****************************************************************/
#ifndef  SMCLIENT
	int verifyuser(unsigned char* puserID,unsigned char* password,unsigned char* role,int& iright);		
#endif
	
	//add by yin 2011.6.1
	/****FUNCTION***************************************************
	* DESCRIPTION : 获得本地存储的用户证书的公钥
	*       INPUT : certType 证书类型：普通用户证书/安全管理员证书
	*      OUTPUT : pcert	用户叶子证书
	*     RETURNS : 0成功，否则返回错误码。
	*    CAUTIONS : 读取配置文件并获得指定类型的证书
	****************************************************************/
#ifndef  SMCLIENT
	int getuserCert(unsigned int certType, X509** pcert);		
#endif

};

#endif
