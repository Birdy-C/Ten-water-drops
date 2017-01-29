/******************************************************************
File name: Button.c
Date: 2016/6
Description:	��ť��غ���
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*����ԭ�ͣ�int btnWidth()												*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ȡ������ť�Ŀ��											*/
/************************************************************************/
int btnWidth() {

	return theApp.btnLT.mWidth/2 ;
}

/************************************************************************/
/*����ԭ�ͣ�int btnHeight()												*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ȡ������ť�ĸ߶�											*/
/************************************************************************/
int btnHeight() {

	return theApp.btnLT.mHeight / theApp.btnRow;
}

/************************************************************************/
/*����ԭ�ͣ�void pressBtn(Button* pCtrl)								*/
/*��������������°�ť��ָ��											*/
/*�� �� ֵ����						   									*/
/*�������ܣ����°�ť������		switch(((Button *)pCtrl)->state)
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
/*����ԭ�ͣ�void releaseBtn(Button* pCtrl)								*/
/*����������ͷŰ�ť��ָ��												*/
/*�� �� ֵ����						   									*/
/*�������ܣ��ͷŰ�ť������											*/
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
/*����ԭ�ͣ�void buttonEvent()											*/
/*�����������															*/
/*�� �� ֵ����						   									*/
/*�������ܣ���ť�¼�����												*/
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