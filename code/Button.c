/******************************************************************
File name: Button.c
Date: 2016/6
Description:	按钮相关函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*函数原型：int btnWidth()												*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取单个按钮的宽度											*/
/************************************************************************/
int btnWidth() {

	return theApp.btnLT.mWidth/2 ;
}

/************************************************************************/
/*函数原型：int btnHeight()												*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：获取单个按钮的高度											*/
/************************************************************************/
int btnHeight() {

	return theApp.btnLT.mHeight / theApp.btnRow;
}

/************************************************************************/
/*函数原型：void pressBtn(Button* pCtrl)								*/
/*传入参数：被按下按钮的指针											*/
/*返 回 值：无						   									*/
/*函数功能：按下按钮处理函数		switch(((Button *)pCtrl)->state)
		{
		case 	btnPlay:
			postUserEvent(evtStartGame);
			Mix_PlayChannel(-1, theApp.audio_start, 0);
			((Button *)pCtrl)->state = btnExposed;
			break;
		case 	btnHelp:
		case 	btnMusic:
		case 	btnQuit:
			event.type = SDL_QUIT;
			SDL_PollEvent(&event);}									*/
/************************************************************************/
void pressBtn(Button* pCtrl)
{
	if (theApp.buttons[1].state == btnExposed)
		Mix_PlayChannel(-1, theApp.audio_btnIn, 0);
	switch (pCtrl->btnIndex)
	{
	case btnPlay:
	
		pCtrl->state = btnDown;
		break;
	case btnMusic:
		if (pCtrl->state = btnExposed)
				pCtrl->state = btnDown;
		break;

	case btnHelp:
		pCtrl->state = btnDown;
		break;
	case btnQuit:
		pCtrl->state = btnDown;
		break;
	}
}


/************************************************************************/
/*函数原型：void releaseBtn(Button* pCtrl)								*/
/*传入参数：释放按钮的指针												*/
/*返 回 值：无						   									*/
/*函数功能：释放按钮处理函数											*/
/************************************************************************/
void releaseBtn(Button* pCtrl) {


	SDL_UserEvent ev;

	switch (pCtrl->btnIndex)
	{
	case btnPlay:
		startGame();
		pCtrl->state = btnExposed;
		break;
	case btnMusic:
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
			pCtrl->state = btnExposed;
		}
		else
		{
			Mix_PauseMusic();
			pCtrl->state = btnDown;
		}
		break;

	case btnHelp:
		if (theApp.gamestateH == 1) {
			pCtrl->state = btnExposed;

			theApp.gamestateH = 0;
		}
		else {
			
				theApp.gamestateH = 1;
		}
		break;
	case btnQuit:
		pCtrl->state = btnExposed;
		ev.type = SDL_QUIT;
		SDL_PushEvent((SDL_Event*)&ev);
		break;
	}
}
/************************************************************************/
/*函数原型：void buttonEvent()											*/
/*传入参数：无															*/
/*返 回 值：无						   									*/
/*函数功能：按钮事件处理												*/
/************************************************************************/

void buttonEvent()
{
	if (theApp.gamestate == sActive)
		mainSprayEvent();
	if (theApp.gamestate == sNormal)
	{
		if (IsWinning()) //pass this level
		{
			theApp.gamestate = sLevelUp;
			if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_win, 0);
		}
		if (theApp.waterCount == 0)//lost the game
		{
			theApp.gamestate = sGameFail;
			if (theApp.buttons[1].state == btnExposed)
				Mix_PlayChannel(-1, theApp.audio_fail, 0);
		}
	}
}