/*
* Copyright (c) 2007 中国数码
* All rights reserved.
* 文件名称：usercontext.h
* 摘    要：提供用户信息配置功能
* * 当前版本：3.0
* 作    者：sm
* 完成日期：2010年06月07日
*/
#ifndef _USERCONTEXT_H_
#define _USERCONTEXT_H_

#include <iostream>
#include <string>
using namespace std;

const unsigned int MAX_FILENAME_LEN = 256;
const unsigned int MAX_PASSWORD_LEN = 12;
const unsigned int FILE_HMACVALUE_LEN = 20;

class CUserContext
{
public:
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 构造函数
	*       INPUT : a_pPuchUserName 登录的用户名
	*				a_pPuchPassword 登录密码
	*				a_pUserP12File 用户p12文件名
	*				a_pDeviceP12File devicep 12文件名
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	CUserContext(); //add by yin 
	~CUserContext(); //add by yin 2010.7.29
	
	CUserContext(const unsigned char* a_pUserP12File, const unsigned char* a_pUserP12Password,
		const unsigned char* a_pDeviceP12File,const unsigned char* a_pDeviceP12Password,
		const unsigned char* a_ptrustcaP12File,const unsigned char* a_ptrustcaP12Password);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 拷贝构造函数
	*       INPUT : a_pOtherUserCtx 用于初始化新实例
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	explicit CUserContext(const CUserContext& a_pOtherUserCtx);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 运算符重载
	*       INPUT : a_pOtherUserCtx 用于给实例赋值的另一个实例
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : 无
	****************************************************************/
	const CUserContext& operator=(const CUserContext& a_pOtherUserCtx);
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取用户p12文件名
	*       INPUT : a_ppUserP12FileName 获取到的文件名
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : a_ppUserP12FileName的内存外部分配，最小MAX_FILENAME_LEN
	****************************************************************/	
	void GetuserP12FileName(unsigned char* a_ppUserP12FileName) const;
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取用户p12密码
	*       INPUT : a_ppPassWord 获取到的密码
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : a_ppPassWord的内存外部分配，最小MAX_PASSWORD_LEN
	****************************************************************/
	void GetUserP12PassWord(unsigned char* a_ppPassWord) const;	

	/****FUNCTION***************************************************
	* DESCRIPTION : 获取设备p12文件名
	*       INPUT : a_ppDeviceP12FileName 获取到的文件名
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : a_ppDeviceP12FileName的内存外部分配，最小MAX_FILENAME_LEN
	****************************************************************/
	void GetDeviceP12FileName(unsigned char* a_ppDeviceP12FileName) const;	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取设备p12密码
	*       INPUT : a_ppPassWord 获取到的密码
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : a_ppPassWord的内存外部分配，最小MAX_PASSWORD_LEN
	****************************************************************/
	void GetDeviceP12PassWord(unsigned char* a_ppPassWord) const;
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取tls信任链p12文件名
	*       INPUT : a_ptrustcaP12FileName 获取到的文件名
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : a_ptrustcaP12FileName的内存外部分配，最小MAX_FILENAME_LEN
	****************************************************************/
	void GettrustcaP12FileName(unsigned char* a_ptrustcaP12FileName) const;	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 获取tls信任链p12密码
	*       INPUT : a_ppPassWord 获取到的密码
	*      OUTPUT : 无
	*     RETURNS : 无
	*    CAUTIONS : a_ppPassWord的内存外部分配，最小MAX_PASSWORD_LEN
	****************************************************************/
	void GettrustcaP12PassWord(unsigned char* a_ppPassWord) const;
	
//add by yin 2010.7.29 start
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置用户p12文件名
	*       INPUT : a_ppUserP12FileName 用户p12文件名
	*               i_UserP12FileNamelen 用户p12文件名长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 
	****************************************************************/
	int SetuserP12FileName(unsigned char* a_ppUserP12FileName,unsigned int i_UserP12FileNamelen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置用户p12密码
	*       INPUT : a_ppPassWord 用户p12的密码
	*               i_PassWordlen 用户p12的密码长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 
	****************************************************************/
	int SetUserP12PassWord(unsigned char* a_ppPassWord,unsigned int i_PassWordlen);
	
		/****FUNCTION***************************************************
	* DESCRIPTION : 设置设备p12文件名
	*       INPUT : a_ppDeviceP12FileName 设备p12文件名
	*               i_DeviceP12FileNamelen 设备p12文件名长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 
	****************************************************************/
	int SetDeviceP12FileName(unsigned char* a_ppDeviceP12FileName,unsigned int i_DeviceP12FileNamelen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置设备p12密码
	*       INPUT : a_ppPassWord 设备p12的密码
	*               i_PassWordlen 设备p12的密码长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 
	****************************************************************/
	int SetDeviceP12PassWord(unsigned char* a_ppPassWord,unsigned int i_PassWordlen);
	
		/****FUNCTION***************************************************
	* DESCRIPTION : 设置tls信任链p12文件名
	*       INPUT : a_pptrustcaP12FileName tls信任链p12文件名
	*               i_trustcaP12FileNamelen tls信任链p12文件名长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 
	****************************************************************/
	int SettrustcaP12FileName(unsigned char* a_pptrustcaP12FileName,unsigned int i_trustcaP12FileNamelen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : 设置tls信任链p12密码
	*       INPUT : a_ppPassWord tls信任链p12的密码
	*               i_PassWordlen tls信任链p12的密码长度
	*      OUTPUT : 无
	*     RETURNS : 0成功 非0失败
	*    CAUTIONS : 
	****************************************************************/
	int SettrustcaP12PassWord(unsigned char* a_ppPassWord,unsigned int i_PassWordlen);
//add by yin 2010.7.29 end

private:
		
	unsigned char m_chUserP12Password[MAX_PASSWORD_LEN];	//用户p12密码
	unsigned char m_chUserP12File[MAX_FILENAME_LEN];		//user p12文件名
	unsigned char m_chDeviceP12File[MAX_FILENAME_LEN];	//device p12文件名
	unsigned char m_chDeviceP12Password[MAX_PASSWORD_LEN];	//设备p12密码
	unsigned char m_chtrustcaP12File[MAX_FILENAME_LEN];   //tls信任链p12
	unsigned char m_chtrustcaP12Password[MAX_PASSWORD_LEN];//tls信任链p12密码
	
};//该结构从配置文件获取

#endif