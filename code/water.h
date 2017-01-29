#pragma once
/******************************************************************
Date: 2016/6
Author: XY,CLx
*******************************************************************/


#ifndef _WATER_H_
#define _WATER_H_ 
#include "constant.h"


//========================以下在Bubble.c中实现=========================//
int bubbleWidth();
int bubbleHeight();
int blankHeight();
void drawBubble(int x, int y);
void INIT_bubble();
void PressBubble(Bubble* pbubble);
void dropEvent();
//========================以下在Button.c中实现=========================//
int btnWidth();
int btnHeight();
void pressBtn(Button* pCtrl);
void releaseBtn(Button* pCtrl);
void buttonEvent();
//=========================以下在Draw.c中实现==========================//
void DrawBackground();
void sDrawBubble();
void renderApp();
void sDrawSpray(LNode* p);
void drawLevel();
void drawCount();
void drawSpray();
void drawNum(int x, int y, int num);
//==========================以下在Event.c中实现========================//
void RunApp();
void postUserEvent(int code);
void startGame();
void routeEvent(SDL_Event* event);
void onUserEvent(SDL_UserEvent *pEvent);
void levelup();
void keyEvent(SDL_Event* event);
//==========================以下在LNode.c中实现========================//
void MakeNode();
void AddNode(LNode* pnode);
void deleteNode(LNode* pnode);
void clearHeaders();
//=========================以下在LTexture.c中实现======================//
LTexture load_image(char* path);
void freeLTexture(LTexture *ltexture);
void renderTexture(LTexture ltexture, int x, int y);
LTexture load_TTF_text(char *text, TTF_Font* gFont);
LTexture load_Number(int num);

//==========================以下在Media.c中实现========================//
BOOL LoadMedia();
BOOL loadPictrure();
BOOL loadMusic();
//==========================以下在Mouse.c中实现========================//
void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags);
void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags);
void LoseMouse(void * pCtrl);
void MoveOnField(void*pCtrl);
void onMouseMove(void * pCtrl);
//==========================以下在Spray.c中实现=========================//
int sprayWidth();
int sprayHeight();
void sprayEvent(LNode* p);
int changeX(int i);
int isCrashingL(int x);
void boom(int i, int j);
void mainSprayEvent();
//==========================以下在Util.c中实现=========================//
void setRect();
void * SetFocus(void * pCtrl);
void MakeRect(SDL_Rect* rect, int x, int y, int w, int h);
BOOL IsWinning();
void* GetControlAt(int x, int y);
BOOL HitRectTest(int x, int y, SDL_Rect rect);
void setDigitWH();

#endif