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

static SDL_Window* MainGameWindow = NULL;
static SDL_Renderer* MainGameRenderer = NULL;
static SDL_Event event;

const int SCREEN_HEIGHT = 640; 
const int SCREEN_WIDTH = 1280;


Map CaptainDucOfficeVR; 

Character CaptainDuc;

MainCamera Camera1;

ObjectStructure House; 
ObjectStructure Flower;
ObjectStructure Fence;
ObjectStructure BackgroundCaptainOfficeVR;
ObjectStructure SwimmingPoor;

