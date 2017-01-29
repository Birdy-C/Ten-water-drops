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
/*�������ܣ���ȡ����ˮ�εĿ��											*/
/************************************************************************/
int bubbleWidth()
{

	return theApp.imgDrops.mWidth/4;
}
/************************************************************************/

/*����ԭ�ͣ�int bubbleHeight() 											*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ȡ����ˮ�εĸ߶�											*/
/************************************************************************/
int bubbleHeight() 
{
	return theApp.imgDrops.mHeight / theApp.bubblerow;
}


/************************************************************************/

/*����ԭ�ͣ�int blankHeight() 											*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ȡ�����浽��Χ�ľ���											*/
/************************************************************************/
int blankHeight()
{

	return ( SCREEN_HEIGHT- COL*bubbleHeight())/2;
}

/************************************************************************/
/*����ԭ�ͣ�void drawDisc(int x,int y)						*/
/*���������x���꣬y����								*/
/*�� �� ֵ����															*/
/*�������ܣ�����bubbles[x][y]										*/
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
/*����ԭ�ͣ�INIT_bubble()								*/
/*���������wu										*/
/*�� �� ֵ����						   									*/
/*�������ܣ�����bubble����											*/
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
/*����ԭ�ͣ�PressBubble((Bubble*)pCtrl);								*/
/*���������bubbleָ��												*/
/*�� �� ֵ��ʱ����ָ��ֵ�򷵻�TRUE.���򷵻�FALSE 						*/
/*�������ܣ��жϿ�ʼ��ʱ��ʱ�����Ƿ񳬹�ָ��ֵ						
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