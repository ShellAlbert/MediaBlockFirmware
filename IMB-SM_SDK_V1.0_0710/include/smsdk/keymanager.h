/*
* Copyright (c) 2010 �й�����
* All rights reserved.
* * �ļ����ƣ�keymanager.h
* ժ    Ҫ����װ��Կ�������ز�������Ҫ�ǹ������ԿΪ���¼��ࣺ������Կ����·������Կ��KEK��
* * ��ǰ�汾��1.0
* ��    �ߣ�yinlifang
** ȡ���汾����
* ������ڣ�2010��03��19��
*/

#ifndef _KEYMANAGER_H_
#define _KEYMANAGER_H_

#include "smsdk/errornumber.h" 
#include "crypto/arithmatic.h"
#include "crypto/arithtype.h"
//#include "drmsdk/SecurityEnviroment.h"
//#include "harddriver/mb.h" 					
//#include "harddriver/mbdriver_types.h" 		
//#include "harddriver/mbdriver_ioctl.h"		//deleted by sunpeng at 20121205
#include "harddriver/c_spi.h"					//added by sunpeng at 20131205
#include "smsdk/Ccspmanager.h" 


extern const unsigned int KEYTPYE_CONTENTKEY;
extern const unsigned int KEYTPYE_LINKKEY;
//add by yin 2010.7.27 start 
extern const unsigned int LEKEY_LEN; 				//LE��Կ����
extern const unsigned int LEKEY_ATTRIBUTE_LEN;		//LE��ԿAttribute���� add by sun at 2012.06.12
extern const unsigned int LEKEY_EXPIRETIME_VALUE; 	//LE��Կ��Ч��  
extern const unsigned int KEK_LEN; 					//KEK����
extern const unsigned int SLEEPTIME_VALUE; 			//Ӳ��Ҫ����������η��ʴ洢������sleep��ʱ����
//add by yin 2010.7.27 end 


class CKeyManager
{
public:
	CKeyManager(struct cspinfo_st cspinfo, const int ldmpopenflag); 

	~CKeyManager();
		
	/****FUNCTION***************************************************
	* DESCRIPTION : ���������
	*       INPUT : reqrandlen Ҫ���ɵ����������
	*      OUTPUT : rand ���ɵ������	
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int GenerateRand (unsigned int reqrandlen, unsigned char* rand);

	/****FUNCTION***************************************************
	* DESCRIPTION : ���ɶԳƼ�����Կ����KEK
	*       INPUT : arith �㷨,ֻ֧��AES_CFB_Encrypt_128_128
	*      OUTPUT : key
	*             	keylen���ɵ���Կ�ĳ���
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int GenerateKEK (/*unsigned short arith,*/ unsigned char* key,unsigned int& keylen); 

	/****FUNCTION***************************************************
	* DESCRIPTION : ����LE��Կ��ֻ֧������AES_CTR�㷨����Կ
	*       INPUT : LEkeynum ��Ҫ���ɵ���Կ����
	*      OUTPUT : LEkeyinfo ���LEkeyinfo
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int GenerateLEKey (unsigned int LEkeynum, vector<link_key>& LEkeyinfo); 

	/****FUNCTION***************************************************
	* DESCRIPTION : �������ݽ�����Կ
	*       INPUT : arithID �㷨
	*              	LEkeynum ��Ҫ���ɵ���Կ����
	*      OUTPUT : LEkeyinfo ���LEkeyinfo
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL ע�⣬�˺������Բ�Ҫ����Ϊkdm��������set����Կ����ֱ�ӿ���load
	****************************************************************/
	int GenerateContentKey(vector<content_key>& Contentkeyinfo); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : �������ݽ�����Կ
	*       INPUT : Contentkeyinfo ������Կ��Ϣ	
	*      OUTPUT : ��
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int SetContentKey(vector<content_key> Contentkeyinfo); 
	

	/****FUNCTION***************************************************
	* DESCRIPTION : ������Կ����
	*       INPUT : key Ҫ�������Կ
	*               keylen �������Կ��
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int loadContentKey(); 

	/****FUNCTION***************************************************
	* DESCRIPTION : ���Ӽ�����Կ���뵽��ȫ�洢������LE
	*       INPUT : key Ҫ�������Կ
	*               keylen �������Կ��
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int loadLEKey(); 
	
#ifdef LEDEMO_TEST
	//add by yin 2010.5.10Ϊ����LEdemo
	/****FUNCTION***************************************************
	* DESCRIPTION : ���Ӽ�����Կ���뵽��ȫ�洢������LE
	*       INPUT : key Ҫ�������Կ
	*               keylen �������Կ��
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int loadLEKey(link_key linkkeyinfo); 
#endif

	/****FUNCTION***************************************************
	* DESCRIPTION : ���ӽ�����Կ����LD
	*       INPUT : ��
	*      OUTPUT : outlink_key ���������װ�������LD����Կ
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	* //������������Կload LD��Կ��������Կ�ǴӼ���ģ�����������LD������Կ�������Ҫ��Ӧ�Դ���Կ
	            //���м��ܣ��������LDЭ�̸�KEK����LD�ܷ�������һ����ȷ��
	****************************************************************/
