/******************************************************************
�ļ����ƣ�IniFile.h
�ļ�˵����Ini�ļ������ඨ��
��    �ߣ�������
��дʱ�䣺2009-09-10
******************************************************************/
#ifndef INIFILE_H
#define INIFILE_H

#include "BinSearchTree.h"

#define  LISTSEPARATOR     ';'

#define  KEYVALUELEN       128     //keyֵ��󳤶�
#define  LINELEN           256     
#define  FILEPATHLEN       128   

//ini�ļ��������д�����
enum ErrCode
{
	NoError=-1,            //�ɹ�����ѯ����Ҫ��¼
	ParaError=-2,          //���������������
	CApiError=-3,          //C Api ��������ʧ��
	BufferShortage=-4,     //���ղ�ѯ����Ļ������ռ䲻��
	NotFound=-5,           //û�ҵ�Ŀ����
	InifileCanNotOpen=-6,  //û�ҵ�Ŀ����
	InifileFormatError=-7,  //û�ҵ�Ŀ����
	InvalidSectionName=-8,  //������Ч
	InvalidKeyName=-9,      //KEY����Ч
	InvalidKeyValue=-10     //KEYֵ��Ч
};

//key�ڵ�ṹ
typedef struct _KeyNode
{
	char Name[NAMELEN];
	struct _KeyNode *right;
	struct _KeyNode *left;
	struct _KeyNode *parent;
	char Value[KEYVALUELEN];
}KeyNode;

//Section�ڵ�ṹ
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
	
	
    int LoadIniFile(char *NewFilePath);               //���ڴ��м���ini�ļ�
    
	int GetKeyValue(              //��ȡ����ֵ
	/*in*/  char *SectionName,    //����section��
	/*in*/  char *KeyName,        //����key��
	/*in*/  char *DefaultValue,	  //���û�в鵽����������keyֵ�����õ�Ĭ��ֵ
	/*in*/  int  BufferLen,       //���շ���keyֵ�Ļ�������С
	/*out*/ char *KeyValueBuffer  //���շ���keyֵ�Ļ�������ַ
	);
 
	int GetSectionNames(           //��ȡ�����ļ���section�б�
	/*in*/  int  BufferLen,        //���շ���Section Names�Ļ�������С
	/*out*/ char *ValueBuffer      //���շ���ection Names�Ļ�������ַ
	);

	int GetSection(                //��ȡָ��section����Ŀ���б�
	/*in*/  char *SectionName,     //����section��
	/*in*/  int  BufferLen,        //���շ���Sectionֵ�Ļ�������С
	/*out*/ char *ValueBuffer      //���շ���Sectionֵ�Ļ�������ַ
	);

	int WriteSection(	            //д������section
	/*in*/  char *SectionName,      //����section��
	/*in*/  char *KeyAndValueString //Ҫд���"key=value"�б�
	);

	int WriteKeyValue(
	/*in*/  char *SectionName,       //����section��
	/*in*/  char *KeyName,           //Ҫд���key��
	/*in*/  char *KeyValue           //Ҫд���key=value"�б�
	);

	int PrintIniTree();              //�ڱ�׼����ϴ�ӡ��ini�ļ���������

private:
	
	int FlushIniFile();              //��Ӳ���ϸ���ini�ļ�

	int FlushSection(                    //��FlushIniFile���ã�����ini�ļ��е�section
	/*in*/ 	FILE *FileFD,                //�򿪵�ini�ļ�������
	/*in*/ 	SectionNode *SectionPoint);  //section���ĸ��ڵ�ָ��

	int FlusheyAndValue (            //��FlushSection���ã�����ini�ļ��е�keyֵ��
	/*in*/ FILE  *FileFD,            //�򿪵�ini�ļ�������
	/*in*/ KeyNode *KeyNodePoint);   //keyֵ���ĸ��ڵ�ָ��

	void PrintSection(                     //�ڱ�׼����ϴ�ӡsection
	/*in*/ SectionNode *SectionNodePoint); //section���ĸ��ڵ�ָ��

	void PrintKeyAndValue(           //�ڱ�׼����ϴ�ӡkeyֵ��
	/*in*/ KeyNode *KeyNodePoint);   //keyֵ���ĸ��ڵ�ָ��
 
	void FreeIniFile();              //�ͷ��ڴ��м��ص�ini�ļ���Ⱥ

	void FreeSection(                       //�ͷ��ڴ��м��ص�section��
	/*in*/ SectionNode *SectionNodePoint);  //section���ĸ��ڵ�ָ��

	SectionNode *InsertSection(      //��section���в���һ��section�ڵ�
	/*in*/ char *SectionName);       //Ҫ�����section��

	int InsertKey(                    //��keyֵ���в���һ���ڵ�
	/*in*/ SectionNode *SectionPoint, //keyֵ������section��ָ��
	/*in*/ char *KeyName,             //key��
	/*in*/ char *KeyValue);           //keyֵ

	SectionNode *IsSectionInIni(      //ȷ��һ��Section�Ƿ���ini�ļ���
	/*in*/ char *SectionName);        //Section��

	KeyNode *IsKeyInSection(           //ȷ��һ��key�Ƿ���section��
	/*in*/ SectionNode *SectionPoint,  //keyֵ������section��ָ��
	/*in*/ char *KeyName);             //key��

	int DeleteSection(                 //ɾ��һ��section�ڵ�
	/*in*/ char *SectionName);         //Ҫɾ����section��

	int DeleteKey(                     //ɾ��һ��key�ڵ�
	/*in*/ SectionNode  *SectionPoint, //keyֵ������section��ָ��
	/*in*/ char *KeyName);             //key��

	int ModifyKey(                      //�޸��ڴ���keyֵ
	/*in*/ SectionNode  *SectionPoint,  //keyֵ������section��ָ��
	/*in*/ char *KeyName,               //key��
	/*in*/ char *KeyValue);             //keyֵ

	int JoinKeyAndValueList(            //����keyֵ�б�
	/*in*/ KeyNode *KeyNodePoint,       //key�ڵ�ָ��
	/*in*/ int BufferLen,               //����keyֵ�б�������С
	/*out*/char *ValueBuffer);          //����keyֵ�б�������ַ

	int JoinSectionList(                //����section�б�
	/*in*/ SectionNode *NodePoint,      //section�ڵ�ָ��
	/*in*/ int BufferLen,               //����section�б�������С
	/*out*/char *ValueBuffer);          //����section�б�������ַ
	
	inline int IsLegalChar(char NewChar);    //�������������Ƿ�Ϸ� ����1�Ϸ� 0�Ƿ�
	
  int IsLegalSectionName(       //����������Ч��
  /*in*/char *SectionName);     
  
  int IsLegalKeyName(           //���KEY����Ч��
  /*in*/char *KeyName);  
  
  int IsLegalKeyValue(          //���keyֵ����Ч��
  /*in*/char *KeyValue);	
  	
	char FilePath[FILEPATHLEN];      //Ŀ��ini�ļ�·��
	SectionNode  *IniTree;           //�������ڴ���ini�ļ��γɵ����ĸ�
};

#endif


