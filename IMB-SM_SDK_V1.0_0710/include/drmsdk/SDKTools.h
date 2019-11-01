#ifndef _SDKTOOLS_H_
#define _SDKTOOLS_H_

#ifndef WIN32        
#define MAX_PATH 255
#endif

#ifdef WIN32
#include <windows.h>   
#include <winsock.h>	//winsock.h必须放在windows.h之后，以避免socket版本冲突
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
	Function:   获取exe路径
	Input:
	Description:    
	Return:		应用程序exe路径
	*************************************************/
	int GetAppPath(char AppPath[MAX_PATH]);
	//char* GetAppPath();

	/*************************************************
	Function:   获取mac地址
	Input:
	Output:	mac地址
	Description:    
	Return:		0_成功,-1_失败
	*************************************************/
	int getMAC(char arrMAC[32]);

	/*************************************************
	Function:   生成GUID
	Input:
	Output:	GUID
	Description:    
	Return:		0_成功,-1_失败
	*************************************************/
	int makeGUID(char uuidbuf[64]);

	/*************************************************
	Function:   将域名转换成IP地址
	Input:	域名
	Output:	IP地址
	Description:    
	Return:		0_成功,-1_域名错误,非0_错误码
	*************************************************/
	int DomainNameToIPAddr(char *domainName, char& IP);

	/*************************************************
	Function:   将IP地址转换成域名
	Input:	IP地址
	Output:	域名
	Description:    
	Return:		0_成功,-1_域名错误,非0_错误码
	*************************************************/
	int IPAddrToDomainName(char *IP, char* domainName);

	/*************************************************
	Function:   获取完整的配置文件名
	Input:
	Description:    
	Return:   0表示成功，-1表示失败 
	*************************************************/
	int GetFileNameAndPath(char* pFileNamePath, char* FileName);

	/*************************************************
	Function:   获取文件是否存在
	Input:	文件名
	Description:    
	Return:   true表示存在，false表示不存在 
	*************************************************/
	bool FileIsExit(char* FileName);

    /*************************************************************
	* FUNCTION : 获取本地机器当前时间
	*       INPUT : NULL
	*      OUTPUT : CurrentTime 当前时间
	*     RETURNS :  0 获取成功，-1 失败
	*    CAUTIONS : NULL
	****************************************************************/ 
	int GetCurrentMachDateTime(char **CurrentMatchTime);

    /*************************************************************
	* FUNCTION : 设置本地当前时间
	*       INPUT : CurrentTime 当前时间
	*      OUTPUT : NULL
	*     RETURNS :  0 获取成功，-1 失败
	*    CAUTIONS : NULL
	****************************************************************/ 
	int SetCurrentMachDateTime(char *CurrentMatchTime);
	
	/*************************************************************
	* FUNCTION : 从文件完整路径中获取文件名
	*       INPUT : pstrFullName 文件完整路径
	*      OUTPUT : pstrFileName 文件名
	*     RETURNS :  0 获取成功，-1 失败
	*    CAUTIONS : NULL
	****************************************************************/ 
	int GetOnlyFileName(char* pstrFullName, char* pstrFileName);
private:
	char* m_pchAppPath;	//应用程序路径
	char* m_pchMAC;		//mac地址
	char* m_puchGUID;	//GUID
};

#endif	//_SDKTOOLS_H_
