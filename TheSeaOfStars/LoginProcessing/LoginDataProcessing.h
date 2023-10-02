#pragma once

#include <stdio.h>
#include <conio.h>
#include <SDL.h>
#include <string.h>
#include "LoginDisplayProcessing.h"

//Struct Data Link With Account
typedef struct DataAccount
{
	int level;
	char usernameingame[50];
}DataAccount;

//Struct Account
typedef struct Account
{
	char UserName[18];
	char Password[18];
	DataAccount* Data;
}Account;

//Struct PosxOy
typedef struct PosxOy
{
	int X;
	int Y;
}PosxOy;
typedef enum
{
	USE_REGISTER_MODE = 0,
	USE_LOGIN_MODE = 1,
	USE_CHANGEPASSWORDMODE = 2
} OPERATION;
//Function Open And Check Data In Account 
void DataAccessProcessing(SDL_Window* MenuWindow, SDL_Renderer* DrawMenu, char UserName[], char Password[], char NewPassword[], OPERATION mode)
{
	// 
	FILE* accountdata;
	char Path[200];
	strcpy_s(Path, 200, "C:/Users/VuDucHuy/OneDrive - st.utc2.edu.vn/Máy tính/TheSeaOfStars/TheSeaOfStars/DataProcessing/LoginData/");
	strcat_s(Path, 200, UserName);
	strcat_s(Path, 200, ".bin");
	errno_t resultopenfile = fopen_s(&accountdata, Path, "rb");
	if (resultopenfile == 0)
	{
		if (mode == USE_REGISTER_MODE)
		{
			fclose(accountdata);
			NoticeWindowOption(1, 1, 300, 184, PNG, "AccountExistedObject", "Account Already Exists");
		}
		else if (mode == USE_LOGIN_MODE)
		{
			char ReadData[37] = {};
			char CheckData[37] = {};
			strcpy_s(CheckData, 37, UserName);
			strcat_s(CheckData, 37, Password);

			int checkread = fread_s(ReadData, sizeof(ReadData), sizeof(char), sizeof(CheckData), accountdata);
			if (checkread > 0)
			{
				printf("%s", ReadData);
				if (strcmp(ReadData, CheckData) == 0)
				{
					DisplayOption(MenuWindow, DrawMenu, 198, 300, 304, 43, "LoginSuccessfulObject", ENABLE_ADD_MENUTHEME, PNG);
				}
			}
			else if (checkread == 0)
			{
				printf("Can not read the Data from the file");
				printf("%d", checkread);
			}

		}
		else if (mode == USE_CHANGEPASSWORDMODE)
		{
			FILE* tempfile;
			errno_t checkopentempfile = fopen_s(&tempfile, "temp.bin", "wb");
			if (checkopentempfile == 0)
			{
				fwrite(&UserName, 1, sizeof(UserName), tempfile);
				fwrite(&NewPassword, 1, sizeof(NewPassword), tempfile);
				fclose(tempfile);
				fclose(accountdata);
				remove(Path);
				//rename("temp.bin", Path);
			}
		}
	}
	else
	{
		if (mode == USE_REGISTER_MODE)
		{
			resultopenfile = fopen_s(&accountdata, Path, "wb");
			if (resultopenfile == 0)
			{
				fwrite(&UserName, 1, strlen(UserName), accountdata);
				fwrite(&Password, 1, strlen(Password), accountdata);
				DisplayOption(MenuWindow, DrawMenu, 198, 300, 304, 43, "RegisterSuccessfulObject", ENABLE_ADD_MENUTHEME, PNG);
				fclose(accountdata);
			}
			else
			{
				printf("File cannot created");
			}
		}
		else if (mode == USE_LOGIN_MODE || mode == USE_CHANGEPASSWORDMODE)
		{
			NoticeWindowOption(1, 1, 300, 184, PNG, "AccountNotExistedObject", "Account Not Exists");
		}
	}

}