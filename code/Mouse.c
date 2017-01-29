/******************************************************************
File name: Mouse.c
Date: 2016/6
Description:   鼠标处理函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/**************************************************************	*****************/
/*函数原型：void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags)	*/
/*传入参数：焦点部件的指针，X坐标，Y坐标，备用参数flags							*/
/*返 回 值：无  																*/
/*函数功能：处理鼠标左键按下事件												*/
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
/*函数原型：void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags)	*/
/*传入参数：焦点部件的指针，X坐标，Y坐标，备用参数flags							*/
/*返 回 值：无  																*/
/*函数功能：处理鼠标左键释放事件												*/
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
/*函数原型：void LoseMouse(void * pCtrl)										*/
/*传入参数：焦点部件的指针														*/
/*返 回 值：无  																*/
/*函数功能：处理鼠标移出按钮或水滴											*/
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
/*函数原型：void onMouseMove(void *pCtrl, int x, int y, unsigned char flags)	*/
/*传入参数：焦点部件的指针，X坐标，Y坐标，备用参数flags							*/
/*返 回 值：无  																*/
/*函数功能：处理鼠标移动事件													*/
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


