#pragma once

#include <windows.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "ObjectProcessing/Layer.h"
#include "ObjectProcessing/Map.h"

static SDL_Window* MainGameWindow = NULL;
static SDL_Renderer* MainGameRenderer = NULL;
static SDL_Event event;

const int SCREEN_HEIGHT = 640; 
const int SCREEN_WIDTH = 1280;

Layer Background;
Layer StaticObject;
Layer DynamicObject;

Map CaptainDucOfficeVR; 
