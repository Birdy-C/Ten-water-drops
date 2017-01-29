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

#define SCREEN_WIDTH 800	//����� 
#define SCREEN_HEIGHT 600 //�����
#define ROW 6	//ͼ������
#define COL 6	//ͼ������ 
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
	sDisapear = 0, //��ʧ
	sHorizon ,    // ����
	sVertical,   // ����
	sCrash1,//�� ײǽ
	sCrash2, //��
	sCrash3, //��
	sCrash4, // �� 
}sprayState;

typedef struct lnode {
	int x, y;//λ��
	int tx, ty;//���з���
	int state;//sprayState
	int time;//��¼ʱ�䣨����ײǽ�¼�
	struct lnode * next;
}LNode;


/*** About drop ****/

typedef enum { 
	remain  = 0 ,// 
	active,       // 

} dropState;

typedef struct { // 
	int slevel;  // ״̬1-8
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
	LTexture numbersLT[10];//0-9�������� 

	int DigitW;	//��λ�������ȣ�ȡ0-9���������ֵ
	int DigitH;	//��λ�������ȣ�ȡ0-9���������ֵ
	int gamestateH;
	void * pFocus;
	int bubblerow;//ͼ�е�����
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