#ifndef PLAYER_H
#define PLAYER_H

#include "commonFunc.h"
#include "LTexture.h"
#include <windows.h>

class Player : public LTexture
{
public:

    Player();
    void move();

    void render(LTexture l_player, SDL_Renderer* ren);

    void handleEvent(SDL_Event event);

    void falling();

    void setCamera(SDL_Rect& camera);

    bool checkGround();

    SDL_Rect getBox();

    int getAttempt();

    void checkMap(Map &mapData);
    void dead();
    bool status();
    bool death();
    void loadMusic(Mix_Music* music);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
    void CenterEntityOnMap(Map& mapData);

    void close();
private:
    //offset
    SDL_Rect mBox;
    SDL_Rect mTile;
    //velocity
    double mVelX, mVelY;

    bool onGround;
    bool isJumping;
    bool isFalling;

    int map_x_;
    int map_y_;

    bool isDead;
    bool winning;

    int attempt = 0;

    Mix_Music* deadSound = NULL;

};

#endif // PLAYER_H
