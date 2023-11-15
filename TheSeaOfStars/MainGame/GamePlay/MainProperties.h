#pragma once

#include <windows.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "ObjectProcessing/Map.h"
#include "ObjectProcessing/Character.h"
#include "ObjectProcessing/Camera.h"
#include "ObjectProcessing/ObjectStructures.h"
#include <thread>
#include <mutex>
#include <condition_variable>

static SDL_Window* MainGameWindow = NULL;
static SDL_Renderer* MainGameRenderer = NULL;
static SDL_Event event;

const int SCREEN_HEIGHT = 640; 
const int SCREEN_WIDTH = 1280;

bool Quest1_Complete = false;
bool Quest2_Complete = false;
bool Quest3_Complete = false;


mutex QuestThreadAccessLock;
condition_variable SighNotice;

Map CaptainDucOfficeVR;
Map HibernateCabin;
Map CommanderRoom;
Map WarpEngineRoom;
Map Sentinus_Antarctic;
Map BaseInAntarctica;
Map IceCage;
Map MountainGroove;


Character CaptainDuc;

MainCamera Camera1;

ObjectStructure House; 
ObjectStructure Flower;
ObjectStructure Fence;
ObjectStructure BackgroundCaptainOfficeVR;
ObjectStructure SwimmingPoor;

