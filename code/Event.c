/******************************************************************
File name: Event.c
Date: 2016/6
Description: 事件处理类函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*函数原型：void onUserEvent( SDL_UserEvent *pEvent )					*/
/*传入参数：SDL_UserEvent												*/
/*返 回 值：无															*/
/*函数功能：处理自定义的用户事件										*/
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
/*函数原型：void startGame()											*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：程序开始前初始化部分数据									*/
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
	//播放背景音乐
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(theApp.audio_bgmusic, -1);
}
/************************************************************************/
/*函数原型：void startGame()											*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：过关判断													*/
/************************************************************************/
void levelup()
{
	theApp.gamestate = sNormal;
	theApp.level++;
	theApp.waterCount++;
	INIT_bubble();
}

/************************************************************************/
/*函数原型：void postUserEvent(int code)								*/
/*传入参数：事件代码 code												*/
/*返 回 值：无															*/
/*函数功能：向SDL事件队列中推送自定义事件								*/
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
/*函数原型：void routeEvent(SDL_Event* event)							*/
/*传入参数：SDL_Event													*/
/*返 回 值：无															*/
/*函数功能：核心函数，用于处理在游戏中的各种事件（如按下各种按键）		*/
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
	case SDL_MOUSEBUTTONDOWN:  //点击
		pNow = GetControlAt(mb->x, mb->y);
		if (!pNow) break;
		SetFocus(pNow);
		if (theApp.gamestate == sNormal)
		{
			if (mb->button == 1)
				onLButtonDown(pNow, mb->x, mb->y, mb->state);
		}
		break;
	case SDL_MOUSEBUTTONUP:   //释放
		pNow = GetControlAt(mb->x, mb->y);
		if (mb->button == 1)
			onLButtonUp(pNow, mb->x, mb->y, mb->state);
	break;
	case SDL_MOUSEMOTION:  //鼠标移动
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
/*函数原型：void RunApp()												*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：游戏主框架，接受玩家触发的事件 ，绘制界面  					*/
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


