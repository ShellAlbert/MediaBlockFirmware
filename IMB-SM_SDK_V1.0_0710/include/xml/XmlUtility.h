/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  xml parser 
FileName   �� XmlUtility.h
Author     �� majinshan@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� use to parse the xml document
Others     :  
History    �� 
      < Author >    			< Date >             < Modification > 
      zhangliang           2010/9/19           code workthrough
********************************************/ 
#ifndef C_XML_UTILITY
#define C_XML_UTILITY
#include <xercesc/dom/DOM.hpp>
#ifndef C_XML_UTILITY_NO_THREAD_SAFE
#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
#endif
class CXmlMemoryUnit;
class CXmlMemoryManager;
class CXmlUtility
{
	friend class CXmlMemoryUnit;
public:
	/************************************************* 
	Function   �� CXmlUtility()
	Description�� constructor of CXmlUtility class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlUtility(void);

	/************************************************* 
	Function   �� ~CXmlUtility()
	Description�� destructor of CXmlUtility class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	~CXmlUtility(void);

	/************************************************* 
	Function   �� InitPlatform()
	Description�� intitial the xml platform
	Input      �� 
	Output     �� 
	Return     �� 0:success  other:failure
	Others     :        
	*************************************************/
	static int InitPlatform(void);

	/************************************************* 
	Function   �� TerminatePlatform()
	Description�� Terminate the xml platform
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	static void TerminatePlatform(void);
private:
	static CXmlMemoryManager * gMemManager;//object of CXmlMemoryManager class
	static unsigned int uRefCount;//the count of the existed reference of InitPlatform()
#ifndef C_XML_UTILITY_NO_THREAD_SAFE
#ifdef WIN32
	static CRITICAL_SECTION g_CriticalSection;
#else
public:
	static pthread_mutex_t gMutex;//mutex for initializing and terminating platform
#endif
#endif
};

class CXmlMemoryUnit
{
	friend class CXmlMemoryManager;
public:
	/************************************************* 
	Function   �� CXmlMemoryUnit()
	Description�� constructor of CXmlMemoryUnit class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlMemoryUnit(void);
	
	/************************************************* 
	Function   �� ~CXmlMemoryUnit()
	Description�� destructor of CXmlMemoryUnit class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	virtual ~CXmlMemoryUnit(void);
protected:
	CXmlMemoryUnit *pPrev;//the prevenient XmlMemoryUnit object
	CXmlMemoryUnit *pNext;//the next XmlMemoryUnit object
	bool	registered;	//current object is in the XmlMemoryUnit list(muList) or not
	bool	managed;//the current object have the dynamic memory or not
	CXmlMemoryManager *pMemManager;//an object of the CXmlMemoryManager
	
	/************************************************* 
	Function   �� CXmlMemoryUnit()
	Description�� copy constructor of CXmlMemoryUnit class
	Input      �� memManager: an object of CXmlMemoryManager 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlMemoryUnit(const CXmlMemoryManager * const memManager);
	
	/************************************************* 
	Function   �� ConvertString()
	Description�� convert a  string from the XMLch format to the char format
	Input      �� xmlStr: a string with XMLch format
	Output     �� a string with char format 
	Return     ��
	Others     :        
	*************************************************/
	char * ConvertString(const XMLCh *xmlStr) const;
	
	/************************************************* 
	Function   �� ConvertString()
	Description�� convert a  string from the char format to the XMLCh format
	Input      �� charStr: a string with the char format
	Output     �� a string with XMLCh format
	Return     ��
	Others     :        
	*************************************************/
	XMLCh * ConvertString(const char *charStr) const;
	
	/************************************************* 
	Function   �� Release()
	Description�� a pure virtual function
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	virtual void Release(void) = 0;
};

class CXmlMemoryManager 
{
public:
	/************************************************* 
	Function   �� CXmlMemoryManager()
	Description�� constructor of CXmlMemoryManager class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlMemoryManager(void);
	
	/************************************************* 
	Function   �� ~CXmlMemoryManager()
	Description�� destructor of CXmlMemoryManager class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	virtual ~CXmlMemoryManager(void);
	
	/************************************************* 
	Function   �� InsertMU()
	Description�� insert the special CXmlMemoryUnit object to the muList
	Input      �� pMU��   a CXmlMemoryUnit object 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void InsertMU(CXmlMemoryUnit *pMU);

	/************************************************* 
	Function   �� RemoveMU()
	Description�� remove the special CXmlMemoryUnit object from the muList
	Input      �� pMU:    a CXmlMemoryUnit object
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void RemoveMU(CXmlMemoryUnit *pMU);
	
protected:
	/************************************************* 
	Function   �� ClearMemory()
	Description�� release all of the CXmlMemoryUnit object in the muList
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void ClearMemory(void);
	
private:
	CXmlMemoryUnit *muList;//a list of CXmlMemoryUnit object
#ifndef C_XML_UTILITY_NO_THREAD_SAFE
#ifdef WIN32
	CRITICAL_SECTION m_CriticalSection;
#else
public:
	pthread_mutex_t m_Mutex;//mutex
#endif
#endif
};

class CXmlString :
public CXmlMemoryUnit
{
public:
	/************************************************* 
	Function   �� CXmlString()
	Description�� constructor of CXmlString class
	Input      �� str:         a  string with char format
	              memManager:  point to a CXmlMemoryManager object
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlString(const char *str, CXmlMemoryManager *memManager);
	
	/************************************************* 
	Function   �� GetString()
	Description�� get the string with XMLCh format
	Input      �� 
	Output     �� XMLCh:   a string with XMLCh format
	Return     ��
	Others     :        
	*************************************************/
	XMLCh *GetString(void);
	
	/************************************************* 
	Function   �� ~CXmlString()
	Description�� destructor of CXmlString class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	~CXmlString(void);
private:
	XMLCh	*pXmlStr;//a string with XMLCh format
	
	/************************************************* 
	Function   �� CXmlString()
	Description�� constructor of CXmlString class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlString();
	
	/************************************************* 
	Function   �� Release()
	Description�� Release the pXmlStr
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void Release(void);
};

class CCharString :
public CXmlMemoryUnit
{
public:
	/************************************************* 
	Function   �� CCharString()
	Description�� constructor of CCharString class
	Input      �� str       :a string with XMLCh format
	              memManager:a object of CXmlMemoryManager
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CCharString(const XMLCh *str, CXmlMemoryManager *memManager);
	
	/************************************************* 
	Function   �� GetString()
	Description�� 
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	char *GetString(void);
	
	/************************************************* 
	Function   �� ~CCharString()
	Description�� destructor of CCharString class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	~CCharString(void);
	
private:
	/************************************************* 
	Function   �� CCharString()
	Description�� constructor of CCharString class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CCharString();
	
	/************************************************* 
	Function   �� Release()
	Description�� do noting
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void Release(void);	
	
	char	*pCharStr;//a string with char format
};

#endif
