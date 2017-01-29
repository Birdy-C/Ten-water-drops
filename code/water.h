#pragma once
/******************************************************************
Date: 2016/6
Author: XY,CLx
*******************************************************************/


#ifndef _WATER_H_
#define _WATER_H_ 
#include "constant.h"


//========================������Bubble.c��ʵ��=========================//
int bubbleWidth();
int bubbleHeight();
int blankHeight();
void drawBubble(int x, int y);
void INIT_bubble();
void PressBubble(Bubble* pbubble);
void dropEvent();
//========================������Button.c��ʵ��=========================//
int btnWidth();
int btnHeight();
void pressBtn(Button* pCtrl);
void releaseBtn(Button* pCtrl);
void buttonEvent();
//=========================������Draw.c��ʵ��==========================//
void DrawBackground();
void sDrawBubble();
void renderApp();
void sDrawSpray(LNode* p);
void drawLevel();
void drawCount();
void drawSpray();
void drawNum(int x, int y, int num);
//==========================������Event.c��ʵ��========================//
void RunApp();
void postUserEvent(int code);
void startGame();
void routeEvent(SDL_Event* event);
void onUserEvent(SDL_UserEvent *pEvent);
void levelup();
void keyEvent(SDL_Event* event);
//==========================������LNode.c��ʵ��========================//
void MakeNode();
void AddNode(LNode* pnode);
void deleteNode(LNode* pnode);
void clearHeaders();
//=========================������LTexture.c��ʵ��======================//
LTexture load_image(char* path);
void freeLTexture(LTexture *ltexture);
void renderTexture(LTexture ltexture, int x, int y);
LTexture load_TTF_text(char *text, TTF_Font* gFont);
LTexture load_Number(int num);

//==========================������Media.c��ʵ��========================//
BOOL LoadMedia();
BOOL loadPictrure();
BOOL loadMusic();
//==========================������Mouse.c��ʵ��========================//
void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags);
void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags);
void LoseMouse(void * pCtrl);
void MoveOnField(void*pCtrl);
void onMouseMove(void * pCtrl);
//==========================������Spray.c��ʵ��=========================//
int sprayWidth();
int sprayHeight();
void sprayEvent(LNode* p);
int changeX(int i);
int isCrashingL(int x);
void boom(int i, int j);
void mainSprayEvent();
//==========================������Util.c��ʵ��=========================//
void setRect();
void * SetFocus(void * pCtrl);
void MakeRect(SDL_Rect* rect, int x, int y, int w, int h);
BOOL IsWinning();
void* GetControlAt(int x, int y);
BOOL HitRectTest(int x, int y, SDL_Rect rect);
void setDigitWH();

#endif