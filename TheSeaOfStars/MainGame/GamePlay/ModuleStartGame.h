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
#include <thread>
#include <mutex>
#include <condition_variable>
#include "PeripheralsDataProcessing.h"
#include "QuestSystem.h"



void GameTrailer(SDL_Renderer* MainGameRenderer)
{
	TTF_Init();
	SDL_Surface* TextSurface = NULL;
	SDL_Texture* TextTexture = NULL;
	SDL_Rect TextRect = {};
	TTF_Font* TextFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 28);
	SDL_Color TextColor = { 255, 255, 255 };
	FILE* loadPologuale;
	ObjectStructure Pologuale = {};


	Pologuale.Load_IMG("TheSeaOfStars/Data Processing and Storage/UIUXDesign/BackgroundTrailerGame.png", MainGameRenderer);
	Pologuale.Initialized_IMG();
	TextRect.w = 10;
	TextRect.h = 20;


	for (int i = 1; i <= 3; i++)
	{
		Pologuale.RenderPicture(MainGameRenderer, 1, 1, 1);
		TextRect.x = 100;
		TextRect.y = 100;

		char Path[200] = "TheSeaOfStars/Design Documentation/Story Design/TrailerGamePologuale/Polo";
		char IntegerElement[10];
		_itoa_s(i, IntegerElement, 10);
		strcat_s(Path, IntegerElement);
		strcat_s(Path, ".txt");
		errno_t checkopenfile = fopen_s(&loadPologuale, Path, "r");
		if (checkopenfile != 0)
		{
			cout << "Error : Cann't Open The Text Trailer File! Error Link :" << Path;
		}
		else if (checkopenfile == 0)
		{
			char c = NULL;
			while (c != EOF)
			{
				c = fgetc(loadPologuale);
				string TextReaded = "";
				TextReaded += c;
				cout << "Ky Tu lay ra :" << TextReaded << endl;
				if (TextReaded == "\n")
				{
					TextRect.x = 100;
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
				SDL_Delay(1);
			}
			fclose(loadPologuale);
			SDL_Delay(2000);
		}
	}
}

void ConversationProcessing(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer, const char* SourceText, Map MapRenderData)
{
	ObjectStructure ConversationBoard = {};
	ConversationBoard.Load_IMG( "TheSeaOfStars/Design Documentation/Design Idea/ConversationBoard.png", MainGameRenderer);
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
		SDL_RenderCopy(MainGameRenderer, MapRenderData.GetTexture(), ConversationBoard.GetPositionRenderFromSourceIMG(), ConversationBoard.GetPositionRenderInScreen());
	}
}


void ConversationCaptainOfficeVR(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer, Map MapRenderData)
{
	for (int i = 1; i < 11; i++)
	{
		cout << "Checking times repeated : " << i << endl;
		char Path[200] = "TheSeaOfStars/Design Documentation/Story Design/ConversationStoryCaptainOfficeVR/Conversation";
		char IntegerElement[10];
		_itoa_s(i, IntegerElement, 10);
		strcat_s(Path, IntegerElement);
		strcat_s(Path, ".txt");
		ConversationProcessing(MenuWindow, MainGameRenderer, Path, MapRenderData);
	}
}


void CaptainOfficeVRScene(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer)
{
	thread QuestThread(QuestSystemCenterProcessing);
	QuestThread.detach();

	CaptainDucOfficeVR.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/WorkingRoom.txt",
							   "TheSeaOfStars/MainGame/GamePlay/Map/WorkingRoom.png",
								MainGameRenderer);

	CaptainDuc.GetRenderPosition(562, 259);
	CaptainDuc.RenderCharacter("TheSeaOfStars/Design Documentation/Design Idea/CaptainDuc.png",
								MainGameRenderer);

	ConversationCaptainOfficeVR(MenuWindow, MainGameRenderer, CaptainDucOfficeVR);

	
	CaptainDuc.Move("TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveUp.png",
					"TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveDown.png",
					"TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveRight.png",
					"TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveLeft.png",
					 MainGameRenderer, CaptainDucOfficeVR);
}