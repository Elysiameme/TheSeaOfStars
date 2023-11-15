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

using namespace std;

void HibernateCabinScene(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer, Map MapRenderData)
{
	HibernateCabin.RenderMap();

	CaptainDuc.GetRenderPosition(562, 259);
	CaptainDuc.RenderCharacter("TheSeaOfStars/Design Documentation/Design Idea/CaptainDuc.png",
		MainGameRenderer);


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

void MapLoading(SDL_Renderer* MainGameRenderer)
{
	HibernateCabin.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/HibernationCabin.png",
						   "TheSeaOfStars/MainGame/GamePlay/Map/HibernationCabin.txt",
							MainGameRenderer);

	CommanderRoom.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/CommanderRoom.png",
					   "TheSeaOfStars/MainGame/GamePlay/Map/CommanderRoom.txt",
						MainGameRenderer);

	WarpEngineRoom.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/EngineRoom.png",
						   "TheSeaOfStars/MainGame/GamePlay/Map/EngineRoom.txt",
							MainGameRenderer);

	BaseInAntarctica.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/BaseInArtactic.png",
							 "TheSeaOfStars/MainGame/GamePlay/Map/BaseInArtactic.txt",
							  MainGameRenderer);

	IceCage.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/IceCage.png",
					"TheSeaOfStars/MainGame/GamePlay/Map/IceCage.txt",
					 MainGameRenderer);

	Sentinus_Antarctic.LoadMap("TheSeaOfStars/MainGame/GamePlay/Map/ArtacticSentinusIV.png",
							   "TheSeaOfStars/MainGame/GamePlay/Map/ArtacticSentinusIV.txt",
								MainGameRenderer);
}
void GamePlay(SDL_Window* MenuWindow, SDL_Renderer* MainGameRenderer)
{
	MapLoading(MainGameRenderer);
	HibernateCabinScene(MenuWindow, MainGameRenderer, HibernateCabin);

	CaptainDuc.Move("TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveUp.png",
		"TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveDown.png",
		"TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveRight.png",
		"TheSeaOfStars/Design Documentation/Design Idea/CaptainDucMoveLeft.png",
		MainGameRenderer, CaptainDucOfficeVR);
}