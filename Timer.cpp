#include "Timer.h"

Timer::Timer()
{
    mSTicks = 0;
    mPTicks = 0;

    mPaused = false;
    mStarted = false;
}

void Timer::start()
{
    mStarted = true;
    mPaused = false;

    mSTicks = SDL_GetTicks();
    mPTicks = 0;
}

void Timer::stop()
{
    mStarted = false;
    mPaused = true;

    mSTicks = 0;
    mPTicks = 0;
}

void Timer::pause()
{
    if (mStarted && !mPaused)
    {
        mPaused = true;

        mPTicks = SDL_GetTicks() - mSTicks;
        mSTicks = 0;
    }
}

void Timer::unpause()
{
    if (mStarted && mPaused)
    {
        mPaused = false;
        mSTicks = SDL_GetTicks() - mPTicks;
        mPTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    Uint32 time = 0;

    if(mStarted)
    {
        if (mPaused)
            time = mPTicks;
        else
            time = SDL_GetTicks() - mSTicks;
    }
    return time;
}

bool Timer::isStarted()
{
    return mStarted;
}

bool Timer::isPaused()
{
    return mPaused;
}
