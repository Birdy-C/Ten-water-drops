#pragma once
/******************************************************************
Date: 2016/6
Author: XY,CLx
*******************************************************************/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>  
#include <SDL_thread.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 800	//界面宽 
#define SCREEN_HEIGHT 600 //界面高
#define ROW 6	//图的行数
#define COL 6	//图的列数 
#define ButtonX 600
#define ButtonY 200
typedef int BOOL;
#define FALSE 0  
#define TRUE  1   

typedef struct {
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
}LTexture;





typedef enum { // states for the mine field of the game
	sDisapear = 0, //消失
	sHorizon ,    // 横向
	sVertical,   // 竖向
	sCrash1,//右 撞墙
	sCrash2, //左
	sCrash3, //上
	sCrash4, // 下 
}sprayState;

typedef struct lnode {
	int x, y;//位置
	int tx, ty;//飞行方向
	int state;//sprayState
	int time;//记录时间（用于撞墙事件
	struct lnode * next;
}LNode;


/*** About drop ****/

typedef enum { 
	remain  = 0 ,// 
	active,       // 

} dropState;

typedef struct { // 
	int slevel;  // 状态1-8
	int state;//
	int time;
} Bubble;

/*** About button ****/
typedef enum {
	btnExposed = 0,
	btnDown
} BtnState;

typedef enum {
	btnPlay,
	btnMusic,
	btnHelp,
	btnQuit
} BtnIndex;

typedef struct {

	BtnState state;
	BtnIndex btnIndex;
	SDL_Rect rect;
}Button;
/***************************/
typedef enum { // user defined event 
	evtStartGame = 0,			// renew a game  
	evtLevelUp
} UserEvent;


typedef enum { // user defined event
	sNormal = 0,
	sActive,
	sGameFail,       // the game is lost
	sLevelUp  ,   // win the game
	
} GameState;

typedef struct {

	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;

	TTF_Font *gFont;

	SDL_Rect bubbleRect;
	SDL_Rect buttonRect;

	LTexture btnLT;
	LTexture bgLT;
	LTexture imgDrops;
	LTexture imgSpray;
	LTexture imgFail;
	LTexture imgLevelUp;
	LTexture imgHelp;
	LTexture levelLT;
	LTexture bubbleLT;	
	LTexture numbersLT[10];//0-9数字纹理 

	int DigitW;	//个位数纹理宽度，取0-9纹理中最大值
	int DigitH;	//个位数纹理宽度，取0-9纹理中最大值
	int gamestateH;
	void * pFocus;
	int bubblerow;//图中的数量
	int btnRow;
	int  keyx;
	int keyy;
	LTexture keyLT;
	int keytime;
	
	int level;
	int waterCount;
	int waterTemp;
	int gamestate;

	LNode *head;
	Bubble bubbles[ROW][COL];
    Button buttons[4];

	Mix_Chunk *audio_btnIn;
	Mix_Chunk *audio_btnDown;
	Mix_Chunk *audio_bgmusic;
    Mix_Chunk *audio_split;
	Mix_Chunk *audio_fail;
	Mix_Chunk *audio_win;
	Mix_Chunk *audio_crash;


	//BOOL AutoRun;

}MineApp;


extern MineApp theApp;


#endif