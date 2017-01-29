/******************************************************************
File name: Event.c
Date: 2016/6
Description: �¼������ຯ��
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*����ԭ�ͣ�void onUserEvent( SDL_UserEvent *pEvent )					*/
/*���������SDL_UserEvent												*/
/*�� �� ֵ����															*/
/*�������ܣ������Զ�����û��¼�										*/
/************************************************************************/
void onUserEvent(SDL_UserEvent *pEvent) {

	switch (pEvent->code) {
	case evtStartGame:
		startGame();
		break;
	case evtLevelUp:
		levelup();
		break;
	
	}
}

/************************************************************************/
/*����ԭ�ͣ�void startGame()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ�����ʼǰ��ʼ����������									*/
/************************************************************************/
void startGame() 
{
	int i;
	clearHeaders();
	MakeNode();
	
	theApp.bubblerow = 4;
	theApp.level = 1;
	theApp.btnRow = 4;
	theApp.waterCount=10;

	INIT_bubble();
	setRect();
	setDigitWH();

	theApp.gamestate = sNormal;
	theApp.gamestateH = 0;
	theApp.keyx = 0;
	theApp.keyy = 0;
	theApp.keytime = 0;

	for(i=0;i<=3;i++)
	{
		theApp.buttons[i].btnIndex = i;
	}
	//���ű�������
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(theApp.audio_bgmusic, -1);
}
/************************************************************************/
/*����ԭ�ͣ�void startGame()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ������ж�													*/
/************************************************************************/
void levelup()
{
	theApp.gamestate = sNormal;
	theApp.level++;
	theApp.waterCount++;
	INIT_bubble();
}

/************************************************************************/
/*����ԭ�ͣ�void postUserEvent(int code)								*/
/*����������¼����� code												*/
/*�� �� ֵ����															*/
/*�������ܣ���SDL�¼������������Զ����¼�								*/
/************************************************************************/
void postUserEvent(int code)
{
	SDL_UserEvent ev;
	ev.type = SDL_USEREVENT;
	ev.code = code;
	ev.data1 = NULL;
	ev.data2 = NULL;

	SDL_PushEvent((SDL_Event*)&ev);
}

void keyEvent(SDL_Event* event) {
	
	
	if (event->key.keysym.sym == SDLK_SPACE)
	{
		onLButtonUp(&theApp.bubbles[theApp.keyx][theApp.keyy],0,0,0);
		theApp.keytime = 1;
		return;
	}
	if (event->key.keysym.sym == SDLK_LEFT) 
	{
		if (theApp.keyx > 0)theApp.keyx--;
	}
	if (event->key.keysym.sym == SDLK_RIGHT)
	{
		if (theApp.keyx<5)theApp.keyx++;
	}

if (event->key.keysym.sym == SDLK_UP)
{
	if (theApp.keyy > 0)theApp.keyy--;
}
if (event->key.keysym.sym == SDLK_DOWN)
{
	if (theApp.keyy<5)theApp.keyy++;
}
theApp.keytime = 1;
onMouseMove(&theApp.bubbles[theApp.keyx][theApp.keyy]);
}
/************************************************************************/
/*����ԭ�ͣ�void routeEvent(SDL_Event* event)							*/
/*���������SDL_Event													*/
/*�� �� ֵ����															*/
/*�������ܣ����ĺ��������ڴ�������Ϸ�еĸ����¼����簴�¸��ְ�����		*/
/************************************************************************/
void routeEvent(SDL_Event* event)
{
	void *pNow=NULL;
	SDL_QuitEvent ev;
	SDL_MouseButtonEvent* mb = (SDL_MouseButtonEvent*)event;
	SDL_MouseMotionEvent* mm = (SDL_MouseMotionEvent*)event;

	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_ESCAPE)
		{
			ev.type = SDL_QUIT;
			SDL_PushEvent((SDL_Event*)&ev);
			return;
		}
		keyEvent(event);
		
		break;
	case SDL_MOUSEBUTTONDOWN:  //���
		pNow = GetControlAt(mb->x, mb->y);
		if (!pNow) break;
		SetFocus(pNow);
		if (theApp.gamestate == sNormal)
		{
			if (mb->button == 1)
				onLButtonDown(pNow, mb->x, mb->y, mb->state);
		}
		break;
	case SDL_MOUSEBUTTONUP:   //�ͷ�
		pNow = GetControlAt(mb->x, mb->y);
		if (mb->button == 1)
			onLButtonUp(pNow, mb->x, mb->y, mb->state);
	break;
	case SDL_MOUSEMOTION:  //����ƶ�
		pNow = GetControlAt(mm->x, mm->y);
		if (theApp.gamestate == sNormal)
		{
			onMouseMove(pNow);
		}
		break;

	default:
		if (event->type >= SDL_USEREVENT && event->type < SDL_LASTEVENT)
			onUserEvent((SDL_UserEvent*)event);
		break;

	}
	SetFocus(pNow);
}



/************************************************************************/
/*����ԭ�ͣ�void RunApp()												*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ���Ϸ����ܣ�������Ҵ������¼� �����ƽ���  					*/
/************************************************************************/
void RunApp()
{
	BOOL quit = 0;
	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = TRUE;
			default:
				routeEvent(&event);
				break;
			}
		}
		
		dropEvent();
		buttonEvent();
		
		renderApp();
		SDL_Delay(20);
	}
}


