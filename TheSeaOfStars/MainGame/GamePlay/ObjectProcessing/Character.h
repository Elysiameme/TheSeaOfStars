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

public:
	void MoveTop(const char* Path);
	void MoveBottom(const char* Path);
	void MoveLeft(const char* Path);
	void MoveRight(const char* Path);
};

void Character::MoveTop(const char* Path)
{
	Animation movetop;
	movetop.SetOptionAnimation(3, Path, VERTICAL);

}
