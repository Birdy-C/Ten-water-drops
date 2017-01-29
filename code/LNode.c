/******************************************************************
File name: LNode.c
Date: 2016/6
Description: 链表相关函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*函数原型：void MakeNode(int index)									*/
/*传入参数：结点数据index												*/
/*返 回 值：无													   		*/
/*函数功能：创建一个数据为0的结点									*/
/************************************************************************/
void MakeNode()
{
	LNode *node;
	node = (LNode *)malloc(sizeof(LNode));
	node->x = 0;
	node->y = 0;
	node->tx = 0;
	node->ty = 0;
	node->next = NULL;
	theApp.head = node;
	
}

/************************************************************************/
/*函数原型：void AddNode(x,y)						*/
/*传入参数：链表头结点指针，待入链结点指针								*/
/*返 回 值：无													   		*/
/*函数功能：在链表头加入一个[x][y]处的水泡产生的水花										*/
/************************************************************************/
void AddNode(LNode* pnode) {
	LNode *node;
	node = theApp.head;

	if (pnode!=NULL && node!=NULL) {
		while (node->next != NULL) { node = node->next; }
		node->next = pnode;
		pnode->next = NULL;

	}
}

/************************************************************************/
/*函数原型：void RejoinNode(int x,int y)								*/
/*传入参数：X坐标,Y坐标													*/
/*返 回 值：空													   		*/
/*函数功能：去掉链表中一个结点					*/
/************************************************************************/
void deleteNode(LNode* pnode) {
	LNode * node;
	node = theApp.head;
	if (pnode != NULL && node != NULL) {
		while (node != NULL)
		{
			if (node->next == pnode)
			{
				node->next = pnode->next;
				free(pnode);
				break;
			}
			node = node->next;
		}
	}
}
/************************************************************************/
/*函数原型：void clearHeaders()											*/
/*传入参数：无															*/
/*返 回 值：无													   		*/
/*函数功能：释放所有结点												*/
/************************************************************************/
void clearHeaders() {
	LNode *node;
	LNode *pnode= theApp.head;
	while (pnode)
	{
		node= pnode->next;
		free(pnode);
		pnode = node;
	}

}


