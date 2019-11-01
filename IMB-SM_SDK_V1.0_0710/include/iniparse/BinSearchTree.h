/******************************************************************
文件名称：BinSearchTree.h
文件说明：搜索二叉树操作函数声明
作    者：胡卫华
编写时间：2009-09-10
******************************************************************/
#ifndef BINSERCHTREE_H
#define BINSERCHTREE_H

#define NAMELEN    128            //节点名长度

//节点结构
typedef struct _Node
{
	char Name[NAMELEN];            //节点名
	struct _Node *right;           //左子节点指针
	struct _Node *left;            //右子节点指针
	struct _Node *parent;          //父节点指针
}NODE;

int  DeleteAllNode(                //删除所有节点
/*in*/ void *ObjectTreeRoot);      //树根指针

int  DeleteNode(                   //删除一个节点
/*in*/ void **ObjectNodePoint);    //树中指向目标节点指针地址

int  AddNode(                      //添加一个节点
/*in*/ void *ObjectTreeRoot,       //树根指针
/*in*/ void *NewNode);             //新节点指针

int  SearchNode(                   //搜索一个节点，函数返回符合条件节点个数
/*in*/ void *ObjectTreeRoot,       //树根指针
/*in*/ char *ObjectName,           //目标节点名
/*out*/void **FirstNodePoint);     //存储第一个符合条件的节点指针

int  TreeIsEmpty(                  //检验树是否为空， 0为空，1非空
/*in*/ void *ObjectTreeRoot);      //树根指针
#endif


