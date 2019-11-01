/******************************************************************
�ļ����ƣ�BinSearchTree.h
�ļ�˵��������������������������
��    �ߣ�������
��дʱ�䣺2009-09-10
******************************************************************/
#ifndef BINSERCHTREE_H
#define BINSERCHTREE_H

#define NAMELEN    128            //�ڵ�������

//�ڵ�ṹ
typedef struct _Node
{
	char Name[NAMELEN];            //�ڵ���
	struct _Node *right;           //���ӽڵ�ָ��
	struct _Node *left;            //���ӽڵ�ָ��
	struct _Node *parent;          //���ڵ�ָ��
}NODE;

int  DeleteAllNode(                //ɾ�����нڵ�
/*in*/ void *ObjectTreeRoot);      //����ָ��

int  DeleteNode(                   //ɾ��һ���ڵ�
/*in*/ void **ObjectNodePoint);    //����ָ��Ŀ��ڵ�ָ���ַ

int  AddNode(                      //���һ���ڵ�
/*in*/ void *ObjectTreeRoot,       //����ָ��
/*in*/ void *NewNode);             //�½ڵ�ָ��

int  SearchNode(                   //����һ���ڵ㣬�������ط��������ڵ����
/*in*/ void *ObjectTreeRoot,       //����ָ��
/*in*/ char *ObjectName,           //Ŀ��ڵ���
/*out*/void **FirstNodePoint);     //�洢��һ�����������Ľڵ�ָ��

int  TreeIsEmpty(                  //�������Ƿ�Ϊ�գ� 0Ϊ�գ�1�ǿ�
/*in*/ void *ObjectTreeRoot);      //����ָ��
#endif


