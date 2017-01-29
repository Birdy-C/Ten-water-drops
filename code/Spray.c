/******************************************************************
File name: Button.c
Date: 2016/6
Description:	ˮ����غ���
Author: XY,CLx
*******************************************************************/
#include "water.h"
/************************************************************************/
/*����ԭ�ͣ�int bubbleWidth()											*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ȡ����ˮ���Ŀ��											*/
/************************************************************************/
int sprayWidth()
{	return theApp.imgSpray.mWidth;
}
/************************************************************************/

/*����ԭ�ͣ�int bubbleHeight() 											*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ȡ����ˮ���ĸ߶�											*/
/************************************************************************/
int sprayHeight()
{

	return theApp.imgSpray.mHeight /6;//ͼ����6�����
}


/************************************************************************/
/*����ԭ�ͣ�void mainSprayEvent()								        */
/*�����������													 		*/
/*�� �� ֵ����										 					*/
/*�������ܣ�����ˮ�������¼�����										*/
/************************************************************************/
void mainSprayEvent() 
{
		LNode*node;
		LNode*pnode;
		node = theApp.head->next;
		while (node!=NULL) {
			pnode = node->next;
			sprayEvent(node);
			node = pnode;
		}
		if (theApp.head->next==NULL) theApp.gamestate = sNormal;

}

/************************************************************************/
/*����ԭ�ͣ�void sprayEvent(LNode* p) 									*/
/*���������ˮ����Ӧ��ַ												*/
/*�� �� ֵ����						   									*/
/*�������ܣ�ˮ���¼�����												*/
/************************************************************************/
void sprayEvent(LNode* p) {
	if (p == NULL)return;
	if (p->state == 0 ) deleteNode(p);
	if (p->state > 2) 
	{
		p->time++;
		if(p->time==3)  deleteNode(p);
	}
	if (p->state <= 2) {
		p->x = p->x + p->tx;
		p->y = p->y + p->ty;
	}
	if (p->tx > 0)
	{
		if (isCrashingL(p->x + sprayWidth() / 2))
		{
			if (changeX(p->x) +1>5) {
				p->state = sCrash1;
				if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_crash, 0);
				
			}
			else if (theApp.bubbles[changeX(p->x) + 1][changeX(p->y)].slevel!=0)
			{
				theApp.bubbles[changeX(p->x) + 1][changeX(p->y)].slevel++;
				p->state = sDisapear;
			}
		}
	}
	if (p->tx< 0)
	{
		if (isCrashingL(p->x - sprayWidth() / 2))
		{
			if (changeX(p->x) == 0) {
				p->state = sCrash2;
				if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_crash, 0);
			}
			else if (theApp.bubbles[changeX(p->x) - 1][changeX(p->y)].slevel !=0)
			{
				theApp.bubbles[changeX(p->x) - 1][changeX(p->y)].slevel++;
				p->state = sDisapear;
				
			}
		}
	}
	if (p->ty > 0)
	{
		if (isCrashingL(p->y + sprayWidth() / 2))
		{
			if (changeX(p->y)==5) {
				p->state = sCrash4;
				if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_crash, 0);
			}
			else if (theApp.bubbles[changeX(p->x) ][changeX(p->y)+ 1].slevel !=0)
			{
				theApp.bubbles[changeX(p->x) ][changeX(p->y)+ 1].slevel++;
				p->state = sDisapear;
			}
		}
	}
	if (p->ty < 0)
	{
		if (isCrashingL(p->y - sprayWidth() / 2))
		{
			if (changeX(p->y) == 0) {
				p->state = sCrash3;
				if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_crash, 0);
			}
			else if (theApp.bubbles[changeX(p->x)][changeX(p->y) - 1].slevel !=0)
			{
				theApp.bubbles[changeX(p->x)][changeX(p->y) - 1].slevel++;
				p->state = sDisapear;
			}
		}
	}

}
/************************************************************************/
/*����ԭ�ͣ�int changeX(int i)								            */
/*�������������ֵi												 		*/
/*�� �� ֵ������ֵi��Ӧ�ĸ������						 				*/
/*�������ܣ�����ֵתΪ��Ӧ������� 										*/
/************************************************************************/
int changeX(int i) {
	return (i - blankHeight())/bubbleHeight();
}

/************************************************************************/
/*����ԭ�ͣ�isCrashingL(int x)								            */
/*���������LNode* p											 		*/
/*�� �� ֵ��TRUE/FALSE									 				*/
/*�������ܣ��ж�ˮ���Ƿ�����������										*/
/************************************************************************/
int isCrashingL(int x) {

	if ((x - blankHeight()) % bubbleHeight() == 0) 
		return TRUE;
	return FALSE;

}
/************************************************************************/
/*����ԭ�ͣ�void boom(int i, int j)									    */
/*���������int i, int j										 		*/
/*�� �� ֵ����										 					*/
/*�������ܣ�����[i][j]��ˮ��ը���¼� 									*/
/************************************************************************/

void boom(int i, int j) {
	LNode *node;
	int x, y;
	x = bubbleWidth()*i + bubbleWidth() / 2 + blankHeight();
	y = bubbleWidth()*j + bubbleWidth() / 2 + blankHeight();
	node = (LNode *)malloc(sizeof(LNode));
	node->x = x;
	node->y = y;
	node->tx = 5;
	node->ty = 0;
	node->state = sHorizon;
	node->time = 0;
	AddNode(node);

	node = (LNode *)malloc(sizeof(LNode));
	node->x = x;
	node->y = y;
	node->tx = -5;
	node->ty = 0;
	node->state = sHorizon;
	node->time = 0;
	AddNode(node);

	node = (LNode *)malloc(sizeof(LNode));
	node->x = x;
	node->y = y;
	node->tx = 0;
	node->ty = 5;
	node->state = sVertical;
	node->time = 0;
	AddNode(node);

	node = (LNode *)malloc(sizeof(LNode));
	node->x = x;
	node->y = y;
	node->tx = 0;
	node->ty = -5;
	node->state = sVertical;
	node->time = 0;
	AddNode(node);

}