/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  xml parser 
FileName   ： XmlDocument.h
Author     ： majinshan@dadimedia.com
Date       ： 10/03/05
Version    ： v1.0
Description： use to parse the xml document
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
      zhangliang           2010/9/19           code workthrough 
********************************************/ 
#ifndef C_XML_DOCUMENT
#define C_XML_DOCUMENT

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

#include "xml/XmlCollections.h"
#include "xml/XmlUtility.h"

#include <string>
enum
{
	VF_DO_NAME_SPACE =					0x0001,
	VF_CREATE_ENTITY_REFERENCE_NODE =	0x0002,
	VF_CACHE_GRAMMER =					0x0004,
	VF_DO_SCHEMA =						0x0008,
	VF_SCHEMA_FULL_CHECK =				0x0010,
	VF_VALIDATE_SCHEMA	=				0x0020,
};

class DOMTreeErrorHandler : public xercesc::ErrorHandler, public CXmlMemoryUnit
{
public:
	/************************************************* 
	Function   ： warning()
	Description： printf the warning formed during pasrsing a xml document and put it into the waringList 
	Input      ： warnings: a warning while parsing a xml document
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void warning(const xercesc::SAXParseException& warnings);
	
	/************************************************* 
	Function   ： resetErrors()
	Description： do nothing
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void resetErrors();
	
	/************************************************* 
	Function   ： error()
	Description： printf the error formed during pasrsing a xml document and put it into the errorList
	Input      ： errors: an error while parsing a xml document         
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void error(const xercesc::SAXParseException& errors);
		
	/************************************************* 
	Function   ： fatalError()
	Description： printf the fatalError formed during pasrsing a xml document and put it into the fatalErrorList
	Input      ： fatalErrors: a fatalError while parsing a xml document 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void fatalError(const xercesc::SAXParseException& fatalErrors);
	
	/************************************************* 
	Function   ： GetFatalErrors()
	Description： get the fatalErrors formed while parsing a xml document
	Input      ： 
	Output     ： fatalErrorList
	Return     ：
	Others     :        
	*************************************************/
	const std::vector <std::string>&GetFatalErrors(void);
		
	/************************************************* 
	Function   ： GetErrors()
	Description： get the errors formed while parsing a xml document
	Input      ： 
	Output     ： errorList
	Return     ：
	Others     :        
	*************************************************/
	const std::vector <std::string>&GetErrors(void);
	
	/************************************************* 
	Function   ： GetWarnings()
	Description： get the warnings formed while parsing a xml document
	Input      ： 
	Output     ： warningList
	Return     ：
	Others     :        
	*************************************************/
	const std::vector <std::string>&GetWarnings(void);
		
private:
	std::vector <std::string> fatalErrorList;//faltal error list
	std::vector <std::string> errorList;//error list
	std::vector <std::string> warningList;//warning list
	
	/************************************************* 
	Function   ： Release()
	Description： do nothing
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/	
	void Release(void){};
};


class CXmlAttribute
{
public:
	/************************************************* 
	Function   ： CXmlAttribute()
	Description： constructor of CXmlAttribute class
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CXmlAttribute(void);
	
	/************************************************* 
	Function   ： CXmlAttribute()
	Description： constructor of CXmlAttribute class
	Input      ： aName : the name of the Attribute
	              aValue: the value of the Attribute
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CXmlAttribute(const char *aName, const char *aValue);
	
	/************************************************* 
	Function   ： ~CXmlAttribute()
	Description： destructor of CXmlAttribute class
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	~CXmlAttribute(void);
	
	/************************************************* 
	Function   ： GetAttributeName()
	Description： get the name of the Attribute
	Input      ： 
	Output     ： the name of the Attribute 
	Return     ：
	Others     :        
	*************************************************/
	const char * GetAttributeName(void);
	
	/************************************************* 
	Function   ： GetAttributeValue()
	Description： get the value of the Attribute
	Input      ： 
	Output     ： the value of the Attribute
	Return     ：
	Others     :        
	*************************************************/
	const char * GetAttributeValue(void);
	
protected:
	std::string name;//name of Attribute
	std::string value;//value of Attribute
};

class CXmlNode;
class CXmlDocument : public CXmlMemoryUnit, public CXmlMemoryManager
{
public:
	/************************************************* 
	Function   ： CXmlDocument()
	Description： constructor of CXmlDocument class
	Input      ： rootName:the name of root node
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CXmlDocument(const char * rootName = NULL);
	
	/************************************************* 
	Function   ： ~CXmlDocument()
	Description： destructor of CXmlDocument class
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	~CXmlDocument(void);
	
	/************************************************* 
	Function   ： ParseString()
	Description： parse a string
	Input      ： xmlString:a string of a xml file
	Output     ： 
	Return     ： 0:success  other:failure
	Others     :        
	*************************************************/
	int ParseString(const char * xmlString);
	
