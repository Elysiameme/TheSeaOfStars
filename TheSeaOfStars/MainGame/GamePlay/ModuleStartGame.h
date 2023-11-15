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
#include "ConversationProcessing.h"
//#include "QuestSystem.h"



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


void ConversationCaptainOfficeVR(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer, Map MapRenderData)
{
	for (int i = 1; i < 10; i++)
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


	CaptainDucOfficeVR.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/WorkingRoom.txt",
							   "TheSeaOfStars/MainGame/GamePlay/Map/WorkingRoom.png",
								MainGameRenderer);
	CaptainDucOfficeVR.RenderMap();

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
