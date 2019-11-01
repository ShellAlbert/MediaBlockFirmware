/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  xml parser 
FileName   £º XmlUtility.h
Author     £º majinshan@dadimedia.com
Date       £º 10/03/01
Version    £º v1.0
Description£º use to parse the xml document
Others     :  
History    £º 
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
	Function   £º CXmlUtility()
	Description£º constructor of CXmlUtility class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlUtility(void);

	/************************************************* 
	Function   £º ~CXmlUtility()
	Description£º destructor of CXmlUtility class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	~CXmlUtility(void);

	/************************************************* 
	Function   £º InitPlatform()
	Description£º intitial the xml platform
	Input      £º 
	Output     £º 
	Return     £º 0:success  other:failure
	Others     :        
	*************************************************/
	static int InitPlatform(void);

	/************************************************* 
	Function   £º TerminatePlatform()
	Description£º Terminate the xml platform
	Input      £º 
	Output     £º 
	Return     £º
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
	Function   £º CXmlMemoryUnit()
	Description£º constructor of CXmlMemoryUnit class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlMemoryUnit(void);
	
	/************************************************* 
	Function   £º ~CXmlMemoryUnit()
	Description£º destructor of CXmlMemoryUnit class
	Input      £º 
	Output     £º 
	Return     £º
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
	Function   £º CXmlMemoryUnit()
	Description£º copy constructor of CXmlMemoryUnit class
	Input      £º memManager: an object of CXmlMemoryManager 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlMemoryUnit(const CXmlMemoryManager * const memManager);
	
	/************************************************* 
	Function   £º ConvertString()
	Description£º convert a  string from the XMLch format to the char format
	Input      £º xmlStr: a string with XMLch format
	Output     £º a string with char format 
	Return     £º
	Others     :        
	*************************************************/
	char * ConvertString(const XMLCh *xmlStr) const;
	
	/************************************************* 
	Function   £º ConvertString()
	Description£º convert a  string from the char format to the XMLCh format
	Input      £º charStr: a string with the char format
	Output     £º a string with XMLCh format
	Return     £º
	Others     :        
	*************************************************/
	XMLCh * ConvertString(const char *charStr) const;
	
	/************************************************* 
	Function   £º Release()
	Description£º a pure virtual function
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	virtual void Release(void) = 0;
};

class CXmlMemoryManager 
{
public:
	/************************************************* 
	Function   £º CXmlMemoryManager()
	Description£º constructor of CXmlMemoryManager class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlMemoryManager(void);
	
	/************************************************* 
	Function   £º ~CXmlMemoryManager()
	Description£º destructor of CXmlMemoryManager class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	virtual ~CXmlMemoryManager(void);
	
	/************************************************* 
	Function   £º InsertMU()
	Description£º insert the special CXmlMemoryUnit object to the muList
	Input      £º pMU£º   a CXmlMemoryUnit object 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	void InsertMU(CXmlMemoryUnit *pMU);

	/************************************************* 
	Function   £º RemoveMU()
	Description£º remove the special CXmlMemoryUnit object from the muList
	Input      £º pMU:    a CXmlMemoryUnit object
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	void RemoveMU(CXmlMemoryUnit *pMU);
	
protected:
	/************************************************* 
	Function   £º ClearMemory()
	Description£º release all of the CXmlMemoryUnit object in the muList
	Input      £º 
	Output     £º 
	Return     £º
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
	Function   £º CXmlString()
	Description£º constructor of CXmlString class
	Input      £º str:         a  string with char format
	              memManager:  point to a CXmlMemoryManager object
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlString(const char *str, CXmlMemoryManager *memManager);
	
	/************************************************* 
	Function   £º GetString()
	Description£º get the string with XMLCh format
	Input      £º 
	Output     £º XMLCh:   a string with XMLCh format
	Return     £º
	Others     :        
	*************************************************/
	XMLCh *GetString(void);
	
	/************************************************* 
	Function   £º ~CXmlString()
	Description£º destructor of CXmlString class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	~CXmlString(void);
private:
	XMLCh	*pXmlStr;//a string with XMLCh format
	
	/************************************************* 
	Function   £º CXmlString()
	Description£º constructor of CXmlString class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlString();
	
	/************************************************* 
	Function   £º Release()
	Description£º Release the pXmlStr
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	void Release(void);
};

class CCharString :
public CXmlMemoryUnit
{
public:
	/************************************************* 
	Function   £º CCharString()
	Description£º constructor of CCharString class
	Input      £º str       :a string with XMLCh format
	              memManager:a object of CXmlMemoryManager
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CCharString(const XMLCh *str, CXmlMemoryManager *memManager);
	
	/************************************************* 
	Function   £º GetString()
	Description£º 
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	char *GetString(void);
	
	/************************************************* 
	Function   £º ~CCharString()
	Description£º destructor of CCharString class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	~CCharString(void);
	
private:
	/************************************************* 
	Function   £º CCharString()
	Description£º constructor of CCharString class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CCharString();
	
	/************************************************* 
	Function   £º Release()
	Description£º do noting
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	void Release(void);	
	
	char	*pCharStr;//a string with char format
};

#endif
