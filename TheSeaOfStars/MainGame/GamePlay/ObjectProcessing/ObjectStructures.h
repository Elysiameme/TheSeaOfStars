#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "TheSeaOfStars/MainGame/GamePlay/StructMode.h"

	using namespace std; 


	class ObjectStructure
	{
	protected:
		SDL_Rect PositionRenderInScreen;
		SDL_Rect PositionFromSourceIMG;
		SDL_Texture* ObjectTexture;
		SDL_Surface* ObjectSurface;
	public:
		void Initialized(const char* Path, SDL_Renderer* GameRenderer);
		void Destroy();
		void RenderPicture(SDL_Renderer* GameRenderer, int Xpos, int Ypos, int SizeRender);

	};


	void ObjectStructure::Initialized(const char* Path, SDL_Renderer* GameRenderer)
		// Path is the link to source image file	
	{
		ObjectSurface = IMG_Load(Path);
		ObjectTexture = SDL_CreateTextureFromSurface(GameRenderer, ObjectSurface);
		if (SDL_QueryTexture(ObjectTexture, NULL, NULL, &PositionFromSourceIMG.w, &PositionFromSourceIMG.h) == 0)
		{
			cout << "Error : Cann't Loading The Image's Size!" << endl << "Error File : " << Path;
		}
		else
		{
			PositionFromSourceIMG.x = 0;
			PositionFromSourceIMG.y = 0;
		}
	}

	void ObjectStructure::Destroy()
	{
		SDL_FreeSurface(ObjectSurface);
		SDL_DestroyTexture(ObjectTexture);
	}
	

	void ObjectStructure::RenderPicture(SDL_Renderer* GameRenderer, int Xpos, int Ypos, int SizeRender)
		// Xpos, Ypos is X, Y Position in Game's Window
	{
		PositionRenderInScreen.x = Xpos;
		PositionRenderInScreen.y = Ypos;
		PositionRenderInScreen.w = PositionFromSourceIMG.w * SizeRender;
		PositionRenderInScreen.h = PositionFromSourceIMG.h * SizeRender;

		SDL_RenderCopy(GameRenderer, ObjectTexture, &PositionFromSourceIMG, &PositionRenderInScreen);
		SDL_RenderPresent(GameRenderer);
	}



	