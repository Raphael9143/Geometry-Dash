#ifndef TIMER_H
#define TIMER_H

#include "commonFunc.h"
#include "LTexture.h"

class Timer
{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isPaused();
    bool isStarted();


private:
    Uint32 mSTicks;
    Uint32 mPTicks;

    bool mPaused;
    bool mStarted;

};
#endif // TIMER_H