	/************************************************* 
	Function   ： ParseFile()
	Description： parse a xml file
	Input      ： path:the path of a xml file
	Output     ： 
	Return     ： 0:success  other:failure
	Others     :        
	*************************************************/
	int ParseFile(const char * path);

	/*	简单XPATH语法
		/  --- 路径分隔符
		// --- 任意路径
		.  --- 当前路径
		*  --- 所有元素
		:  --- 名称空间分隔符(例如 xmlns:element)
	*/
	/************************************************* 
	Function   ： Search()
	Description： Search a node according as the path
	Input      ： xpathSimple:the path of the node
	Output     ： 
	Return     ：  
	Others     :        
	*************************************************/
	CXmlResultSet *Search(const char * xpathSimple) const;

  /************************************************* 
	Function   ： GetRootNode()
	Description： get the root node of a xml document
	Input      ： 
	Output     ： 
	Return     ： the root node of a xml document
	Others     :        
	*************************************************/
	CXmlNode *GetRootNode(void) const;

	/************************************************* 
	Function   ： LoadSchemaFile()
	Description： load a schema file
	Input      ： path：path of the schema file
	Output     ： 
	Return     ： 0:success  other:failure
	Others     :        
	*************************************************/
	int LoadSchemaFile(const char * path);

	/************************************************* 
	Function   ： LoadDtdFile()
	Description： load a dtd file
	Input      ： path：path of the dtd file
	Output     ： 
	Return     ： 0:success  other:failure
	Others     :        
	*************************************************/
	int LoadDtdFile(const char * path);

	/************************************************* 
	Function   ： SetValidate()
	Description： set the flags valid
	Input      ： flag:no less then one flag
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void SetValidate(unsigned int flag);

	/************************************************* 
	Function   ： operator=()
	Description： redefine of "=" operator
	Input      ： a object of CXmlDocument
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void operator=(CXmlDocument &);
	
	/************************************************* 
	Function   ： CopyNode()
	Description： copy a node
	Input      ： srcNode   : the source node
	              isDeepCopy: deeply copy or not
	Output     ：  
	Return     ： destination node
	Others     :        
	*************************************************/
	CXmlNode * CopyNode(const CXmlNode * srcNode, bool isDeepCopy);

	/************************************************* 
	Function   ： GetFatalErrors()
	Description： get the fatalErrors
	Input      ： 
	Output     ： a list of fatalErrors
	Return     ：
	Others     :        
	*************************************************/
	const std::vector <std::string>&GetFatalErrors(void);
	
	/************************************************* 
	Function   ： GetErrors()
	Description： get the errors
	Input      ： 
	Output     ： 
	Return     ： a list of errors
	Others     :        
	*************************************************/
	const std::vector <std::string>&GetErrors(void);
		
	/************************************************* 
	Function   ： GetWarnings()
	Description：  get the warnings
	Input      ： 
	Output     ： 
	Return     ： a list of warnings
	Others     :        
	*************************************************/
	const std::vector <std::string>&GetWarnings(void);

	/************************************************* 
	Function   ： CreateNewNode()
	Description： creat a new node
	Input      ： name: the name of the node
	Output     ： 
	Return     ： the new node
	Others     :        
	*************************************************/
	CXmlNode * CreateNewNode(const char *name);

protected:
	xercesc::DOMDocument *pDoc;	//a object of DOMDocument
	xercesc::XercesDOMParser *pDomParser;//a object of XercesDOMParser
	xercesc::DOMElement *pRootNode;//a object of DOMElement
	DOMTreeErrorHandler *pErrorHandler;//a object of DOMTreeErrorHandler
	CXmlNode * pRootXmlNode;//root node

private:
	/************************************************* 
	Function   ： Release()
	Description： release the resouces
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void Release(void);
	
	bool isDocParsed;//??

};

class CXmlNode : public CXmlMemoryUnit
{
	/************************************************* 
	Function   ： CopyNode()
	Description： copy a node
	Input      ： srcNode   : the source node
	              isDeepCopy: deep copy or not
	Output     ： 
	Return     ： the destination node
	Others     :        
	*************************************************/
	friend CXmlNode * CXmlDocument::CopyNode(const CXmlNode * srcNode, bool isDeepCopy);

public:
	/************************************************* 
	Function   ： CXmlNode()
	Description： constructor of CXmlNode class
	Input      ： node：an object of DOMElement
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CXmlNode(xercesc::DOMElement * node);

	/************************************************* 
	Function   ： ~CXmlNode()
	Description： destructor of CXmlNode class
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	~CXmlNode(void);

	/************************************************* 
	Function   ： GetAttribute()
	Description： get the value of the attribute 
	Input      ： name: name of the attribute 
	Output     ： 
	Return     ： value of the attribute
	Others     :        
	*************************************************/
	const char * GetAttribute(const char * name) const;
	
