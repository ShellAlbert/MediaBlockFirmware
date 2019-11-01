/******************************************************************
文件名称：IniFile.h
文件说明：Ini文件操作类定义
作    者：胡卫华
编写时间：2009-09-10
******************************************************************/
#ifndef INIFILE_H
#define INIFILE_H

#include "BinSearchTree.h"

#define  LISTSEPARATOR     ';'

#define  KEYVALUELEN       128     //key值最大长度
#define  LINELEN           256     
#define  FILEPATHLEN       128   

//ini文件解析所有错误码
enum ErrCode
{
	NoError=-1,            //成功，查询到想要记录
	ParaError=-2,          //函数输入参数错误
	CApiError=-3,          //C Api 函数运行失败
	BufferShortage=-4,     //接收查询结果的缓冲区空间不足
	NotFound=-5,           //没找到目标项
	InifileCanNotOpen=-6,  //没找到目标项
	InifileFormatError=-7,  //没找到目标项
	InvalidSectionName=-8,  //段名无效
	InvalidKeyName=-9,      //KEY名无效
	InvalidKeyValue=-10     //KEY值无效
};

//key节点结构
typedef struct _KeyNode
{
	char Name[NAMELEN];
	struct _KeyNode *right;
	struct _KeyNode *left;
	struct _KeyNode *parent;
	char Value[KEYVALUELEN];
}KeyNode;

//Section节点结构
typedef struct _SectionNode
{
	char Name[NAMELEN];
	struct _SectionNode *right;
	struct _SectionNode *left;
	struct _SectionNode *parent;
	KeyNode *KeyTreeRoot;
}SectionNode;


class IniFile
{
public:

	//IniFile(char *NewFilePath);
	 IniFile();
	~IniFile();	
	
	
    int LoadIniFile(char *NewFilePath);               //在内存中加载ini文件
    
	int GetKeyValue(              //获取配置值
	/*in*/  char *SectionName,    //配置section名
	/*in*/  char *KeyName,        //配置key名
	/*in*/  char *DefaultValue,	  //如果没有查到符合条件的key值，采用的默认值
	/*in*/  int  BufferLen,       //接收返回key值的缓冲区大小
	/*out*/ char *KeyValueBuffer  //接收返回key值的缓冲区地址
	);
 
	int GetSectionNames(           //获取配置文件中section列表
	/*in*/  int  BufferLen,        //接收返回Section Names的缓冲区大小
	/*out*/ char *ValueBuffer      //接收返回ection Names的缓冲区地址
	);

	int GetSection(                //获取指定section中项目的列表
	/*in*/  char *SectionName,     //配置section名
	/*in*/  int  BufferLen,        //接收返回Section值的缓冲区大小
	/*out*/ char *ValueBuffer      //接收返回Section值的缓冲区地址
	);

	int WriteSection(	            //写入整块section
	/*in*/  char *SectionName,      //配置section名
	/*in*/  char *KeyAndValueString //要写入的"key=value"列表
	);

	int WriteKeyValue(
	/*in*/  char *SectionName,       //配置section名
	/*in*/  char *KeyName,           //要写入的key名
	/*in*/  char *KeyValue           //要写入的key=value"列表
	);

	int PrintIniTree();              //在标准输出上打印出ini文件所有内容

private:
	
	int FlushIniFile();              //在硬盘上更新ini文件

	int FlushSection(                    //供FlushIniFile调用，更新ini文件中的section
	/*in*/ 	FILE *FileFD,                //打开的ini文件描述符
	/*in*/ 	SectionNode *SectionPoint);  //section树的根节点指针

	int FlusheyAndValue (            //供FlushSection调用，更新ini文件中的key值对
	/*in*/ FILE  *FileFD,            //打开的ini文件描述符
	/*in*/ KeyNode *KeyNodePoint);   //key值树的根节点指针

	void PrintSection(                     //在标准输出上打印section
	/*in*/ SectionNode *SectionNodePoint); //section树的根节点指针

	void PrintKeyAndValue(           //在标准输出上打印key值对
	/*in*/ KeyNode *KeyNodePoint);   //key值树的根节点指针
 
	void FreeIniFile();              //释放内存中加载的ini文件树群

	void FreeSection(                       //释放内存中加载的section树
	/*in*/ SectionNode *SectionNodePoint);  //section树的根节点指针

	SectionNode *InsertSection(      //在section树中插入一个section节点
	/*in*/ char *SectionName);       //要插入的section名

	int InsertKey(                    //在key值树中插入一个节点
	/*in*/ SectionNode *SectionPoint, //key值树所属section的指针
	/*in*/ char *KeyName,             //key名
	/*in*/ char *KeyValue);           //key值

	SectionNode *IsSectionInIni(      //确定一个Section是否在ini文件中
	/*in*/ char *SectionName);        //Section名

	KeyNode *IsKeyInSection(           //确定一个key是否在section中
	/*in*/ SectionNode *SectionPoint,  //key值树所属section的指针
	/*in*/ char *KeyName);             //key名

	int DeleteSection(                 //删除一个section节点
	/*in*/ char *SectionName);         //要删除的section名

	int DeleteKey(                     //删除一个key节点
	/*in*/ SectionNode  *SectionPoint, //key值树所属section的指针
	/*in*/ char *KeyName);             //key名

	int ModifyKey(                      //修改内存中key值
	/*in*/ SectionNode  *SectionPoint,  //key值树所属section的指针
	/*in*/ char *KeyName,               //key名
	/*in*/ char *KeyValue);             //key值

	int JoinKeyAndValueList(            //构造key值列表
	/*in*/ KeyNode *KeyNodePoint,       //key节点指针
	/*in*/ int BufferLen,               //接收key值列表缓冲区大小
	/*out*/char *ValueBuffer);          //接收key值列表缓冲区地址

	int JoinSectionList(                //构造section列表
	/*in*/ SectionNode *NodePoint,      //section节点指针
	/*in*/ int BufferLen,               //接收section列表缓冲区大小
	/*out*/char *ValueBuffer);          //接收section列表缓冲区地址
	
	inline int IsLegalChar(char NewChar);    //检查变量名命名是否合法 返回1合法 0非法
	
  int IsLegalSectionName(       //检查段名的有效性
  /*in*/char *SectionName);     
  
  int IsLegalKeyName(           //检查KEY的有效性
  /*in*/char *KeyName);  
  
  int IsLegalKeyValue(          //检查key值的有效性
  /*in*/char *KeyValue);	
  	
	char FilePath[FILEPATHLEN];      //目标ini文件路径
	SectionNode  *IniTree;           //加载在内存中ini文件形成的树的根
};

#endif


