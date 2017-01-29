/******************************************************************
File name: Util.c
Date: 2016/6
Description:    通用工具类函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/*函数功能：设定包围圈								*/
void setRect() {

	int i;
	MakeRect(&theApp.bubbleRect, blankHeight(), blankHeight(), bubbleWidth()*ROW, bubbleHeight()*COL);
	for (i=0;i<=3;i++)
		MakeRect(&theApp.buttons[i].rect, ButtonX, SCREEN_HEIGHT -blankHeight()-(4-i)*btnHeight(), btnWidth(), btnHeight());

}

/************************************************************************/
/*函数原型：void * SetFocus(void * pCtrl)								*/
/*传入参数：空类型的指针												*/
/*返 回 值：无															*/
/*函数功能：设定焦点为pCtrl 											*/
/************************************************************************/
void * SetFocus(void * pCtrl)
{
	theApp.pFocus = pCtrl;
	return pCtrl;
}
/************************************************************************/
/*函数原型：void MakeRect(SDL_Rect *rect,int x,int y,int w,int h)		*/
/*传入参数：待修改的SDL_Rect，横坐标x,纵坐标y，宽度w，高度h				*/
/*返 回 值：无						   									*/
/*函数功能：设定入参SDL_Rect的坐标与宽高								*/
/************************************************************************/
void MakeRect(SDL_Rect* rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}
/************************************************************************/
/*函数原型：BOOL IsWinning()											*/
/*传入参数：无															*/
/*返 回 值：所有Bubble  为0？ 			*/
/*函数功能：判断游戏是否成功							 				*/
/************************************************************************/
BOOL IsWinning() {
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if(theApp.bubbles[i][j].slevel!=0)return FALSE;
		}
	}

	return TRUE;

	
}





/************************************************************************/
/*函数原型：void* GetControlAt(int x,int y)								*/
/*传入参数：横坐标x,纵坐标y												*/
/*返 回 值：坐标所在的部件						   						*/
/*函数功能：获取屏幕坐标所在的部件（按钮，圆盘或者空）					*/
/************************************************************************/
void* GetControlAt(int x, int y) {

	int i;
	void* pFocus = NULL;

	for (i = 0; i<4; i++)
	{
		if (HitRectTest(x, y, theApp.buttons[i].rect))
			return theApp.buttons + i;
	}

	if (HitRectTest(x, y, theApp.bubbleRect))
		return &theApp.bubbles[changeX(x)][changeX(y)];

	return pFocus;
}
/************************************************************************/
/*函数原型：BOOL HitRectTest(int x, int y, SDL_Rect rect)				*/
/*传入参数：待修改的SDL_Rect，横坐标x,纵坐标y，宽度w，高度h				*/
/*返 回 值：坐标位于矩形区域内返回TRUE，否则返回FALSE					*/
/*函数功能：判断坐标（x，y）是否位于矩形区域内							*/
/************************************************************************/
BOOL HitRectTest(int x, int y, SDL_Rect rect)
{
	return (x >= rect.x && y >= rect.y && x<rect.x + rect.w && y<rect.y + rect.h);
}
void setDigitWH() {
	int maxw = 0, maxh = 0, i;
	//获取0-9十个数字纹理中宽度与高度的最大值
	for (i = 1; i<10; i++)
	{
		if (theApp.numbersLT[i].mWidth>theApp.numbersLT[maxw].mWidth)
		{
			maxw = i;
		}
		if (theApp.numbersLT[i].mHeight>theApp.numbersLT[maxh].mHeight)
		{
			maxh = i;
		}
	}
	//设定数字纹理为最大值
	theApp.DigitW = theApp.numbersLT[maxw].mWidth;
	theApp.DigitH = theApp.numbersLT[maxh].mHeight;
}