	/************************************************* 
	Function   ： GetTextValue()
	Description： get the node value
	Input      ： 
	Output     ： 
	Return     ： node value 
	Others     :        
	*************************************************/
	const char * GetTextValue(void) const;

	/************************************************* 
	Function   ： CreateNode()
	Description： create a node
	Input      ： node      ：object of DOMElement 
								memManager：object of CXmlMemoryManager
	Output     ： 
	Return     ： a node
	Others     :        
	*************************************************/
	static CXmlNode * CreateNode(xercesc::DOMElement * node, const CXmlMemoryManager * const memManager);

	/************************************************* 
	Function   ： WriteToString()
	Description： convert the node to a string with char format
	Input      ： isCanonicalize：the returned string is Canonicalize or not
	Output     ： 
	Return     ： a string with char format
	Others     :        
	*************************************************/
	const char * WriteToString(bool isCanonicalize = false);

	/************************************************* 
	Function   ： SetTextValue()
	Description： set the node value
	Input      ： 
	Output     ： 
	Return     ：0:success  other:failure
	Others     :        
	*************************************************/
	int SetTextValue(const char * strValue);

	/************************************************* 
	Function   ： SetAttribute()
	Description： set the attribute value of the node
	Input      ： name : name of the attribute
								value: value of the attribute
	Output     ： 
	Return     ：0:success  other:failure
	Others     :        
	*************************************************/
	int SetAttribute(const char * name, const char * value);

	/************************************************* 
	Function   ： InsertChild()
	Description： insert a node befor the specail node
	Input      ： newNode: the node prepared to insert
	              refNode: the node whoes position will be replace by the new node
	Output     ： 
	Return     ：0:success  other:failure
	Others     :        
	*************************************************/
	int InsertChild(CXmlNode * newNode, CXmlNode * refNode = NULL);

	/************************************************* 
	Function   ： GetFirstChild()
	Description： get the first child of the node
	Input      ： 
	Output     ： 
	Return     ：first child of the node
	Others     :        
	*************************************************/
	CXmlNode * GetFirstChild(void);

	/************************************************* 
	Function   ： GetNextSibling()
	Description： get the next silbing node
	Input      ： 
	Output     ： 
	Return     ： the next silbing node
	Others     :        
	*************************************************/
	CXmlNode * GetNextSibling(void);

	/************************************************* 
	Function   ： GetNodeName()
	Description： get the node name 
	Input      ： 
	Output     ： 
	Return     ：node name
	Others     :        
	*************************************************/
	const char * GetNodeName(void);

	/************************************************* 
	Function   ： GetAttributeList()
	Description： get attribute list of the node
	Input      ： 
	Output     ： 
	Return     ： attributes list
	Others     :        
	*************************************************/
	std::vector <CXmlAttribute> GetAttributeList(void);

	/************************************************* 
	Function   ： RemoveChild()
	Description： remove a child of the node
	Input      ： child: a child of the node
	Output     ： 
	Return     ： 0:success  other:failure
	Others     :        
	*************************************************/
	int RemoveChild(const CXmlNode * child);

	/************************************************* 
	Function   ： RemoveAttribute()
	Description： remove a node attribute
	Input      ： name:the attribute name
	Output     ： 
	Return     ：0:success  other:failure
	Others     :        
	*************************************************/
	int RemoveAttribute(const char * name);
	
	/************************************************* 
	Function   ： InsertChild()
	Description： insert a child to the node
	Input      ： nodeName:the node name that to been inserted
	Output     ： 
	Return     ： 0:success  other:failure
	Others     :        
	*************************************************/
	int InsertChild(const char * nodeName);
	
	/************************************************* 
	Function   ： getParent()
	Description： get the parent of the node
	Input      ： 
	Output     ： 
	Return     ： the parent of the node
	Others     :        
	*************************************************/
	CXmlNode *GetParent(void);
	
	/*	简单XPATH语法
		/  --- 路径分隔符
		// --- 任意路径
		.  --- 当前路径
		*  --- 所有元素
		:  --- 名称空间分隔符(例如 xmlns:element)
	*/
	/************************************************* 
	Function   ： Search()
	Description： Search the object of CXmlResultSet according as the path
	Input      ： xpathSimple:node path
	Output     ： 
	Return     ： a object of CXmlResultSet 
	Others     :        
	*************************************************/
	CXmlResultSet *Search(const char * xpathSimple) const;

protected:
	xercesc::DOMElement *pNode;//an object of DOMElement
		
private:
	/************************************************* 
	Function   ： CXmlNode()
	Description： constructor of CXmlNode class
	Input      ： node   :an object of DOMElement
	              manager:an object of CXmlMemoryManager
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CXmlNode(xercesc::DOMElement * node, const CXmlMemoryManager * const manager);
		
	/************************************************* 
	Function   ： operator=()
	Description： redefine of the "=" operator
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void operator=(CXmlNode &);

	/************************************************* 
	Function   ： Release()
	Description： do nothing
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	void Release(void);
};

#endif