//	int loadLDKey(vector<link_key>& outlink_key);

	/****FUNCTION***************************************************
	* DESCRIPTION : ��Կ���루����������Կ�����Ӽӽ�����Կ���������ӿڣ�Ϊ�������������ܺ�
	*       INPUT : key Ҫ�������Կ
	*               keylen �������Կ��
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int loadallkey (vector<link_key>& outlink_key); 

	/****FUNCTION***************************************************
	* DESCRIPTION : ����������Կ��ָ����������Կ��LE��Կ
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	*             : ������ԿӦ��������������Կ��LE��Կ
	****************************************************************/
	int destroyallkey (); 

	/****FUNCTION***************************************************
	* DESCRIPTION : ����ָ�����͵���Կ��LEKey��Contentkey��
	*       INPUT : KeyType Ҫ���ٵ���Կ����
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int destroyKeybyType (unsigned int KeyType); 	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����ָ�����͵��ض�ID��Key
	*       INPUT : KeyType Ҫ���ٵ���Կ����
	*               KeyID Ҫ���ٵ���ԿID
	*      OUTPUT : NULL
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int destroyKeybyID (unsigned int KeyType, unsigned char* KeyID); 	

	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��ѯĳ���͵�ָ��id����Կ��Ϣ
	*       INPUT : KeyType Ҫ��ѯ����Կ����
	*               pKeyID Ҫ��ѯ����Կid	 
	*      OUTPUT : pKey ��ѯ�������Կ��Ϣ	
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int QueryKeybyID(unsigned int KeyType, unsigned char* pKeyID,unsigned char* pKey);

	/****FUNCTION***************************************************
	* DESCRIPTION : ��ѯָ�����͵�������Կ��Ϣ
	*       INPUT : KeyType Ҫ��ѯ����Կ����	
	*      OUTPUT : pKey ��ѯ������ĸ�������Կ��������Ϣ	
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int QueryKeyallbyType(unsigned int KeyType,vector<unsigned char*> pKey);
	
	//add by yin 2010.5.10
	/****FUNCTION***************************************************
	* DESCRIPTION : ������·����
	*       INPUT : ��	
	*      OUTPUT : ��
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int setCinelinkEnable(void);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ȡ����·���ܣ�����cinelink
	*       INPUT : ��	
	*      OUTPUT : ��
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int setCinelinkDisable(void);
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ˮӡ����
	*       INPUT : deviceID 4���ֽڣ�8��16��������
	*      OUTPUT : fmdata ���ɵ�ˮӡ����	
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int GenerateFMData(unsigned int ideviceID, unsigned char fmdata[5]);	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ˮӡ����
	*       INPUT : fmdata 5���ֽڣ�40bit��
	*      OUTPUT : ��
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int LoadFMData (unsigned char fmdata[5]);
	
	
	//add by yin 2011.8.23
	/****FUNCTION***************************************************
	* DESCRIPTION : ˮӡ��Կ����
	*       INPUT : fmkey 16���ֽ�
	*      OUTPUT : ��
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int LoadFMKey (unsigned char fmkey[16]);
	
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����ˮӡ
	*       INPUT : NULL
	*      OUTPUT : BULL	
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int setFMEnable ();
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ȡ��ˮӡ
	*       INPUT : NULL
	*      OUTPUT : BULL	
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
//	int setFMDisable ();
	
private:  	
	int m_ldmpopenflag; 						//Ӳ���洢�򿪱�ʶ
	vector<content_key> m_Contentkey;			//�洢���ݽ�����Կ�б�
//	vector<link_key> m_link_key;				//�洢��·��Կ��Ϣ�б�
	cspinfo_st m_cspinfo;						//�洢��Ӳ���л�ȡ��csp��Ϣ
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ��Կ�洢
	*       INPUT : key Ҫ�洢����Կ
	*               keylen �洢����Կ��
	*               keytype Ҫ�洢����Կ���ͣ�������Կ���Ͳ��ò�ͬ�Ĵ洢���ԣ�
	*      OUTPUT : enckey �洢��������Կ
	*               enckeylen �洢��������Կ��
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int storekey (unsigned char* key, unsigned int keylen); 
	
	/****FUNCTION***************************************************
	* DESCRIPTION : ����ˮӡ�е�ʱ�䲿��
	*       INPUT : NULL	
	*      OUTPUT : FMtimeData �������ˮӡ�е�ʱ��ֵ
	*     RETURNS : 0��ʾ�ɹ���-1��ʾʧ��
	*    CAUTIONS : NULL
	****************************************************************/
	int calculateFMtimeData(unsigned short& FMtimeData);
};

#endif
