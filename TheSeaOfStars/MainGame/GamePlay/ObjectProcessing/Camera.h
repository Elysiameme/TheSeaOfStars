#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"
#include "ObjectStructures.h"
#include "Character.h"

using namespace std;

class MainCamera
{
private:
	SDL_Rect Camera;
public:
	void Initialized_Camera();
	void View(SDL_Renderer* GameRenderer);
	//void 
};


void MainCamera::Initialized_Camera()
{
	Camera.w = 640;
	Camera.h = 320;
}
void MainCamera::View(SDL_Renderer* Game_Renderer)
{

}
