/******************************************************************
File name: Mouse.c
Date: 2016/6
Description:   声音函数
Author: XY,CLx
*******************************************************************/
#include "water.h"

/************************************************************************/
/*函数原型：BOOL LoadMedia()											*/
/*传入参数：无															*/
/*返 回 值：媒体资源是否全部加载成功   									*/
/*函数功能：加载游戏中用到的媒体资源					 				*/
/************************************************************************/
BOOL LoadMedia()
{
	if(! loadPictrure())return FALSE;
	if(!loadMusic())return FALSE;
	

	 //加载数字纹理
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
	 //加载游戏结束提示标语
	 theApp.gFont = TTF_OpenFont("media/Arial.ttf", 24);
	 theApp.levelLT = load_TTF_text("Level:", theApp.gFont);
	 theApp.bubbleLT = load_TTF_text("Drops:", theApp.gFont);
	 //

	return TRUE;
}
BOOL loadPictrure()
{
	//加载游戏背景纹理
	theApp.bgLT = load_image("media/pics/background.jpg");
if (!theApp.bgLT.mTexture)
{
	printf("Failed to load imgBackground");
	return FALSE;
}
//加载水滴纹理
theApp.imgDrops = load_image("media/pics/drops.png");
if (!theApp.imgDrops.mTexture)
{
	printf("Failed to load imgDrops");
	return FALSE;
}
//加载水滴纹理
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

//加载失败纹理
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
//加载开始键纹理
theApp.StartBtn.ltexture = load_image("./media/pics/startPic.png");
if (!theApp.StartBtn.ltexture.mTexture)
{
printf("Failed to load StartBtn");
return FALSE;
}

//加载暂停键纹理
theApp.StopBtn.ltexture = load_image("./media/pics/stopPic.png");
if (!theApp.StopBtn.ltexture.mTexture)
{
printf("Failed to load StopBtn");
return FALSE;
}

//加载退出键纹理
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
	//加载鼠标进入按钮时的音频
	theApp.audio_btnIn = Mix_LoadWAV("./media/audio/btnIn.wav");
	if (!theApp.audio_btnIn)
	{
		printf("Failed to load levelUp sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//加载鼠标按下按钮时的音频
	theApp.audio_btnDown = Mix_LoadWAV("./media/audio/btnDown.wav");
	if (!theApp.audio_btnDown)
	{
		printf("Failed to load btnDown sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//加载得分时的音频
	theApp.audio_win = Mix_LoadWAV("./media/audio/success.wav");
	if (!theApp.audio_win)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//加载失败时的音频
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