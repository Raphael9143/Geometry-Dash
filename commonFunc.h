#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define BLANK_TILE 0
#define SPIKE 7

//level
const int LEVEL_WIDTH = 1280*20;
const int LEVEL_HEIGHT = 720;
const int PIXEL_WIDTH = 40;
const int PIXEL_HEIGHT = 40;
const int GROUND = 600;

//screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int PLAYER_WIDTH = 40;
const int PLAYER_HEIGHT = 40;
const int LAYER_BACKGROUND = 5;

//player
const double JUMP_HEIGHT = 12;
const double NORMAL_SPEED = 4;
const double GRAVITY = 0.6;
const double MAX_GRAVITY = 10;
const int EX_FRAME = 25;

//tile
const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;

//Timer
const int SCREEN_FPS = 120;
const int SCREEN_TICK_PER_FRAME = 1000/SCREEN_FPS;

//Menu
const int EXITGAME = 0;
const int PLAYGAME = 1;
const int TUTORIAL = 2;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Surface* gScreenSurface = NULL;
static TTF_Font* gFont = NULL;
static Mix_Music* levelMusic = NULL;

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[LEVEL_HEIGHT/PIXEL_HEIGHT][LEVEL_WIDTH/PIXEL_WIDTH];
    char* file_name_;
};


#endif // COMMONFUNC_H
