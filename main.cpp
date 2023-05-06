#include "commonFunc.h"
#include "LTexture.h"
#include "Player.h"
#include <windows.h>
#include "GameMap.h"
#include "Timer.h"
#include "Menu.h"

bool init();
bool initBG();
void close();
bool loadMedia();

LTexture playerTex;
LTexture layer[5];
GameMap PressStart;
LTexture background;
Menu menu;
Player player;

int main(int argc, char** argv)
{
    srand(time(0));
    if (!init())
        std::cout << "Can't initialize. SDL Error: " << SDL_GetError() << std::endl;
    if (!initBG())//gRenderer))
        std::cout << "Can't initialize background. SDL Error: " << SDL_GetError() << std::endl;
    SDL_Event gEvent;
    bool quit = false;

    float scrolling[5];

    PressStart.loadMap("map/PressStart.map");
    PressStart.loadTiles(gRenderer);

    Map mainMap = PressStart.getMap();

    Timer fpsTimer;
    Timer capTimer;

    int countedFrames = 0;
    fpsTimer.start();

    int openMenu = menu.loadMenu(gRenderer);
    if (openMenu == TUTORIAL)
    {
        menu.renderTutorial(gRenderer);
        SDL_Delay(5000);
        openMenu = menu.loadMenu(gRenderer);
    }
    if (openMenu == EXITGAME)
        quit = true;
    else if (openMenu == PLAYGAME)
    {
        Mix_HaltMusic();
        menu.loadPlaySound();
        SDL_Delay(1000);
    }
    Mix_HaltMusic();

    while (!quit)
    {
        player.loadMusic(levelMusic);
        capTimer.start();
        while (SDL_PollEvent(&gEvent))
        {
            if (gEvent.type == SDL_QUIT)
            {
                std::cout << "You've quited the game!" << std::endl;
                quit = true;
            }
            if (gEvent.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
            player.handleEvent(gEvent);
        }
        float avgFPS = countedFrames / (fpsTimer.getTicks()/1000.f);
        if (avgFPS > 2000000)
            avgFPS = 0;

        loadMedia();
        player.move();

        for (int i=0; i<5; i++)
        {
            if (i == 3)
                scrolling[i] = 0;
            else
                scrolling[i] -= 0.1*i;
            if (scrolling[i] < -layer[i].getWidth())
                scrolling[i] = 0;
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(gRenderer);

        for (int i=0; i<5; i++)
        {
            layer[i].render(scrolling[i], 0, NULL, gRenderer);
            layer[i].render(scrolling[i] + layer[i].getWidth(), 0, NULL, gRenderer);
        }

        background.render(0, GROUND, NULL, gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

        player.CenterEntityOnMap(mainMap);
        player.SetMapXY(mainMap.start_x_, mainMap.start_y_);
        player.dead();
        player.checkMap(mainMap);
        if(!player.death())
            player.render(playerTex, gRenderer);
        PressStart.setMap(mainMap);
        PressStart.drawMap(gRenderer);
        SDL_RenderPresent(gRenderer);

        ++countedFrames;
        int frameTicks = capTimer.getTicks();
        if(frameTicks < SCREEN_TICK_PER_FRAME)
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
        if (player.status())
        {
            std::cout << "You've won the game!" << std::endl;
            quit = true;
        }
    }

    std::cout << "Attempt: " << player.getAttempt() << std::endl;

    close();
    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;
    else
    {
        gWindow = SDL_CreateWindow("Geometry Dash", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
            return false;

        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == NULL)
            return false;

        gScreenSurface = SDL_GetWindowSurface(gWindow);

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            return false;
    }
    return true;
}

bool initBG()
{
    bool success = true;
    if (!background.loadFromFile("assets/background/ground_.png", gRenderer))
        success = false;
    if (!layer[0].loadFromFile("assets/background/1/Day/1.png", gRenderer))
        success = false;
    if (!layer[1].loadFromFile("assets/background/1/Day/2.png", gRenderer))
        success = false;
    if (!layer[2].loadFromFile("assets/background/1/Day/3.png", gRenderer))
        success = false;
    if (!layer[3].loadFromFile("assets/background/1/Day/4.png", gRenderer))
        success = false;
    if (!layer[4].loadFromFile("assets/background/1/Day/5.png", gRenderer))
        success = false;
    return success;

}


bool loadMedia()
{
    bool success = true;
    if (!playerTex.loadFromFile("assets/player/player.png", gRenderer))
        success = false;
    gFont = TTF_OpenFont("assets/font/Consolas.ttf", 28);
    if (gFont == NULL)
        success = false;
    levelMusic = Mix_LoadMUS("assets/sound/PressStart.mp3");
    if (levelMusic == NULL)
        success = false;
    return success;
}


void close()
{
    for (int i=0; i<5; i++)
    {
        layer[i].free();
    }
    menu.free();
    player.close();
    playerTex.free();

    Mix_FreeMusic(levelMusic);
    levelMusic = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
