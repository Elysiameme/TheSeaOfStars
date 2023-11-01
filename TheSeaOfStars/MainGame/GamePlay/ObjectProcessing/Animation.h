#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ObjectStructures.h"
#include "C:/Users/VuDucHuy/OneDrive - st.utc2.edu.vn/Máy tính/TheSeaOfStars/TheSeaOfStars/TheSeaOfStars/MainGame/GamePlay/PeripheralsDataProcessing.h"
#include "Map.h"
#include <math.h>

	using namespace std;
	

	enum ANIMATION_DIRECTION
	{
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};


	enum ANIMATION_RENDER_MODE
	{
		CHARACTER_MOVEMODE = 1,
		ITEM_MODE = 2,
		CHARACTER_ACTIONMODE = 3
	};

	struct ObjectPosInScreen
	{
		int x, y;
	};
	class Animation : public ObjectStructure
	{
	private:
		ANIMATION_RENDER_MODE rendermode;
		ANIMATION_DIRECTION renderdirection;
		int numberframe;
		int frame_width;
		int frame_height;
		vector<SDL_Rect> RenderFrames;
	public:
		void SetOptionAnimation(int frames, ANIMATION_DIRECTION direction, ANIMATION_RENDER_MODE mode, SDL_Renderer* GameRenderer);
		void RenderAnimation(SDL_Rect* PosRender, SDL_Renderer* GameRenderer, Map MapData);
	};


	void Animation::SetOptionAnimation(int frames, ANIMATION_DIRECTION direction, ANIMATION_RENDER_MODE mode, SDL_Renderer* GameRenderer)
	{
		SDL_Rect SaveFrames = {};
		int Img_width = 0, Img_height = 0;
		numberframe = frames;
		rendermode = mode;
		renderdirection = direction;
		SDL_QueryTexture(this->ObjectTexture, NULL, NULL, &Img_width, &Img_height);
		this->PositionFromSourceIMG = { 1, 1, Img_width, Img_height };

		switch (rendermode)
		{
			case CHARACTER_MOVEMODE:

				if (direction == LEFT || direction == RIGHT)
				{
					frame_width = Img_width / frames;
					frame_height = Img_height;
					for (int i = 0; i < numberframe; i++)
					{
						SaveFrames.x = i * frame_width + 1;
						SaveFrames.w = frame_width;
						SaveFrames.y = 1;
						SaveFrames.h = frame_height;
						this->RenderFrames.push_back(SaveFrames);
					}
				}
				if (direction == UP || direction == DOWN)
				{
					frame_width = Img_width;
					frame_height = Img_height / frames;

					for (int i = 0; i < numberframe; i++)
					{
						SaveFrames.y = i * frame_height + 1;
						SaveFrames.h = frame_height;
						SaveFrames.x = 1;
						SaveFrames.w = frame_width;
						this->RenderFrames.push_back(SaveFrames);
					}
				}
				break;
			case CHARACTER_ACTIONMODE:
				break;
			case ITEM_MODE:
				break;
		}
		
	}


	void Animation::RenderAnimation(SDL_Rect* PosRender, SDL_Renderer* GameRenderer, Map MapData)
	{
		ObjectPosInScreen Character = {};
		PosRender->w = RenderFrames[0].w;
		PosRender->h = RenderFrames[0].h;

		if (rendermode == CHARACTER_MOVEMODE)
		{
			Character = { PosRender->x + (PosRender->w / 2), PosRender->y + PosRender->h - 5 };
			int PosTile = (MapData.Map_width / 16) * ceil(Character.y / 16) + floor(Character.x / 16) - 1;
			switch (renderdirection)
			{
			case UP:
				if ((MapData.MapTileID[PosTile - (MapData.Map_width / 16)] == 0))
					return;
				for (int i = 0; i < numberframe; i++)
				{
					PosRender->y -= 5;
					SDL_RenderCopy(GameRenderer, this->ObjectTexture, &RenderFrames[i], PosRender);
					SDL_RenderPresent(GameRenderer);
					SDL_RenderCopy(GameRenderer, MapData.GetTexture(), PosRender, PosRender);
					SDL_Delay(50);
				}
				break;
			case DOWN:
				if ((MapData.MapTileID[PosTile + (MapData.Map_width / 16)] == 0) && renderdirection == DOWN)
					return;
				for (int i = 0; i < numberframe; i++)
				{
					PosRender->y = PosRender->y + 5;

					SDL_RenderCopy(GameRenderer, this->ObjectTexture, &RenderFrames[i], PosRender);
					SDL_RenderPresent(GameRenderer);
					SDL_RenderCopy(GameRenderer, MapData.GetTexture(), PosRender, PosRender);
					SDL_Delay(50);
				}
				break;
			case LEFT:
				if (MapData.MapTileID[PosTile - 1] == 0)
				{
					return;
				}
					
			case RIGHT:
				if ((MapData.MapTileID[PosTile + 1] == 0) && renderdirection == RIGHT)
					return;
				for (int i = 0; i < numberframe; i++)
				{
					if (renderdirection == LEFT)
						PosRender->x = PosRender->x - 5;
					if (renderdirection == RIGHT)
						PosRender->x = PosRender->x + 5;
					SDL_RenderCopy(GameRenderer, this->ObjectTexture, &RenderFrames[i], PosRender);
					SDL_RenderPresent(GameRenderer);
					SDL_RenderCopy(GameRenderer, MapData.GetTexture(), PosRender, PosRender);
					SDL_Delay(50);
				}
				break;
			}

		}
		else if (rendermode == ITEM_MODE)
		{
			while (true)
			{
				for (int i = 0; i < numberframe; i++)
				{
					SDL_RenderCopy(GameRenderer, this->ObjectTexture, &RenderFrames[i], PosRender);
					SDL_Delay(50);
					SDL_RenderPresent(GameRenderer);
					SDL_RenderCopy(GameRenderer, MapData.GetTexture(), PosRender, PosRender);
				}
			}
		}
	}