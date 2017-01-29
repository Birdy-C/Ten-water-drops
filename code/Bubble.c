/******************************************************************
File name: Button.c
Date: 2016/6
Description:	水滴相关函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*函数原型：int bubbleWidth()											*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取单个水滴的宽度											*/
/************************************************************************/
int bubbleWidth()
{

	return theApp.imgDrops.mWidth/4;
}
/************************************************************************/

/*函数原型：int bubbleHeight() 											*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取单个水滴的高度											*/
/************************************************************************/
int bubbleHeight() 
{
	return theApp.imgDrops.mHeight / theApp.bubblerow;
}


/************************************************************************/

/*函数原型：int blankHeight() 											*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取主界面到周围的距离											*/
/************************************************************************/
int blankHeight()
{

	return ( SCREEN_HEIGHT- COL*bubbleHeight())/2;
}

/************************************************************************/
/*函数原型：void drawDisc(int x,int y)						*/
/*传入参数：x坐标，y坐标								*/
/*返 回 值：无															*/
/*函数功能：绘制bubbles[x][y]										*/
/************************************************************************/
void drawBubble(int x, int y) {

	int sx, sy,t;
	SDL_Rect srcRect, destRect;
	sx = x * bubbleWidth() + blankHeight();
	sy = y * bubbleHeight() + blankHeight();
	t = theApp.bubbles[x][y].time/5%4;
	if (theApp.bubbles[x][y].slevel < 5 && theApp.bubbles[x][y].slevel >0) {
		MakeRect(&srcRect, t*bubbleWidth(), bubbleHeight()*(theApp.bubbles[x][y].slevel-1), bubbleWidth(), bubbleHeight());
		MakeRect(&destRect, sx, sy, bubbleWidth(), bubbleHeight());

		SDL_RenderCopy(theApp.gRenderer, theApp.imgDrops.mTexture, &srcRect, &destRect);
	}
}


/************************************************************************/
/*函数原型：INIT_bubble()								*/
/*传入参数：wu										*/
/*返 回 值：无						   									*/
/*函数功能：定义bubble数组											*/
/*********************************************************************/

void INIT_bubble() {
	int i, j , k;
	k = 0;

	srand(time(NULL));
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			theApp.bubbles[i][j].slevel =rand()%5;
			theApp.bubbles[i][j].state = remain;
		}
	}
}

/************************************************************************/
/*函数原型：PressBubble((Bubble*)pCtrl);								*/
/*传入参数：bubble指针												*/
/*返 回 值：时长超指定值则返回TRUE.否则返回FALSE 						*/
/*函数功能：判断开始计时后时间间隔是否超过指定值						
/************************************************************************/
void PressBubble( Bubble* pbubble) {
	if (pbubble == NULL)return;
	pbubble->slevel++;
	theApp.waterCount--;
	
	if (pbubble->slevel == 5)
	{
		theApp.gamestate = sActive;
		theApp.waterTemp = 0;
	}
}

void dropEvent() {
	int i, j;
	
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if (theApp.bubbles[i][j].slevel >= 5) {
				if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_split, 0);

				boom(i, j);
				theApp.bubbles[i][j].slevel = 0;
				theApp.gamestate = sActive;
				theApp.waterTemp++;
				if (theApp.waterTemp == 3) {
					theApp.waterTemp = 0;
					theApp.waterCount++;
				}
			}
			if (theApp.bubbles[i][j].time)
			{
				if (theApp.bubbles[i][j].time <= 34&& theApp.bubbles[i][j].time>0)
					theApp.bubbles[i][j].time++;
				if (theApp.bubbles[i][j].time == 35 && theApp.pFocus != & theApp.bubbles[i][j])
				{
					theApp.bubbles[i][j].state = remain;
					theApp.bubbles[i][j].time = 0;
				}
						
			}
		}

	}

}