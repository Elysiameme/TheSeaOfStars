#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ObjectStructures.h"

	using namespace std;
	

	enum ANIMATION_DIRECTION
	{
		NONE = 0,
		HORIZONTAL = 1,
		VERTICAL = 2
	};


	class Animation : public ObjectStructure
	{
	private:
		string PathtoSourceImg;
		int numberframe;
		int frame_width;
		int frame_height;
		SDL_Rect* RenderFrames;
	public:
		void SetOptionAnimation(int frames, const char* Path, ANIMATION_DIRECTION direction, SDL_Renderer* GameRenderer);
		void RenderAnimation();
	};


	void Animation::SetOptionAnimation(int frames, const char* Path, ANIMATION_DIRECTION direction, SDL_Renderer* GameRenderer)
	{
		int Img_width = 0, Img_height = 0;
		this->Initialized(Path, GameRenderer);
		SDL_QueryTexture(this->ObjectTexture, NULL, NULL, &Img_width, &Img_height);
		PathtoSourceImg = Path;
		numberframe = frames;
		if (direction == HORIZONTAL)
		{
			frame_width = Img_width / frames;
			frame_height = Img_height;
			RenderFrames = new SDL_Rect[numberframe - 1];

			for (int i = 0; i < numberframe; i++)
			{
				RenderFrames[i].x = i * frame_width;
				RenderFrames[i].w = RenderFrames[i].x + frame_width;
				RenderFrames[i].y = 0;
				RenderFrames[i].h = frame_height;
			}
		}
		if (direction == VERTICAL)
		{
			frame_width = Img_width;
			frame_height = Img_height / frames;
			RenderFrames = new SDL_Rect[numberframe - 1];

			for (int i = 0; i < numberframe; i++)
			{
				RenderFrames[i].y = i * frame_height;
				RenderFrames[i].h= RenderFrames[i].y + frame_height;
				RenderFrames[i].x = 0;
				RenderFrames[i].w = frame_width;
			}
		}
	}


	void Animation::RenderAnimation()
	{
		
	}