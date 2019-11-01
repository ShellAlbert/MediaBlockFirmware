/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  xml parser 
FileName   �� XmlCollection.h
Author     �� majinshan@dadimedia.com
Date       �� 10/03/03
Version    �� v1.0
Description�� use to parse the xml document
Others     :  
History    �� 
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
	Function   �� CXmlResultSet()
	Description�� constructor of CXmlResultSet class
	Input      �� result:an object of DOMXPathResult
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlResultSet(xercesc::DOMXPathResult * result = NULL);
	
	/************************************************* 
	Function   �� CreateRS()
	Description�� creat a CXmlResultSet object
	Input      �� result    :an object of CXmlResultSet
	              memManager:an object of CXmlMemoryManager
	Output     �� 
	Return     �� an object of CXmlResultSet
	Others     :        
	*************************************************/
	static CXmlResultSet * CreateRS(xercesc::DOMXPathResult * result = NULL, const CXmlMemoryManager * const memManager = NULL);
	
	/************************************************* 
	Function   �� ~CXmlResultSet()
	Description�� destructor of CXmlResultSet class
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	~CXmlResultSet(void);
	
	/************************************************* 
	Function   �� GetResult()
	Description�� get the special node 
	Input      �� index:the index of the node
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/	
	CXmlNode *GetResult(unsigned int index);
	
	/************************************************* 
	Function   �� operator []()
	Description�� redefine of the operator []
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlNode *operator [](unsigned int index);
	
	/************************************************* 
	Function   �� Size()
	Description�� get the size of the nodeList 
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	unsigned int Size(void)
	{
		return size;
	}
	
private:
	/************************************************* 
	Function   �� CXmlResultSet()
	Description�� constructor of CXmlMemoryUnit class
	Input      �� result :an object of DOMXPathResult
	              manager:an object of CXmlMemoryManager
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	CXmlResultSet(xercesc::DOMXPathResult * result, const CXmlMemoryManager * const manager);

	/************************************************* 
	Function   �� operator=()
	Description�� redefine of the "=" operator
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void operator=(CXmlResultSet &);

	/************************************************* 
	Function   �� Release()
	Description�� clear the nodeList
	Input      �� 
	Output     �� 
	Return     ��
	Others     :        
	*************************************************/
	void Release(void);
	
	std::vector <CXmlNode *> nodeList;//node list
	unsigned int size;//size of the node list	
};

#endif
