/******************************************************************
File name: LNode.c
Date: 2016/6
Description: ������غ���
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*����ԭ�ͣ�void MakeNode(int index)									*/
/*����������������index												*/
/*�� �� ֵ����													   		*/
/*�������ܣ�����һ������Ϊ0�Ľ��									*/
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
/*����ԭ�ͣ�void AddNode(x,y)						*/
/*�������������ͷ���ָ�룬���������ָ��								*/
/*�� �� ֵ����													   		*/
/*�������ܣ�������ͷ����һ��[x][y]����ˮ�ݲ�����ˮ��										*/
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
/*����ԭ�ͣ�void RejoinNode(int x,int y)								*/
/*���������X����,Y����													*/
/*�� �� ֵ����													   		*/
/*�������ܣ�ȥ��������һ�����					*/
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
/*����ԭ�ͣ�void clearHeaders()											*/
/*�����������															*/
/*�� �� ֵ����													   		*/
/*�������ܣ��ͷ����н��												*/
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


