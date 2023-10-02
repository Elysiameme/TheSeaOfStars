#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
typedef enum 
{
	DISABLE_ADD_MENUTHEME = 0,
	ENABLE_ADD_MENUTHEME = 1
} MENU_THEME_OPTION;
typedef enum 
{
	JPEG = 0,
	PNG = 1,
} PICTURE_TYPE;
void DisplayOption(SDL_Window* MenuWindow, SDL_Renderer* DrawMenu, int x, int y, int w, int h, const char* FileName, MENU_THEME_OPTION mode, PICTURE_TYPE type)
{
	// Initialize Position and Size
	SDL_Rect ObjectPos = { x, y, w, h };
	// Initialize the Path to the File need to load
	char Path[500];
	// Add Menutheme to the Screen by some step consist of create Surface, Texture, Copy to renderer and Present.
	// The step add Menutheme can be enable or disable by conditional statement.
	// Developer can adjust setting via use ENABLE mode or DISABLE mode by write it into the argument MENU_THEME_OPTION in Function.
	// The flags of MENU_THEME_OPTION have two, include ENABLE_ADD_MENUTHEME and DISABLE_MENU_THEME.
	// If you want choose one of two mode, please write corresponding flags into corresponding argument.
	if (mode == ENABLE_ADD_MENUTHEME)
	{
		SDL_Surface* MenuTheme = IMG_Load("TheSeaOfStars/Data Processing and Storage/LoginDisplayDesignObject/MenuTheme.jpeg");
		if (MenuTheme == NULL)
		{
			printf("Can't Load The MenuTheme Image !");
		}
		SDL_Texture* MenuThemeTexture = SDL_CreateTextureFromSurface(DrawMenu, MenuTheme);
		SDL_FreeSurface(MenuTheme);
		SDL_RenderCopy(DrawMenu, MenuThemeTexture, NULL, NULL);
	}
	// Use variable 'Path' to save the link to the file you need to load to the window
	// If the picture have different type example jpeg, png, ....., you can use corresponding flags in enum PICTURE_TYPE
	// The Path will have the link to the folder save object was designed by the developer (Vu Duc Huy)
	// If you write the Filename, program will choose the file corresponding
	strcpy_s(Path, 350, "TheSeaOfStars/Data Processing and Storage/LoginDisplayDesignObject/");
	strcat_s(Path, 350, FileName);
	if (type == JPEG)
	{
		strcat_s(Path, 350, ".jpeg");
	}
	else if (type == PNG)
	{
		strcat_s(Path, 350, ".png");
	}
	SDL_Surface* ObjectDisplay = IMG_Load(Path);
	if (ObjectDisplay == NULL)
	{
		printf("Can't Load The Object !");
	}
	SDL_Texture* ObjectDisplayTexture = SDL_CreateTextureFromSurface(DrawMenu, ObjectDisplay);
	SDL_FreeSurface(ObjectDisplay);	
	SDL_RenderCopy(DrawMenu, ObjectDisplayTexture, NULL, &ObjectPos);
	SDL_RenderPresent(DrawMenu);
}
void NoticeWindowOption(int x, int y, int w, int h, PICTURE_TYPE type, const char* FileName, const char* NoticeName)
{
	// The function will be create the another window to display the notice you need
	// You can change the settings of Position, type of picture and the Path to the file you want to load to the window
	// by write the value into corresponding argument 
	// Initialize the Path to the File need to load
	// The Path will have the link to the folder save object was designed by the developer (Vu Duc Huy)
	// If you write the Filename, program will choose the corresponding file
	char Path[500];
	strcpy_s(Path, 350, "TheSeaOfStars/Data Processing and Storage/LoginDisplayDesignObject/");
	strcat_s(Path, 350, FileName);
	if (type == JPEG)
	{
		strcat_s(Path, 350, ".jpeg");
	}
	else if (type == PNG)
	{
		strcat_s(Path, 350, ".png");
	}
	//Initialize Window and Renderer to Create the Notice 
	SDL_Window* WindowNotice = SDL_CreateWindow(NoticeName, 200, 450, w, h, 0);
	SDL_Renderer* NoticeRenderer = SDL_CreateRenderer(WindowNotice, -1, 0);
	// Initialize Position and Size
	SDL_Rect ObjectPos = { x, y, w, h };
	// Create Surface
	SDL_Surface* Notice = IMG_Load(Path);
	if (Notice == NULL)
	{
		printf("Can't Load The Object !");
	}

	//Create Texture From Surface
	SDL_Texture* NoticeTexture = SDL_CreateTextureFromSurface(NoticeRenderer, Notice);
	//Free Surface
	SDL_FreeSurface(Notice);
	SDL_RenderCopy(NoticeRenderer, NoticeTexture, NULL, &ObjectPos);
	SDL_RenderPresent(NoticeRenderer);
	SDL_Delay(2000);
	SDL_DestroyWindow(WindowNotice);
}
