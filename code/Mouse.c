/******************************************************************
File name: Mouse.c
Date: 2016/6
Description:   ��괦����
Author: XY,CLx
*******************************************************************/
#include "water.h"

/**************************************************************	*****************/
/*����ԭ�ͣ�void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags)	*/
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/
/*�� �� ֵ����  																*/
/*�������ܣ����������������¼�												*/
/********************************************************************************/
void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags)
{
	if (theApp.gamestate != sNormal)return;
	if (pCtrl <=(void*)(theApp.buttons+3)&& pCtrl >= (void*)theApp.buttons )
	{
		pressBtn( (Button *)pCtrl );
		
	}
	
		
}

/**************************************************************	*****************/
/*����ԭ�ͣ�void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags)	*/
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/
/*�� �� ֵ����  																*/
/*�������ܣ������������ͷ��¼�												*/
/********************************************************************************/
void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags)
{
	
	if (theApp.gamestate == sActive)
		return;
	if (theApp.gamestateH == 1) 
	{
		theApp.gamestateH = 0;
		theApp.buttons[2].state = btnExposed;
		return;
	}
	if (theApp.gamestate == sGameFail) 
	{
		startGame();
		return; 
	}
	if (theApp.gamestate == sLevelUp)
	{
		levelup(); 
		return;
	}

	if (pCtrl <= (void*)(theApp.buttons + 3) && pCtrl >= (void*)theApp.buttons)
		releaseBtn(pCtrl);

	else
	{
		PressBubble((Bubble*)pCtrl);
		
	}
	
}






/**************************************************************	*****************/
/*����ԭ�ͣ�void LoseMouse(void * pCtrl)										*/
/*������������㲿����ָ��														*/
/*�� �� ֵ����  																*/
/*�������ܣ���������Ƴ���ť��ˮ��											*/
/********************************************************************************/
void LoseMouse(void * pCtrl)
{
	if (pCtrl == NULL) return;
	if (pCtrl <= theApp.buttons + 3 && pCtrl >= theApp.buttons)
	{
		;

	}
	else
	{
		if (theApp.gamestate != sNormal) return;
		((Bubble*)pCtrl)->state = remain;
	}
	
}

void MoveOnField(void*pCtrl) 
{
	
	if (pCtrl==0)return;
	if (pCtrl <= (void*)(theApp.buttons + 3) && pCtrl >= (void*)theApp.buttons)
	{
		if(theApp.buttons[1].state == btnExposed)
			Mix_PlayChannel(-1, theApp.audio_btnIn, 0);
	}
	else
	{
		if (theApp.gamestate != sNormal) return;
		((Bubble*)pCtrl)->state = active;
		((Bubble*)pCtrl)->time = 1;
	}
}


/**************************************************************	*****************/
/*����ԭ�ͣ�void onMouseMove(void *pCtrl, int x, int y, unsigned char flags)	*/
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/
/*�� �� ֵ����  																*/
/*�������ܣ���������ƶ��¼�													*/
/********************************************************************************/
void onMouseMove(void * pCtrl)
{
	
	void * pOld = theApp.pFocus;
	if ( pOld != pCtrl)
	{
		LoseMouse(pOld);
		MoveOnField(pCtrl);
	}
	
	if (!pOld) return; // no control to handle
}


