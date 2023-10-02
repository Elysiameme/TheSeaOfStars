#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "LoginDataProcessing.h"
#include "LoginDisplayProcessing.h"

bool MouseEventProcessing(int& x, int& y, SDL_Window* MenuWindow, SDL_Renderer* DrawMenu, SDL_Event event);
void TextDataProcessing(SDL_Window* MenuWindow, SDL_Renderer* DrawMenu, char TextInput[], PosxOy StartPoint, PosxOy FinishPoint);
void removeLastchar(char string[]);
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

//The function handles input and output and displays characters on the screen

void TextDataProcessing(SDL_Window* MenuWindow, SDL_Renderer* DrawMenu, char TextInput[], PosxOy StartPoint, PosxOy FinishPoint)
{
	TTF_Init();
	SDL_Event InputTextProcessing;
	SDL_Surface* TextSurface = NULL;
	SDL_Texture* TextTexture = NULL;
	SDL_Rect TextRect = {}, InputBoxRect = {};
	InputBoxRect.x = StartPoint.X;
	InputBoxRect.y = StartPoint.Y;
	InputBoxRect.w = FinishPoint.X - StartPoint.X;
	InputBoxRect.h = FinishPoint.Y - StartPoint.Y;
	TextRect.x = StartPoint.X + 2;
	TextRect.y = StartPoint.Y + 2;
	TextRect.w = 0;
	TextRect.h = 39;
	TTF_Font* TextFont = NULL; 
	SDL_Color TextColor = { 0, 0, 0 };
	
	strcpy_s(TextInput, 51, "");
	SDL_SetRenderDrawColor(DrawMenu, 255, 255, 255, 0);
	SDL_RenderFillRect(DrawMenu, &InputBoxRect);
	SDL_RenderPresent(DrawMenu);
	// Start Text Input Mode in SDL2
	SDL_StartTextInput();
	while (true)
	{
		SDL_PollEvent(&InputTextProcessing);
		switch (InputTextProcessing.type)
		{
			case SDL_QUIT:
				SDL_DestroyRenderer(DrawMenu);
				SDL_DestroyWindow(MenuWindow);
				SDL_Quit();
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_MinimizeWindow(MenuWindow);
				break;
			case SDL_TEXTINPUT:
				if (strlen(TextInput) < 17)
				{
					TextRect.w = TextRect.w + 15;
					SDL_RenderFillRect(DrawMenu, &InputBoxRect);
					strcat_s(TextInput, 18, InputTextProcessing.text.text);
					TextFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 1000);
					if (TextFont == NULL)
						printf("TextFont run wrong! Please test again!");
					TextSurface = TTF_RenderText_Solid(TextFont, TextInput, TextColor);
					if (TextSurface == NULL)
						printf("TextSurface run wrong! Please test again!");
					TextTexture = SDL_CreateTextureFromSurface(DrawMenu, TextSurface);
					if (TextTexture == NULL)
						printf("TextTexture run wrong! Please test again!");
					SDL_RenderCopy(DrawMenu, TextTexture, NULL, &TextRect);
					SDL_RenderPresent(DrawMenu);
				}
				else
				{
					NoticeWindowOption(1, 1, 300, 33, PNG, "CharLimitObject", "CharLimit");
					
				}
				break;
			case SDL_KEYDOWN:
				if (InputTextProcessing.key.keysym.sym == SDLK_RETURN)
				{
					goto Quit;
				}
				else if (InputTextProcessing.key.keysym.sym == SDLK_BACKSPACE)
				{
					TextRect.w = TextRect.w - 15;
					SDL_RenderFillRect(DrawMenu, &InputBoxRect);
					removeLastchar(TextInput);
					TextFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 1000);
					if (TextFont == NULL)
						printf("TextFont run wrong! Please test again!");
					TextSurface = TTF_RenderText_Solid(TextFont, TextInput, TextColor);
					if (TextSurface == NULL)
						printf("TextSurface run wrong! Please test again!");
					TextTexture = SDL_CreateTextureFromSurface(DrawMenu, TextSurface);
					if (TextTexture == NULL)
						printf("TextTexture run wrong! Please test again!");
					SDL_RenderCopy(DrawMenu, TextTexture, NULL, &TextRect);
					SDL_RenderPresent(DrawMenu);
				}
				break;
		}
	}
Quit:
	SDL_StopTextInput();
	TTF_Quit();
}
void removeLastchar(char string[])
{
	int DeletePos = 0;
	
	for (int i = 0; i <= strlen(string); i++)
	{
		if (string[i] == '\0')
		{
			DeletePos = i - 1;
			break;
		}
			
	}
	string[DeletePos] = '\0';
	string[DeletePos + 1] = NULL;
}
/*bool StringComparativeProcessing(char string1[], char string2[])
{

}*/

