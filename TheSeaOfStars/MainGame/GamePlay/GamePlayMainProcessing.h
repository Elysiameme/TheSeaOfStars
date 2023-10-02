#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "MainProperties.h"

	using namespace std;
	
	int GamePlayMainProcessing()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		MainGameWindow = SDL_CreateWindow("The Sea Of Stars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		MainGameRenderer = SDL_CreateRenderer(MainGameWindow, -1, 0);

	}