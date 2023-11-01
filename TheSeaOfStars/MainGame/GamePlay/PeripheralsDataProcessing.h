#pragma once

#include <iostream>
#include <SDL.h>


using namespace std;

bool MouseEventProcessing(int& x, int& y, SDL_Window* MenuWindow, SDL_Renderer* DrawMenu, SDL_Event event)
{
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				SDL_DestroyRenderer(DrawMenu);
				SDL_DestroyWindow(MenuWindow);
				SDL_Quit();
			}
			else if (event.type == SDL_WINDOWEVENT_MINIMIZED)
			{
				SDL_MinimizeWindow(MenuWindow);
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					x = event.button.x;
					y = event.button.y;
					return true;
				}
			}
		}
	}
}
SDL_Event KeyboardEventProcessing()
{
	SDL_Event event;
	while (true)
	{
		while (SDL_WaitEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
				return event;
		}
	}
}
