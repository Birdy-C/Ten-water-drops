/******************************************************************
File name: Draw.c
Date: 2016/6
Description:     �����ຯ����������Ϸ�и�������
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*����ԭ�ͣ�void sdrawDisc(int x,int y,int index)						*/
/*���������x���꣬y���꣬Բ�̱�־index									*/
/*�� �� ֵ����															*/
/*�������ܣ�����bubbles							*/
/************************************************************************/
void sDrawBubble() {

	int i, j;
	int sx, sy, t;
	SDL_Rect srcRect, destRect;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if (theApp.keytime > 0 && theApp.keytime < 3000) 
			{
				theApp.keytime++;
				sx = theApp.keyx * bubbleWidth() + blankHeight();
				sy = theApp.keyy * bubbleHeight() + blankHeight();
				MakeRect(&srcRect,0, 0, bubbleWidth(), bubbleHeight());
				MakeRect(&destRect, sx, sy, bubbleWidth(), bubbleHeight());
				SDL_RenderCopy(theApp.gRenderer, theApp.keyLT.mTexture, &srcRect, &destRect);
				
			}
			drawBubble(i,j);
		}
	
	}
}
/************************************************************************/
/*����ԭ�ͣ�void drawDisc(int x,int y)						*/
/*���������x���꣬y����								*/
/*�� �� ֵ����															*/
/*�������ܣ���(x,y)Ϊ���Ļ���spray										*/
/************************************************************************/
void sDrawSpray(LNode* p) {

	int sx, sy;
	SDL_Rect srcRect, destRect;
	sx = p->x - sprayWidth() / 2;
	sy = p->y - sprayHeight() / 2;

	MakeRect(&srcRect, 0, sprayHeight()*(p->state-1), sprayWidth(), sprayHeight());
	MakeRect(&destRect, sx, sy, sprayWidth(), sprayHeight());

	SDL_RenderCopy(theApp.gRenderer, theApp.imgSpray.mTexture, &srcRect, &destRect);
}
void drawSpray() {
	LNode*node;
	node = theApp.head->next;
	
	while (node) {
		sDrawSpray(node);
		node = node->next;
	}


}
void drawNum(int x, int y, int num) {

	int i = 0, len = 0, width = 0;
	int numbers[3] = { 0 };

	for (i = 0; i<3; i++)
	{
		numbers[i] = -1;
	}
	//��num�ĸ�λ���ִ���numbers���飬������num���������ܳ���
	if (num == 0)
	{
		numbers[0] = 0;
		width = theApp.DigitW;
	}

	i = 0;
	while (num>0)
	{
		numbers[i] = num % 10;
		width += theApp.DigitW;//ÿλ���ִ�Сһ�£����⵹��ʱ�Ķ�������
		num /= 10;
		i++;
	}
	//��λ��������
	for (i = 2; i >= 0; i--)
	{
		if (numbers[i] >= 0)
		{
			renderTexture(theApp.numbersLT[numbers[i]], x - width / 2 + len, y - theApp.DigitH / 2);
			len += theApp.DigitW;
		}
	}
}
/************************************************************************/
/*����ԭ�ͣ�void drawLevel()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�������Ϸ�Ѷȵȼ�											*/
/************************************************************************/
void drawLevel() {

	renderTexture(theApp.levelLT, 600, 10 );
	drawNum(700, 50, theApp.level );
	
}
void drawCount() {
	renderTexture(theApp.bubbleLT, 600,110);
	drawNum(700,150, theApp.waterCount);
	}
/************************************************************************/
/*����ԭ�ͣ�void DrawButtons()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�������Ϸ��ť								 				*/
/************************************************************************/
void DrawButtons() {

	int i, x, y;
	SDL_Rect srcRect;

	for (i = 0; i<4; i++)
	{
	
		x = theApp.buttons[i].state * btnWidth();
		y = theApp.buttons[i].btnIndex * btnHeight();
		MakeRect(&srcRect, x, y, btnWidth(), btnHeight());

		SDL_RenderCopy(theApp.gRenderer, theApp.btnLT.mTexture, &srcRect, &theApp.buttons[i].rect);

	}

}




/************************************************************************/
/*����ԭ�ͣ�void DrawBackground()										*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�������Ϸ���������ˮ��							 				*/
/************************************************************************/
void DrawBackground() {

	renderTexture(theApp.bgLT, 0, 0);
	if (theApp.gamestate == sActive)
		drawSpray();
}


/************************************************************************/
/*����ԭ�ͣ�void renderApp()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�������Ϸ���в���											*/
/************************************************************************/
void renderApp() {
	SDL_RenderClear(theApp.gRenderer);
	DrawBackground();
	sDrawBubble();
	DrawButtons();
	drawLevel();
	drawCount();
	if (theApp.gamestate == sGameFail)
		renderTexture(theApp.imgFail, 0, 0);
	if (theApp.gamestate == sLevelUp)
		renderTexture(theApp.imgLevelUp, 0, 0);
	if (theApp.gamestateH == 1)
		renderTexture(theApp.imgHelp, 0, 0);
	SDL_RenderPresent(theApp.gRenderer);
}