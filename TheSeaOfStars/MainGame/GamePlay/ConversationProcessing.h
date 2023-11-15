#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <locale>
#include "MainProperties.h"
#include "PeripheralsDataProcessing.h"

using namespace std;


void ConversationProcessing(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer, const char* SourceText, Map MapRenderData)
{
	ObjectStructure ConversationBoard = {};
	ConversationBoard.Load_IMG("TheSeaOfStars/Design Documentation/Design Idea/ConversationBoard.png", MainGameRenderer);
	ConversationBoard.Initialized_IMG();
	ConversationBoard.RenderPicture(MainGameRenderer, 90, 420, 1);
	SDL_Event Event = {};

	TTF_Init();
	SDL_Surface* TextSurface = NULL;
	SDL_Texture* TextTexture = NULL;
	SDL_Rect TextRect = {}, InputBoxRect = {};
	TTF_Font* TextFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 28);
	SDL_Color TextColor = { 255, 255, 255 };
	TextRect.w = 10;
	TextRect.h = 20;
	TextRect.x = 121;
	TextRect.y = 452;
	int MousePosX = 0, MousePosY = 0;
	FILE* openSourceText;

	if (fopen_s(&openSourceText, SourceText, "r") != 0)
	{
		cout << "Error : Cann't Open The Text Trailer File! Error Link :" << SourceText;
	}
	else
	{
		char c = NULL;
		while (c != EOF)
		{
			c = fgetc(openSourceText);
			string TextReaded;
			TextReaded += c;
			if (TextReaded == "\n")
			{
				TextRect.x = 121;
				TextRect.y += 20;
				continue;
			}
			else
				TextRect.x += 11;
			TextSurface = TTF_RenderText_Solid(TextFont, TextReaded.c_str(), TextColor);
			if (TextSurface == NULL)
				printf("TextSurface run wrong! Please test again!");
			TextTexture = SDL_CreateTextureFromSurface(MainGameRenderer, TextSurface);
			if (TextTexture == NULL)
				printf("TextTexture run wrong! Please test again!");
			SDL_RenderCopy(MainGameRenderer, TextTexture, NULL, &TextRect);
			SDL_RenderPresent(MainGameRenderer);
			SDL_Delay(50);
		}
		fclose(openSourceText);
		while (1)
		{
			if (!MouseEventProcessing(MousePosX, MousePosY, MenuWindow, MainGameRenderer, Event))
				cout << "Error in Mouse Event Processing" << endl;
			if (MousePosX >= 90 && MousePosX <= 1190 && MousePosY >= 420 && MousePosY <= 600)
				break;
			cout << "Chay den day roi nha" << endl;
		}
		SDL_RenderCopy(MainGameRenderer, MapRenderData.GetTexture(), ConversationBoard.GetPositionRenderInScreen(), ConversationBoard.GetPositionRenderInScreen());
	}
}