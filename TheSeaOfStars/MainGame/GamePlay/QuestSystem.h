#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "MainProperties.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "PeripheralsDataProcessing.h"

enum QuestType
{
	MAIN_QUEST = 1,
	SIDE_QUEST = 2
};


class QuestHandle
{
private:
	string QuestName;
	QuestType Type;
	bool QuestCompleteStatus;

public:
	QuestHandle(string questname, QuestType type, bool questcompletestatus)
		: QuestName(questname), Type(type), QuestCompleteStatus(questcompletestatus) {}
	string GetName() { return QuestName; }
	bool GetStatus() { return QuestCompleteStatus; }
};

class QuestList
{
	private:
		vector<QuestHandle> ListQuest;
		ObjectStructure QuestBoard;
	public:
		QuestList(SDL_Renderer* GameRenderer) 
		{
			QuestBoard.Load_IMG("TheSeaOfStars/Design Documentation/Design Idea/QuestBoard.png", GameRenderer);
			QuestBoard.Initialized_IMG();
		}

		void CreateQuest(string questname, QuestType type, bool questcompletestatus)
		{
			QuestHandle QuestAdd(questname, type, questcompletestatus);
			ListQuest.push_back(QuestAdd);
		}

		void QuestNoticeBoard(SDL_Renderer* GameRenderer, SDL_Window* MenuWindow, Map Mapdata, Character CharacterInfo)
		{
			QuestBoard.RenderPicture(GameRenderer, 193, 127, 1);
			TTF_Init();
			SDL_Event event = {};
			SDL_Surface* TextSurface = NULL;
			SDL_Texture* TextTexture = NULL;
			SDL_Rect TextRect = {}, InputBoxRect = {};
			TTF_Font* TextFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 28);
			SDL_Color TextColor = { 79, 123, 255 };
			TextRect.h = 20;
			TextRect.y = 238;
			int MousePosX = 0, MousePosY = 0;

			for (int i = 0; i < ListQuest.size(); i++)
			{
				if (!ListQuest[i].GetStatus())
				{
					TextRect.x = 172;
					TextRect.w = 11 * ListQuest[i].GetName().length();
					TextSurface = TTF_RenderText_Solid(TextFont, ListQuest[i].GetName().c_str(), TextColor);
					if (TextSurface == NULL)
						printf("TextSurface run wrong! Please test again!");
					TextTexture = SDL_CreateTextureFromSurface(MainGameRenderer, TextSurface);
					if (TextTexture == NULL)
						printf("TextTexture run wrong! Please test again!");
					SDL_RenderCopy(GameRenderer, TextTexture, NULL, &TextRect);
					TextRect.y += 20;
				}
			}
			SDL_RenderPresent(MainGameRenderer);
			while (true)
			{
				if (!MouseEventProcessing(MousePosX, MousePosY, MenuWindow, MainGameRenderer, event))
					cout << "Error in Mouse Event Processing" << endl;
				if (MousePosX >= 193 && MousePosX <= 1087 && MousePosY >= 127 && MousePosY <= 512)
					continue;
				else
					break;
				cout << "Chay den day roi nha" << endl;
			}
			SDL_RenderCopy(GameRenderer, Mapdata.GetTexture(), QuestBoard.GetPositionRenderInScreen(), QuestBoard.GetPositionRenderInScreen());
			SDL_RenderCopy(GameRenderer,
						   CharacterInfo.GetStatusInRealTime().AnimationTexture,
						  CharacterInfo.GetStatusInRealTime().SourcePos,
						  CharacterInfo.GetStatusInRealTime().DesinationPos);
			SDL_RenderPresent(GameRenderer);
		}
};

void Quest1_Accepted()
{
	int a = 6;
}
void QuestSystemCenterProcessing(SDL_Renderer* GameRenderer, SDL_Window* MenuWindow, Map Mapdata, Character CharacterRTInfo)
{
	QuestList ListQuestInGame();
	ObjectStructure QuestIcon;
	int MousePosX, MousePosY;
	SDL_Event event;
	unique_lock<mutex> lock(QuestThreadAccessLock);
	SighNotice.wait(lock, [] {return Quest1_Complete;});
	
	QuestIcon.Load_IMG("TheSeaOfStars/Design Documentation/Design Idea/QuestBoard.png", GameRenderer);
	QuestIcon.Initialized_IMG();
	QuestIcon.RenderPicture(GameRenderer, 10, 200, 1);
	ListQuestInGame().CreateQuest("Quest 1 : Repair The Ship", MAIN_QUEST, false);

	while (true)
	{
		if (!MouseEventProcessing(MousePosX, MousePosY, MenuWindow, MainGameRenderer, event))
			cout << "Error in Mouse Event Processing" << endl;
		if (MousePosX >= 10 && MousePosX <= 34 && MousePosY >= 200 && MousePosY <= 222)
			ListQuestInGame().QuestNoticeBoard(GameRenderer, MenuWindow, Mapdata, CharacterRTInfo);
	}
}