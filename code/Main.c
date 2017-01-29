/******************************************************************
Date: 2016/6
Author: XY,CLx
*******************************************************************/
#include "water.h"
MineApp theApp;
/************************************************************************/
/*函数原型：void InitApp(int argc,char* args[])							*/
/*传入参数：计算提供到程序的参数										*/
/*返 回 值：初始化是否成功												*/
/*函数功能：初始化程序数据，加载媒体资源								*/
/************************************************************************/
BOOL InitApp(int argc, char* args[]) {

	//初始化SDL 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
	{
		printf("SDL could not initialize! SDL error:%s\n", SDL_GetError());
		return FALSE;
	}
	//创建游戏窗口
	theApp.gWindow = SDL_CreateWindow("Ten Water Drops", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (theApp.gWindow == NULL)
	{
		printf("Fail to create SDL window! SDL error:%s\n", SDL_GetError());
		return FALSE;
	}
	//创建游戏窗口的渲染器
	theApp.gRenderer = SDL_CreateRenderer(theApp.gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (theApp.gRenderer == NULL)
	{
		printf("Failed to create renderer!SDL Error:%s\n", SDL_GetError());
		return FALSE;
	}
	//采用PNG和JPG图片加载模式 
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return FALSE;
	}
	//初始化SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return FALSE;
	}
	//初始化SDL_mixer 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return FALSE;
	}
	//加载媒体资源
	if (!LoadMedia())
	{
		printf("Failed in loading media!\n");
		return FALSE;
	}
postUserEvent(evtStartGame);
	return TRUE;
}

/************************************************************************/
/*函数原型：void CleanApp()												*/
/*传入参数：无															*/
/*返 回 值：无															*/
/*函数功能：释放程序资源					 							*/
/************************************************************************/
void CleanApp()
{
	
	int i;
	freeLTexture(&theApp.btnLT);//clear texture
	freeLTexture(&theApp.bgLT);
	freeLTexture(&theApp.imgDrops);
	freeLTexture(&theApp.imgSpray);
	freeLTexture(&theApp.imgFail);
	freeLTexture(&theApp.imgLevelUp);
	freeLTexture(&theApp.imgHelp);
	freeLTexture(&theApp.keyLT);
	freeLTexture(&theApp.levelLT);
	freeLTexture(&theApp.bubbleLT);

	for (i = 0; i<10; i++)
	{
		freeLTexture(&theApp.numbersLT[i]);
	}

	
	clearHeaders();	//clear node

	
	Mix_FreeChunk(theApp.audio_btnIn);//clear music
	Mix_FreeChunk(theApp.audio_btnDown);
	Mix_FreeChunk(theApp.audio_bgmusic);
	Mix_FreeChunk(theApp.audio_split);
	Mix_FreeChunk(theApp.audio_fail);
	Mix_FreeChunk(theApp.audio_win);
	Mix_FreeChunk(theApp.audio_crash);
	theApp.audio_btnIn=NULL;//clear music
	theApp.audio_btnDown = NULL;
	theApp.audio_bgmusic = NULL;
	theApp.audio_split= NULL;
	theApp.audio_fail = NULL;
	theApp.audio_win= NULL;
	theApp.audio_crash=NULL;

	
	TTF_CloseFont(theApp.gFont);//clear font
	SDL_DestroyWindow(theApp.gWindow);
	SDL_DestroyRenderer(theApp.gRenderer);	

	theApp.gFont = NULL;
	theApp.gWindow = NULL;
	theApp.gRenderer = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/************************************************************************/
/*函数原型：int main(int argc,char* args[]) 							*/
/*传入参数：计算机传给程序的参数										*/
/*返 回 值：是否正常退出												*/
/*函数功能：入口函数,包含十滴水主流程									*/
/************************************************************************/
int main(int argc, char* args[])
{
	if (!InitApp(argc, args))
		return 0;
	RunApp();
	CleanApp();
	return 0;
}