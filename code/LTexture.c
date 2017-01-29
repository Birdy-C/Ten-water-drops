/******************************************************************
File name: LTexture.c
Date: 2016/6
Description:	实现加载带颜色文本的LTexture,加载图片的LTexture
Author: XY,CLx
EMAIL：xgliu@cad.zju.edu.cn
*******************************************************************/
#include "water.h"


/************************************************************************/
/*函数原型：void renderTexture(LTexture ltexture,int x,int y)	 		*/
/*传入参数：LTexture ltexture,坐标x,坐标y								*/
/*返 回 值：无															*/
/*函数功能：在指定位置绘制纹理						 					*/
/************************************************************************/
void renderTexture(LTexture ltexture, int x, int y) {

	SDL_Rect srcRect = { 0,0,ltexture.mWidth,ltexture.mHeight }, destRect = { x,y,ltexture.mWidth,ltexture.mHeight };

	SDL_RenderCopy(theApp.gRenderer, ltexture.mTexture, &srcRect, &destRect);
}

/************************************************************************/
/*函数原型：LTexture load_image(char* path)								*/
/*传入参数：图片资源在硬盘上的相对路径									*/
/*返 回 值：LTexture													*/
/*函数功能：加载在硬盘上的图片资源，生成纹理			 				*/
/************************************************************************/
LTexture load_image(char* path) {
	
	LTexture ltexture;

	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s!SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		ltexture.mTexture = SDL_CreateTextureFromSurface(theApp.gRenderer, loadedSurface);

		if (ltexture.mTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else {
			ltexture.mWidth = loadedSurface->w;
			ltexture.mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	
	return ltexture;
}
/************************************************************************/
/*函数原型：LTexture load_TTF_text( char *text,TTF_Font* gFont)			*/
/*传入参数：待显示的字符ch,文本字体gFont								*/
/*返 回 值：LTexture													*/
/*函数功能：生成字符串纹理						 						*/
/************************************************************************/
LTexture load_TTF_text(char *text, TTF_Font* gFont) {

	SDL_Surface* textSurface;
	LTexture textTexture;
	SDL_Color color = { 0,92,175,255 };

	textSurface = TTF_RenderText_Solid(gFont, text, color);

	if (textSurface != NULL)
	{
		textTexture.mTexture = SDL_CreateTextureFromSurface(theApp.gRenderer, textSurface);
		if (textTexture.mTexture == NULL)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		else {
			textTexture.mWidth = textSurface->w;
			textTexture.mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	else
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

	return textTexture;
}

/************************************************************************/
/*函数原型：LTexture load_Number( int num)			 					*/
/*传入参数：待显示的数字												*/
/*返 回 值：LTexture													*/
/*函数功能：生成数字的纹理							 					*/
/************************************************************************/
LTexture load_Number(int num) {
	char numText[10];
	numText[0] = 48 + num;
	numText[1] = 0;
	return load_TTF_text(numText, theApp.gFont);
}
/************************************************************************/
/*函数原型：void freeLTexture(LTexture *ltexture)		 				*/
/*传入参数：待释放的LTexture											*/
/*返 回 值：无															*/
/*函数功能：释放LTexture资源						 					*/
/************************************************************************/
void freeLTexture(LTexture *ltexture) {

	if (ltexture->mTexture != NULL) {

		SDL_DestroyTexture(ltexture->mTexture);
		ltexture->mWidth = 0;
		ltexture->mHeight = 0;
		ltexture->mTexture = NULL;
	}
}