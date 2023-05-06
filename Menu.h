#ifndef MENU_H
#define MENU_H

#include "commonFunc.h"
#include "LTexture.h"

#define PLAY 0
#define EXIT 1

class Menu
{
public:
    Menu();
    ~Menu();
    bool checkMotion(const int& x, const int& y, const int& objX, const int& objY, const int& objW, const int& objH);

    int loadMenu(SDL_Renderer* ren);

    void loadMusic();
    void free();
    void loadTex(SDL_Renderer* ren);
    void loadPlaySound();
    void renderTutorial(SDL_Renderer* ren);

private:
    SDL_Rect mPlay;
    SDL_Rect mExit;
    SDL_Rect cPlay;
    SDL_Rect cExit;
    SDL_Rect mTutorial;
    SDL_Rect cTutorial;

    bool bPlay;
    bool bExit;
    bool bTutorial;

    bool play;

    Mix_Music* menuMusic = NULL;
    Mix_Music* playSound = NULL;
    LTexture mPlayButton, mExitButton, mainMenu, cPlayButton, cExitButton;
    LTexture mTutorialButton, cTutorialButton, tutorial;
};

#endif // MENU_H
