#include "Menu.h"

Menu::Menu()
{
    mPlay.x = 0;
    mPlay.y = 0;

    cPlay.x = 0;
    cPlay.y = 0;

    mExit.x = 0;
    mExit.y = 0;

    cExit.x = 0;
    cExit.y = 0;

    bPlay = false;
    bExit = false;

    play = false;
}

Menu::~Menu()
{
    free();
}



bool Menu::checkMotion(const int& x, const int& y, const int& objX, const int& objY, const int& objW, const int& objH)
{
    if (x >= objX && x <= objX + objW &&
        y >= objY && y <= objY + objH)
    {
        return true;
    }
    return false;
}

void Menu::loadTex(SDL_Renderer* ren)
{
    mainMenu.loadFromFile("assets/Menu/MainMenu.jpg", ren);
    mPlayButton.loadFromFile("assets/Menu/PlayButton.png", ren);
    mExitButton.loadFromFile("assets/Menu/X.png", ren);
    cPlayButton.loadFromFile("assets/Menu/Play.png", ren);
    cExitButton.loadFromFile("assets/Menu/afterX.png", ren);
    mTutorialButton.loadFromFile("assets/Menu/toturial.png", ren);
    cTutorialButton.loadFromFile("assets/Menu/toturial (1).png", ren);
    tutorial.loadFromFile("assets/Menu/insideTu.png", ren);
}

int Menu::loadMenu(SDL_Renderer* ren)
{
    loadMusic();
    loadTex(ren);

    SDL_Event mEvent;

    mPlay.x = 810;
    mPlay.y = 540;

    cPlay.x = 807;
    cPlay.y = 537;

    mTutorial.x = SCREEN_WIDTH - mTutorialButton.getWidth();
    mTutorial.y = 0;

    cTutorial.x = SCREEN_WIDTH - cTutorialButton.getWidth();
    cTutorial.y = 0;

    mExit.x = 0;
    mExit.y = 0;

    cExit.x = 0;
    cExit.y = 0;

    int xMot, yMot;
    while (true)
    {
        mainMenu.render(0, 0, NULL, ren);
        if (!bPlay)
            mPlayButton.render(mPlay.x, mPlay.y, NULL, ren);
        else
            cPlayButton.render(cPlay.x, cPlay.y, NULL, ren);

        if (!bTutorial)
            mTutorialButton.render(mTutorial.x, mTutorial.y, NULL, ren);
        else
            cTutorialButton.render(cTutorial.x, cTutorial.y, NULL, ren);

        if(!bExit)
            mExitButton.render(mExit.x, mExit.y, NULL, ren);
        else
            cExitButton.render(cExit.x, cExit.y, NULL, ren);

        while (SDL_PollEvent(&mEvent))
        {
            switch (mEvent.type)
                {
                case SDL_QUIT:
                    return EXITGAME;
                case SDL_MOUSEMOTION:
                {
                    xMot = mEvent.motion.x;
                    yMot = mEvent.motion.y;

                    if (checkMotion(xMot, yMot, mPlay.x, mPlay.y, mPlayButton.getWidth(), mPlayButton.getHeight()))
                        bPlay = true;
                    else
                        bPlay = false;

                    if(checkMotion(xMot, yMot, mTutorial.x, mTutorial.y, mTutorialButton.getWidth(), mTutorialButton.getHeight()))
                        bTutorial = true;
                    else
                        bTutorial = false;

                    if (checkMotion(xMot, yMot, mExit.x, mExit.y, mExitButton.getWidth(), mExitButton.getHeight()))
                        bExit = true;
                    else
                        bExit = false;

                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    xMot = mEvent.button.x;
                    yMot = mEvent.button.y;
                    if (checkMotion(xMot, yMot, cPlay.x, cPlay.y, cPlayButton.getWidth(), cPlayButton.getHeight()))
                    {
                        play = true;
                        return PLAYGAME;
                    }
                    else if (checkMotion(xMot, yMot, cTutorial.x, cTutorial.y, cTutorialButton.getWidth(), cTutorialButton.getHeight()))
                        return TUTORIAL;

                    else if (checkMotion(xMot, yMot, cExit.x, cExit.y, cExitButton.getWidth(), cExitButton.getHeight()))
                        return EXITGAME;
                    break;
                }
                default:
                    break;
                }
        }
        SDL_RenderPresent(ren);
    }
    return EXITGAME;
}

void Menu::renderTutorial(SDL_Renderer* ren)
{
    tutorial.render(0, 0, NULL, ren);
    SDL_RenderPresent(ren);
}

void Menu::loadMusic()
{
    menuMusic = Mix_LoadMUS("assets/sound/Menu.mp3");
    Mix_PlayMusic(menuMusic, -1);
}

void Menu::loadPlaySound()
{
    playSound = Mix_LoadMUS("assets/sound/PlaySound.mp3");
    Mix_PlayMusic(playSound, -1);
}

void Menu::free()
{
    mPlayButton.free();
    mExitButton.free();
    cPlayButton.free();
    cExitButton.free();
    mainMenu.free();
    mTutorialButton.free();
    cTutorialButton.free();
    tutorial.free();

    Mix_FreeMusic(menuMusic);
    menuMusic = NULL;

    Mix_FreeMusic(playSound);
    playSound = NULL;

}
