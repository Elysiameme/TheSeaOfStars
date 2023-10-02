#pragma once

#include <SDL.h>
#include "LoginDisplayProcessing.h"
#include "LoginLogicProcressing.h"
#include "LoginDataProcessing.h"
#include <stdio.h>

void ScreenProcessing()
{
	// // Initialize some inportant things to create platform for run the code
	SDL_Init(SDL_INIT_EVERYTHING);
	int MouseClickPosX, MouseClickPosY;
	SDL_Event event;
	PosxOy StartPoint = {};
	PosxOy EndPoint = {};

	SDL_Window* MenuWindow = SDL_CreateWindow("The Sea Of Stars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, 0);
	SDL_Renderer* DrawMenu = SDL_CreateRenderer(MenuWindow, -1, 0);
Backpack: //Set Point To Return To MenuDisplay
	DisplayOption(MenuWindow, DrawMenu, 244, 200, 212, 46, "RegisterObject", ENABLE_ADD_MENUTHEME, PNG);
	DisplayOption(MenuWindow, DrawMenu, 244, 260, 212, 46, "LoginObject", DISABLE_ADD_MENUTHEME, PNG);
	DisplayOption(MenuWindow, DrawMenu, 244, 320, 212, 46, "ChangePasswordObject", DISABLE_ADD_MENUTHEME, PNG);

	while (true)
	{
		SDL_WaitEvent(&event);
		if (MouseEventProcessing(MouseClickPosX, MouseClickPosY, MenuWindow, DrawMenu, event) == true)
			if (MouseClickPosX >= 244 && MouseClickPosX <= 456 && MouseClickPosY >= 260 && MouseClickPosY <= 306)
			{
				DisplayOption(MenuWindow, DrawMenu, 198, 200, 304, 243, "LoginMenu", ENABLE_ADD_MENUTHEME, PNG);
				DisplayOption(MenuWindow, DrawMenu, 500, 500, 136, 35, "BackpackObject", DISABLE_ADD_MENUTHEME, PNG);
				DisplayOption(MenuWindow, DrawMenu, 64, 500, 136, 35, "ContinueObject", DISABLE_ADD_MENUTHEME, PNG);
				Account AccountInformation = {};
				while (true)
				{
					SDL_WaitEvent(&event);
					if (MouseEventProcessing(MouseClickPosX, MouseClickPosY, MenuWindow, DrawMenu, event) == true)
					{
						if (MouseClickPosX >= 500 && MouseClickPosX <= 636 && MouseClickPosY >= 500 && MouseClickPosY <= 535)
						{
							goto Backpack;
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 271 && MouseClickPosY <= 314)
						{
							StartPoint.X = 225;
							StartPoint.Y = 271;
							EndPoint.X = 480;
							EndPoint.Y = 314;
							TextDataProcessing(MenuWindow, DrawMenu, AccountInformation.UserName, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 357 && MouseClickPosY <= 400)
						{
							StartPoint.X = 225;
							StartPoint.Y = 357;
							EndPoint.X = 480;
							EndPoint.Y = 400;
							TextDataProcessing(MenuWindow, DrawMenu, AccountInformation.Password, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 64 && MouseClickPosX <= 200 && MouseClickPosY >= 500 && MouseClickPosY <= 535)
						{
							if (AccountInformation.UserName != NULL && AccountInformation.Password != NULL)
							{
								DataAccessProcessing(MenuWindow, DrawMenu, AccountInformation.UserName, AccountInformation.Password, NULL, USE_LOGIN_MODE);
							}
						}
					}
				}
			}
			else if (MouseClickPosX >= 244 && MouseClickPosX <= 456 && MouseClickPosY >= 200 && MouseClickPosY <= 246)
			{
				DisplayOption(MenuWindow, DrawMenu, 198, 139, 304, 322, "RegisterMenu", ENABLE_ADD_MENUTHEME, PNG);
				DisplayOption(MenuWindow, DrawMenu, 500, 500, 136, 35, "BackpackObject", DISABLE_ADD_MENUTHEME, PNG);
				DisplayOption(MenuWindow, DrawMenu, 64, 500, 136, 35, "ContinueObject", DISABLE_ADD_MENUTHEME, PNG);
				Account AccountInformation = {};
				char PasswordConfirm[18] = {};
				while (true)
				{
					SDL_PollEvent(&event);
					if (MouseEventProcessing(MouseClickPosX, MouseClickPosY, MenuWindow, DrawMenu, event) == true)
					{
						if (MouseClickPosX >= 500 && MouseClickPosX <= 636 && MouseClickPosY >= 500 && MouseClickPosY <= 535)
						{
							goto Backpack;
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 209 && MouseClickPosY <= 250)
						{
							StartPoint.X = 225;
							StartPoint.Y = 209;
							EndPoint.X = 480;
							EndPoint.Y = 250;
							TextDataProcessing(MenuWindow, DrawMenu, AccountInformation.UserName, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 296 && MouseClickPosY <= 338)
						{
							StartPoint.X = 225;
							StartPoint.Y = 296;
							EndPoint.X = 480;
							EndPoint.Y = 338;
							TextDataProcessing(MenuWindow, DrawMenu, AccountInformation.Password, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 383 && MouseClickPosY <= 426)
						{
							StartPoint.X = 225;
							StartPoint.Y = 384;
							EndPoint.X = 480;
							EndPoint.Y = 426;	
							TextDataProcessing(MenuWindow, DrawMenu, PasswordConfirm, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 64 && MouseClickPosX <= 200 && MouseClickPosY >= 500 && MouseClickPosY <= 535)
						{
							if (AccountInformation.UserName != NULL && AccountInformation.Password != NULL && PasswordConfirm != NULL)
							{
								if (strcmp(AccountInformation.Password, PasswordConfirm) == 0)
								{
									DataAccessProcessing(MenuWindow, DrawMenu, AccountInformation.UserName, AccountInformation.Password, NULL, USE_REGISTER_MODE);
								}
								else
									NoticeWindowOption(1, 1, 300, 184, PNG, "CPNotMarchObject", "Confirm Password Does Not Match");
							}
						}
					}				
				}
			}
			else if (MouseClickPosX >= 244 && MouseClickPosX <= 456 && MouseClickPosY >= 320 && MouseClickPosY <= 366)
			{
				DisplayOption(MenuWindow, DrawMenu, 198, 139, 304, 322, "ChangePasswordMenu", ENABLE_ADD_MENUTHEME, PNG);
				DisplayOption(MenuWindow, DrawMenu, 500, 500, 136, 35, "BackpackObject", DISABLE_ADD_MENUTHEME, PNG);
				DisplayOption(MenuWindow, DrawMenu, 64, 500, 136, 35, "ContinueObject", DISABLE_ADD_MENUTHEME, PNG);
				Account AccountInformation = {};
				char NewPassword[18] = {};
				while (true)
				{
					SDL_WaitEvent(&event);
					if (MouseEventProcessing(MouseClickPosX, MouseClickPosY, MenuWindow, DrawMenu, event) == true)
					{
						if (MouseClickPosX >= 500 && MouseClickPosX <= 636 && MouseClickPosY >= 500 && MouseClickPosY <= 535)
						{
							goto Backpack;
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 209 && MouseClickPosY <= 250)
						{
							StartPoint.X = 225;
							StartPoint.Y = 209;
							EndPoint.X = 480;
							EndPoint.Y = 250;
							TextDataProcessing(MenuWindow, DrawMenu, AccountInformation.UserName, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 296 && MouseClickPosY <= 338)
						{
							StartPoint.X = 225;
							StartPoint.Y = 297;
							EndPoint.X = 480;
							EndPoint.Y = 338;
							TextDataProcessing(MenuWindow, DrawMenu, AccountInformation.Password, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 225 && MouseClickPosX <= 480 && MouseClickPosY >= 383 && MouseClickPosY <= 426)
						{
							StartPoint.X = 225;
							StartPoint.Y = 385;
							EndPoint.X = 480;
							EndPoint.Y = 426;
							TextDataProcessing(MenuWindow, DrawMenu, NewPassword, StartPoint, EndPoint);
						}
						else if (MouseClickPosX >= 64 && MouseClickPosX <= 200 && MouseClickPosY >= 500 && MouseClickPosY <= 535)
						{
							if (AccountInformation.UserName != NULL && AccountInformation.Password != NULL && NewPassword != NULL)
							{
								DataAccessProcessing(MenuWindow, DrawMenu, AccountInformation.UserName, AccountInformation.Password, NewPassword, USE_CHANGEPASSWORDMODE);
							}
						}
					}
				}
			}
	}
}
