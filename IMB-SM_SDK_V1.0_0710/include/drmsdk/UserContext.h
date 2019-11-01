/*
* Copyright (c) 2007 �й�����
* All rights reserved.
* �ļ����ƣ�usercontext.h
* ժ    Ҫ���ṩ�û���Ϣ���ù���
* * ��ǰ�汾��3.0
* ��    �ߣ�sm
* ������ڣ�2010��06��07��
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
	* DESCRIPTION : ���캯��
	*       INPUT : a_pPuchUserName ��¼���û���
	*				a_pPuchPassword ��¼����
	*				a_pUserP12File �û�p12�ļ���
	*				a_pDeviceP12File devicep 12�ļ���
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	CUserContext(); //add by yin 
	~CUserContext(); //add by yin 2010.7.29
	
	CUserContext(const unsigned char* a_pUserP12File, const unsigned char* a_pUserP12Password,
		const unsigned char* a_pDeviceP12File,const unsigned char* a_pDeviceP12Password,
		const unsigned char* a_ptrustcaP12File,const unsigned char* a_ptrustcaP12Password);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : �������캯��
	*       INPUT : a_pOtherUserCtx ���ڳ�ʼ����ʵ��
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	explicit CUserContext(const CUserContext& a_pOtherUserCtx);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ���������
	*       INPUT : a_pOtherUserCtx ���ڸ�ʵ����ֵ����һ��ʵ��
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : ��
	****************************************************************/
	const CUserContext& operator=(const CUserContext& a_pOtherUserCtx);
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�û�p12�ļ���
	*       INPUT : a_ppUserP12FileName ��ȡ�����ļ���
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : a_ppUserP12FileName���ڴ��ⲿ���䣬��СMAX_FILENAME_LEN
	****************************************************************/	
	void GetuserP12FileName(unsigned char* a_ppUserP12FileName) const;
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�û�p12����
	*       INPUT : a_ppPassWord ��ȡ��������
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : a_ppPassWord���ڴ��ⲿ���䣬��СMAX_PASSWORD_LEN
	****************************************************************/
	void GetUserP12PassWord(unsigned char* a_ppPassWord) const;	

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�豸p12�ļ���
	*       INPUT : a_ppDeviceP12FileName ��ȡ�����ļ���
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : a_ppDeviceP12FileName���ڴ��ⲿ���䣬��СMAX_FILENAME_LEN
	****************************************************************/
	void GetDeviceP12FileName(unsigned char* a_ppDeviceP12FileName) const;	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡ�豸p12����
	*       INPUT : a_ppPassWord ��ȡ��������
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : a_ppPassWord���ڴ��ⲿ���䣬��СMAX_PASSWORD_LEN
	****************************************************************/
	void GetDeviceP12PassWord(unsigned char* a_ppPassWord) const;
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡtls������p12�ļ���
	*       INPUT : a_ptrustcaP12FileName ��ȡ�����ļ���
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : a_ptrustcaP12FileName���ڴ��ⲿ���䣬��СMAX_FILENAME_LEN
	****************************************************************/
	void GettrustcaP12FileName(unsigned char* a_ptrustcaP12FileName) const;	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ȡtls������p12����
	*       INPUT : a_ppPassWord ��ȡ��������
	*      OUTPUT : ��
	*     RETURNS : ��
	*    CAUTIONS : a_ppPassWord���ڴ��ⲿ���䣬��СMAX_PASSWORD_LEN
	****************************************************************/
	void GettrustcaP12PassWord(unsigned char* a_ppPassWord) const;
	
//add by yin 2010.7.29 start
	/****FUNCTION***************************************************
	* DESCRIPTION : �����û�p12�ļ���
	*       INPUT : a_ppUserP12FileName �û�p12�ļ���
	*               i_UserP12FileNamelen �û�p12�ļ�������
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : 
	****************************************************************/
	int SetuserP12FileName(unsigned char* a_ppUserP12FileName,unsigned int i_UserP12FileNamelen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : �����û�p12����
	*       INPUT : a_ppPassWord �û�p12������
	*               i_PassWordlen �û�p12�����볤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : 
	****************************************************************/
	int SetUserP12PassWord(unsigned char* a_ppPassWord,unsigned int i_PassWordlen);
	
		/****FUNCTION***************************************************
	* DESCRIPTION : �����豸p12�ļ���
	*       INPUT : a_ppDeviceP12FileName �豸p12�ļ���
	*               i_DeviceP12FileNamelen �豸p12�ļ�������
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : 
	****************************************************************/
	int SetDeviceP12FileName(unsigned char* a_ppDeviceP12FileName,unsigned int i_DeviceP12FileNamelen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : �����豸p12����
	*       INPUT : a_ppPassWord �豸p12������
	*               i_PassWordlen �豸p12�����볤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : 
	****************************************************************/
	int SetDeviceP12PassWord(unsigned char* a_ppPassWord,unsigned int i_PassWordlen);
	
		/****FUNCTION***************************************************
	* DESCRIPTION : ����tls������p12�ļ���
	*       INPUT : a_pptrustcaP12FileName tls������p12�ļ���
	*               i_trustcaP12FileNamelen tls������p12�ļ�������
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : 
	****************************************************************/
	int SettrustcaP12FileName(unsigned char* a_pptrustcaP12FileName,unsigned int i_trustcaP12FileNamelen);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����tls������p12����
	*       INPUT : a_ppPassWord tls������p12������
	*               i_PassWordlen tls������p12�����볤��
	*      OUTPUT : ��
	*     RETURNS : 0�ɹ� ��0ʧ��
	*    CAUTIONS : 
	****************************************************************/
	int SettrustcaP12PassWord(unsigned char* a_ppPassWord,unsigned int i_PassWordlen);
//add by yin 2010.7.29 end

private:
		
	unsigned char m_chUserP12Password[MAX_PASSWORD_LEN];	//�û�p12����
	unsigned char m_chUserP12File[MAX_FILENAME_LEN];		//user p12�ļ���
	unsigned char m_chDeviceP12File[MAX_FILENAME_LEN];	//device p12�ļ���
	unsigned char m_chDeviceP12Password[MAX_PASSWORD_LEN];	//�豸p12����
	unsigned char m_chtrustcaP12File[MAX_FILENAME_LEN];   //tls������p12
	unsigned char m_chtrustcaP12Password[MAX_PASSWORD_LEN];//tls������p12����
	
};//�ýṹ�������ļ���ȡ

#endif