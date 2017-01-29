/******************************************************************
File name: Button.c
Date: 2016/6
Description:	水花相关函数
Author: XY,CLx
*******************************************************************/
#include "water.h"
/************************************************************************/
/*函数原型：int bubbleWidth()											*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取单个水花的宽度											*/
/************************************************************************/
int sprayWidth()
{	return theApp.imgSpray.mWidth;
}
/************************************************************************/

/*函数原型：int bubbleHeight() 											*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取单个水花的高度											*/
/************************************************************************/
int sprayHeight()
{

	return theApp.imgSpray.mHeight /6;//图中有6种情况
}


/************************************************************************/
/*函数原型：void mainSprayEvent()								        */
/*传入参数：无													 		*/
/*返 回 值：无										 					*/
/*函数功能：遍历水花进行事件处理										*/
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
/*函数原型：void sprayEvent(LNode* p) 									*/
/*传入参数：水花对应地址												*/
/*返 回 值：无						   									*/
/*函数功能：水花事件处理												*/
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
/*函数原型：int changeX(int i)								            */
/*传入参数：坐标值i												 		*/
/*返 回 值：坐标值i对应的格子序号						 				*/
/*函数功能：坐标值转为对应格子序号 										*/
/************************************************************************/
int changeX(int i) {
	return (i - blankHeight())/bubbleHeight();
}

/************************************************************************/
/*函数原型：isCrashingL(int x)								            */
/*传入参数：LNode* p											 		*/
/*返 回 值：TRUE/FALSE									 				*/
/*函数功能：判断水花是否碰到交界线										*/
/************************************************************************/
int isCrashingL(int x) {

	if ((x - blankHeight()) % bubbleHeight() == 0) 
		return TRUE;
	return FALSE;

}
/************************************************************************/
/*函数原型：void boom(int i, int j)									    */
/*传入参数：int i, int j										 		*/
/*返 回 值：无										 					*/
/*函数功能：处理[i][j]处水泡炸开事件 									*/
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