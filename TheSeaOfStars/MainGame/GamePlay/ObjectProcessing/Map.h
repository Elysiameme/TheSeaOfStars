#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "ObjectStructures.h"
using namespace std;

class Map : public ObjectStructure
{
private:
public:
	int Map_width, Map_height;
	vector<int> MapTileID;
	vector<SDL_Rect> MapTileBlock;
	void LoadMap(const char* Pathtxt, const char* PathIMG, SDL_Renderer* GameRenderer);
	void RenderMap();
};


void Map::LoadMap(const char* Pathtxt, const char* PathIMG, SDL_Renderer* GameRenderer)
{
	FILE* filemap;
	SDL_Rect InputPositionMaptiles = {};
	int Xtiles = 0, Ytiles = 0, IDreaded = 0;
	
	errno_t openfilemap = fopen_s(&filemap, Pathtxt, "r+");
	if (openfilemap != 0)
	{
		cout << "Error : Cann't Open The Map File! Error Link :" << Pathtxt;
	}
	else if (openfilemap == 0)
	{
		this->Load_IMG(PathIMG, GameRenderer);
		this->Initialized_IMG();
		this->GetRenderer(GameRenderer);
		while (fscanf_s(filemap, "%d ", &IDreaded) != EOF)
		{
			if (Xtiles < (PositionFromSourceIMG.w/16) )
			{
				Xtiles++;
			}
			else
			{
				Xtiles = 1;
				Ytiles++;
			}
			InputPositionMaptiles = { (((Xtiles - 1) * 16) + 1), ((Ytiles * 16) + 1), 16, 16 };
			this->MapTileID.push_back(IDreaded);
			this->MapTileBlock.push_back(InputPositionMaptiles);
		}
	}
}


void Map::RenderMap()
{
	SDL_QueryTexture(this->ObjectTexture, NULL, NULL, &Map_width, &Map_height);
	this->RenderPicture(this->ObjectRenderer, 1, 1, (Map_width / 1280));
}