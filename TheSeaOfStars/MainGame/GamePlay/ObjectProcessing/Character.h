#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "ObjectStructures.h"

using namespace std;


class Character : public ObjectStructure
{
private:
	int CharacterMoveFrames;
	SDL_Rect RenderPosition;
public:
	void GetRenderPosition(int x, int y)
	{
		RenderPosition.x = x;
		RenderPosition.y = y;
	}
	void RenderCharacter(const char* characterPath, SDL_Renderer* GameRenderer)
	{
		this->Load_IMG(characterPath, GameRenderer);
		this->Initialized_IMG();
		this->RenderPicture(GameRenderer, RenderPosition.x, RenderPosition.y, 1);
	}
	void Move(const char* PathTop, const char* PathDown, const char* PathRight, const char* PathLeft, SDL_Renderer* GameRenderer, Map MapData);
};


void Character::Move(const char* PathTop, const char* PathDown, const char* PathRight, const char* PathLeft, SDL_Renderer* GameRenderer, Map MapData)
{
	Animation movetop = {}, movedown = {}, moveleft = {}, moveright = {};

	movetop.Load_IMG(PathTop, GameRenderer);
	movetop.Initialized_IMG();
	movedown.Load_IMG(PathDown, GameRenderer);
	movedown.Initialized_IMG();
	moveleft.Load_IMG(PathLeft, GameRenderer);
	moveleft.Initialized_IMG();
	moveright.Load_IMG(PathRight, GameRenderer);
	moveright.Initialized_IMG();

	movetop.SetOptionAnimation(3, UP, CHARACTER_MOVEMODE, GameRenderer);
	movedown.SetOptionAnimation(3, DOWN, CHARACTER_MOVEMODE, GameRenderer);
	moveleft.SetOptionAnimation(3, LEFT, CHARACTER_MOVEMODE, GameRenderer);
	moveright.SetOptionAnimation(3, RIGHT, CHARACTER_MOVEMODE, GameRenderer);


	while (true)
	{
		SDL_Event KeyboardEvent = KeyboardEventProcessing();
		switch (KeyboardEvent.key.keysym.sym)
		{
			case 1073741906:
				cout << "Pressed" << endl;
				movetop.RenderAnimation(&RenderPosition, GameRenderer, MapData);
				break;
			case 1073741905:
				movedown.RenderAnimation(&RenderPosition, GameRenderer, MapData);
				break;
			case 1073741904:
				moveleft.RenderAnimation(&RenderPosition, GameRenderer, MapData);
				break;
			case 1073741903:
				moveright.RenderAnimation(&RenderPosition, GameRenderer, MapData);
				break;
		}
	}
	

}
