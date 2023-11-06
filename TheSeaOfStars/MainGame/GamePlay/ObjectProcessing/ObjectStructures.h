#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

	using namespace std; 


	class ObjectStructure
	{
	protected:
		SDL_Rect PositionRenderInScreen;
		SDL_Rect PositionFromSourceIMG;
		SDL_Texture* ObjectTexture;
		SDL_Surface* ObjectSurface;
		const char* PathtoSourceImg;
	public:

		void Load_IMG(const char* Path, SDL_Renderer* GameRenderer);
		void Initialized_IMG();
		void RenderPicture(SDL_Renderer* GameRenderer, int Xpos, int Ypos, int SizeRender);
		SDL_Texture* GetTexture()
		{
			return ObjectTexture;
		}
		SDL_Rect* GetPositionRenderInScreen() { return &PositionRenderInScreen; }
		SDL_Rect* GetPositionRenderFromSourceIMG() { return &PositionFromSourceIMG; }
		~ObjectStructure() {
			SDL_FreeSurface(ObjectSurface);
			SDL_DestroyTexture(ObjectTexture);
		}

	};


	void ObjectStructure::Load_IMG(const char* Path, SDL_Renderer* GameRenderer)
	{
		// Path is the link to source image file

		ObjectSurface = IMG_Load(Path);
		if (ObjectSurface == NULL)
			cout << "Error : Cann't Loading The Image's Surface! Enror Link :" << Path;
		else
		{
			ObjectTexture = SDL_CreateTextureFromSurface(GameRenderer, ObjectSurface);
			if (ObjectTexture == NULL)
				cout << "Error : Cann't Loading The Image's Texture!";
		}
	}


	void ObjectStructure::Initialized_IMG()
	{
		if (SDL_QueryTexture(ObjectTexture, NULL, NULL, &PositionFromSourceIMG.w, &PositionFromSourceIMG.h) != 0)
			cout << "Error : Cann't Loading The Image's Size!";
		else
		{
			PositionFromSourceIMG.x = 1;
			PositionFromSourceIMG.y = 1;
		}
	}

	
	void ObjectStructure::RenderPicture(SDL_Renderer* GameRenderer, int Xpos, int Ypos, int SizeRender)
		// Xpos, Ypos is X, Y Position in Game's Window
	{
		PositionRenderInScreen.x = Xpos;
		PositionRenderInScreen.y = Ypos;
		PositionFromSourceIMG.w = PositionFromSourceIMG.w / SizeRender;
		PositionFromSourceIMG.h = PositionFromSourceIMG.h / SizeRender;
		PositionRenderInScreen.w = PositionFromSourceIMG.w * SizeRender;
		PositionRenderInScreen.h = PositionFromSourceIMG.h * SizeRender;

		SDL_RenderCopy(GameRenderer, ObjectTexture, &PositionFromSourceIMG, &PositionRenderInScreen);
		SDL_RenderPresent(GameRenderer);
	}



	