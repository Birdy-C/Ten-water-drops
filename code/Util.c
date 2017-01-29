/******************************************************************
File name: Util.c
Date: 2016/6
Description:    ͨ�ù����ຯ��
Author: XY,CLx
*******************************************************************/
#include "water.h"

/*�������ܣ��趨��ΧȦ								*/
void setRect() {

	int i;
	MakeRect(&theApp.bubbleRect, blankHeight(), blankHeight(), bubbleWidth()*ROW, bubbleHeight()*COL);
	for (i=0;i<=3;i++)
		MakeRect(&theApp.buttons[i].rect, ButtonX, SCREEN_HEIGHT -blankHeight()-(4-i)*btnHeight(), btnWidth(), btnHeight());

}

/************************************************************************/
/*����ԭ�ͣ�void * SetFocus(void * pCtrl)								*/
/*��������������͵�ָ��												*/
/*�� �� ֵ����															*/
/*�������ܣ��趨����ΪpCtrl 											*/
/************************************************************************/
void * SetFocus(void * pCtrl)
{
	theApp.pFocus = pCtrl;
	return pCtrl;
}
/************************************************************************/
/*����ԭ�ͣ�void MakeRect(SDL_Rect *rect,int x,int y,int w,int h)		*/
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/
/*�� �� ֵ����						   									*/
/*�������ܣ��趨���SDL_Rect����������								*/
/************************************************************************/
void MakeRect(SDL_Rect* rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}
/************************************************************************/
/*����ԭ�ͣ�BOOL IsWinning()											*/
/*�����������															*/
/*�� �� ֵ������Bubble  Ϊ0�� 			*/
/*�������ܣ��ж���Ϸ�Ƿ�ɹ�							 				*/
/************************************************************************/
BOOL IsWinning() {
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if(theApp.bubbles[i][j].slevel!=0)return FALSE;
		}
	}

	return TRUE;

	
}





/************************************************************************/
/*����ԭ�ͣ�void* GetControlAt(int x,int y)								*/
/*���������������x,������y												*/
/*�� �� ֵ���������ڵĲ���						   						*/
/*�������ܣ���ȡ��Ļ�������ڵĲ�������ť��Բ�̻��߿գ�					*/
/************************************************************************/
void* GetControlAt(int x, int y) {

	int i;
	void* pFocus = NULL;

	for (i = 0; i<4; i++)
	{
		if (HitRectTest(x, y, theApp.buttons[i].rect))
			return theApp.buttons + i;
	}

	if (HitRectTest(x, y, theApp.bubbleRect))
		return &theApp.bubbles[changeX(x)][changeX(y)];

	return pFocus;
}
/************************************************************************/
/*����ԭ�ͣ�BOOL HitRectTest(int x, int y, SDL_Rect rect)				*/
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/
/*�� �� ֵ������λ�ھ��������ڷ���TRUE�����򷵻�FALSE					*/
/*�������ܣ��ж����꣨x��y���Ƿ�λ�ھ���������							*/
/************************************************************************/
BOOL HitRectTest(int x, int y, SDL_Rect rect)
{
	return (x >= rect.x && y >= rect.y && x<rect.x + rect.w && y<rect.y + rect.h);
}
void setDigitWH() {
	int maxw = 0, maxh = 0, i;
	//��ȡ0-9ʮ�����������п����߶ȵ����ֵ
	for (i = 1; i<10; i++)
	{
		if (theApp.numbersLT[i].mWidth>theApp.numbersLT[maxw].mWidth)
		{
			maxw = i;
		}
		if (theApp.numbersLT[i].mHeight>theApp.numbersLT[maxh].mHeight)
		{
			maxh = i;
		}
	}
	//�趨��������Ϊ���ֵ
	theApp.DigitW = theApp.numbersLT[maxw].mWidth;
	theApp.DigitH = theApp.numbersLT[maxh].mHeight;
}
