/******************************************************************
File name: Mouse.c
Date: 2016/6
Description:   ��������
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*����ԭ�ͣ�BOOL LoadMedia()											*/
/*�����������															*/
/*�� �� ֵ��ý����Դ�Ƿ�ȫ�����سɹ�   									*/
/*�������ܣ�������Ϸ���õ���ý����Դ					 				*/
/************************************************************************/
BOOL LoadMedia()
{
	if(! loadPictrure())return FALSE;
	if(!loadMusic())return FALSE;
	

	 //������������
	 int i;
	
	 theApp.gFont = TTF_OpenFont("media/Arial.ttf", 40);
	 if (theApp.gFont==NULL) {
		 printf("Font Wrong");
		 return FALSE;
	 }
	 for (i = 0; i<10; i++)
	 {
		 theApp.numbersLT[i] = load_Number(i);
	 }
	 setDigitWH();
	 //������Ϸ������ʾ����
	 theApp.gFont = TTF_OpenFont("media/Arial.ttf", 24);
	 theApp.levelLT = load_TTF_text("Level:", theApp.gFont);
	 theApp.bubbleLT = load_TTF_text("Drops:", theApp.gFont);
	 //

	return TRUE;
}
BOOL loadPictrure()
{
	//������Ϸ��������
	theApp.bgLT = load_image("media/pics/background.jpg");
if (!theApp.bgLT.mTexture)
{
	printf("Failed to load imgBackground");
	return FALSE;
}
//����ˮ������
theApp.imgDrops = load_image("media/pics/drops.png");
if (!theApp.imgDrops.mTexture)
{
	printf("Failed to load imgDrops");
	return FALSE;
}
//����ˮ������
theApp.keyLT = load_image("media/pics/keyLT.png");
if (!theApp.imgDrops.mTexture)
{
	printf("Failed to load keyLT");
	return FALSE;
}

theApp.imgSpray = load_image("media/pics/spray.png");
if (!theApp.imgDrops.mTexture)
{
	printf("Failed to load imgSpray");
	return FALSE;
}

//����ʧ������
theApp.imgFail = load_image("./media/pics/failbg.jpg");
if (!theApp.imgFail.mTexture)
{
	printf("Failed to load failbg");
	return FALSE;
}

theApp.imgLevelUp = load_image("./media/pics/levelupbg.jpg");
if(!theApp.imgFail.mTexture)
{
	printf("Failed to load levelupbg");
	return FALSE;
}
theApp.imgHelp = load_image("./media/pics/helpbg.jpg");
if (!theApp.imgHelp.mTexture)
{
	printf("Failed to load helpbg");
	return FALSE;
}
theApp.btnLT= load_image("./media/pics/button.png");
if (!theApp.imgHelp.mTexture)
	{
		printf("Failed to load button");
		return FALSE;
	}




/*
//���ؿ�ʼ������
theApp.StartBtn.ltexture = load_image("./media/pics/startPic.png");
if (!theApp.StartBtn.ltexture.mTexture)
{
printf("Failed to load StartBtn");
return FALSE;
}

//������ͣ������
theApp.StopBtn.ltexture = load_image("./media/pics/stopPic.png");
if (!theApp.StopBtn.ltexture.mTexture)
{
printf("Failed to load StopBtn");
return FALSE;
}

//�����˳�������
theApp.QuitBtn.ltexture = load_image("./media/pics/quitPic.png");
if (!theApp.QuitBtn.ltexture.mTexture)
{
printf("Failed to load QuitBtn");
return FALSE;
*/

return TRUE;



}
BOOL loadMusic() {
	
	theApp.audio_bgmusic = Mix_LoadMUS("./media/audio/bgmusic.mp3");
	if (theApp.audio_bgmusic == NULL)
	{
		printf("Failed to load bgmusic music! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//���������밴ťʱ����Ƶ
	theApp.audio_btnIn = Mix_LoadWAV("./media/audio/btnIn.wav");
	if (!theApp.audio_btnIn)
	{
		printf("Failed to load levelUp sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//������갴�°�ťʱ����Ƶ
	theApp.audio_btnDown = Mix_LoadWAV("./media/audio/btnDown.wav");
	if (!theApp.audio_btnDown)
	{
		printf("Failed to load btnDown sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//���ص÷�ʱ����Ƶ
	theApp.audio_win = Mix_LoadWAV("./media/audio/success.wav");
	if (!theApp.audio_win)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//����ʧ��ʱ����Ƶ
	theApp.audio_fail = Mix_LoadWAV("./media/audio/fail.wav");
	if (!theApp.audio_fail)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	
	theApp.audio_split = Mix_LoadWAV("./media/audio/split.wav");
	if (!theApp.audio_split)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}

	theApp.audio_crash= Mix_LoadWAV("./media/audio/bump.wav");
	if (!theApp.audio_split)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	
	return TRUE;


}