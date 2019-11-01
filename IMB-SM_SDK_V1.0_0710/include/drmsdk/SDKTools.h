#ifndef _SDKTOOLS_H_
#define _SDKTOOLS_H_

#ifndef WIN32        
#define MAX_PATH 255
#endif

#ifdef WIN32
#include <windows.h>   
#include <winsock.h>	//winsock.h�������windows.h֮���Ա���socket�汾��ͻ
#include <wincon.h>   
#endif 

#include <stdlib.h>   
#include <stdio.h>   

#include <iostream>
using namespace std;

const int DRM_MAX_PATH = 255;
class SDKTools
{
public:
	SDKTools();
	~SDKTools();

	/*************************************************
	Function:   ��ȡexe·��
	Input:
	Description:    
	Return:		Ӧ�ó���exe·��
	*************************************************/
	int GetAppPath(char AppPath[MAX_PATH]);
	//char* GetAppPath();

	/*************************************************
	Function:   ��ȡmac��ַ
	Input:
	Output:	mac��ַ
	Description:    
	Return:		0_�ɹ�,-1_ʧ��
	*************************************************/
	int getMAC(char arrMAC[32]);

	/*************************************************
	Function:   ����GUID
	Input:
	Output:	GUID
	Description:    
	Return:		0_�ɹ�,-1_ʧ��
	*************************************************/
	int makeGUID(char uuidbuf[64]);

	/*************************************************
	Function:   ������ת����IP��ַ
	Input:	����
	Output:	IP��ַ
	Description:    
	Return:		0_�ɹ�,-1_��������,��0_������
	*************************************************/
	int DomainNameToIPAddr(char *domainName, char& IP);

	/*************************************************
	Function:   ��IP��ַת��������
	Input:	IP��ַ
	Output:	����
	Description:    
	Return:		0_�ɹ�,-1_��������,��0_������
	*************************************************/
	int IPAddrToDomainName(char *IP, char* domainName);

	/*************************************************
	Function:   ��ȡ�����������ļ���
	Input:
	Description:    
	Return:   0��ʾ�ɹ���-1��ʾʧ�� 
	*************************************************/
	int GetFileNameAndPath(char* pFileNamePath, char* FileName);

	/*************************************************
	Function:   ��ȡ�ļ��Ƿ����
	Input:	�ļ���
	Description:    
	Return:   true��ʾ���ڣ�false��ʾ������ 
	*************************************************/
	bool FileIsExit(char* FileName);

    /*************************************************************
	* FUNCTION : ��ȡ���ػ�����ǰʱ��
	*       INPUT : NULL
	*      OUTPUT : CurrentTime ��ǰʱ��
	*     RETURNS :  0 ��ȡ�ɹ���-1 ʧ��
	*    CAUTIONS : NULL
	****************************************************************/ 
	int GetCurrentMachDateTime(char **CurrentMatchTime);

    /*************************************************************
	* FUNCTION : ���ñ��ص�ǰʱ��
	*       INPUT : CurrentTime ��ǰʱ��
	*      OUTPUT : NULL
	*     RETURNS :  0 ��ȡ�ɹ���-1 ʧ��
	*    CAUTIONS : NULL
	****************************************************************/ 
	int SetCurrentMachDateTime(char *CurrentMatchTime);
	
	/*************************************************************
	* FUNCTION : ���ļ�����·���л�ȡ�ļ���
	*       INPUT : pstrFullName �ļ�����·��
	*      OUTPUT : pstrFileName �ļ���
	*     RETURNS :  0 ��ȡ�ɹ���-1 ʧ��
	*    CAUTIONS : NULL
	****************************************************************/ 
	int GetOnlyFileName(char* pstrFullName, char* pstrFileName);
private:
	char* m_pchAppPath;	//Ӧ�ó���·��
	char* m_pchMAC;		//mac��ַ
	char* m_puchGUID;	//GUID
};

#endif	//_SDKTOOLS_H_
