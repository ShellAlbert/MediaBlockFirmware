/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  xml parser 
FileName   £º XmlCollection.h
Author     £º majinshan@dadimedia.com
Date       £º 10/03/03
Version    £º v1.0
Description£º use to parse the xml document
Others     :  
History    £º 
      < Author >    			< Date >             < Modification > 
      zhangliang           2010/9/19           code workthrough
********************************************/ 

#ifndef XML_COLLECTIONS
#define XML_COLLECTIONS

#include <vector>
#include <xercesc/dom/DOM.hpp>

#include "xml/XmlUtility.h"
class CXmlNode;

class CXmlResultSet : public CXmlMemoryUnit
{
public:
	/************************************************* 
	Function   £º CXmlResultSet()
	Description£º constructor of CXmlResultSet class
	Input      £º result:an object of DOMXPathResult
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlResultSet(xercesc::DOMXPathResult * result = NULL);
	
	/************************************************* 
	Function   £º CreateRS()
	Description£º creat a CXmlResultSet object
	Input      £º result    :an object of CXmlResultSet
	              memManager:an object of CXmlMemoryManager
	Output     £º 
	Return     £º an object of CXmlResultSet
	Others     :        
	*************************************************/
	static CXmlResultSet * CreateRS(xercesc::DOMXPathResult * result = NULL, const CXmlMemoryManager * const memManager = NULL);
	
	/************************************************* 
	Function   £º ~CXmlResultSet()
	Description£º destructor of CXmlResultSet class
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	~CXmlResultSet(void);
	
	/************************************************* 
	Function   £º GetResult()
	Description£º get the special node 
	Input      £º index:the index of the node
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/	
	CXmlNode *GetResult(unsigned int index);
	
	/************************************************* 
	Function   £º operator []()
	Description£º redefine of the operator []
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlNode *operator [](unsigned int index);
	
	/************************************************* 
	Function   £º Size()
	Description£º get the size of the nodeList 
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	unsigned int Size(void)
	{
		return size;
	}
	
private:
	/************************************************* 
	Function   £º CXmlResultSet()
	Description£º constructor of CXmlMemoryUnit class
	Input      £º result :an object of DOMXPathResult
	              manager:an object of CXmlMemoryManager
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	CXmlResultSet(xercesc::DOMXPathResult * result, const CXmlMemoryManager * const manager);

	/************************************************* 
	Function   £º operator=()
	Description£º redefine of the "=" operator
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	void operator=(CXmlResultSet &);

	/************************************************* 
	Function   £º Release()
	Description£º clear the nodeList
	Input      £º 
	Output     £º 
	Return     £º
	Others     :        
	*************************************************/
	void Release(void);
	
	std::vector <CXmlNode *> nodeList;//node list
	unsigned int size;//size of the node list	
};

#endif
