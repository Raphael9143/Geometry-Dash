#include "Player.h"

Player::Player()
{
    mBox.x = 0;
    mBox.y = GROUND - PLAYER_HEIGHT;
    mBox.w = PLAYER_WIDTH;
    mBox.h = PLAYER_HEIGHT;

    mVelX = 0;
    mVelY = 0;
    onGround = false;
    isDead = false;
    isFalling = false;
    map_x_ = 0;
    map_y_ = 0;
    winning = false;
}


void Player::handleEvent(SDL_Event event)
{
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_SPACE:
                if (checkGround())
                    isJumping = true;
                break;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0)
    {
        switch (event.button.button)
        {
        case SDL_BUTTON_LEFT:
            if (checkGround())
                isJumping = true;
            break;
        }
    }
}

void Player::falling()
{
    mVelY += GRAVITY;
    if (mVelY > MAX_GRAVITY)
        mVelY = MAX_GRAVITY;
}

void Player::move()
{
    falling();
    if (isJumping)
    {
        mVelY = -JUMP_HEIGHT;
        onGround = false;
        isJumping = false;
    }
    mVelX = NORMAL_SPEED;

}


void Player::CenterEntityOnMap(Map& mapData)
{
    mapData.start_x_ = mBox.x - (SCREEN_WIDTH/2);
    if (mapData.start_x_ < 0)
        mapData.start_x_ = 0;
    if (mapData.start_x_ + SCREEN_WIDTH > mapData.max_x_)
        mapData.start_x_ = mapData.max_x_ - SCREEN_WIDTH;
    mapData.start_y_ = mBox.y - (SCREEN_HEIGHT/2);
    if (mapData.start_y_ < 0)
        mapData.start_y_ = 0;
    if (mapData.start_y_ + SCREEN_HEIGHT > mapData.max_y_)
        mapData.start_y_ = mapData.max_y_ - SCREEN_HEIGHT;

}

void Player::checkMap(Map& mapData)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min = PLAYER_HEIGHT < PIXEL_HEIGHT ? PLAYER_HEIGHT : PIXEL_HEIGHT;

    x1 = (mBox.x + mVelX)/PIXEL_WIDTH;
    x2 = (mBox.x + mVelX + PLAYER_WIDTH - 1)/PIXEL_WIDTH;

    y1 = (mBox.y)/PLAYER_WIDTH;
    y2 = (mBox.y + height_min - 1)/PIXEL_HEIGHT;

    if (x1 >= 0 && x2 < LEVEL_WIDTH/PIXEL_WIDTH && y1>=0 && y2 <= LEVEL_HEIGHT/PIXEL_HEIGHT)
    {
        if (mVelX > 0)
        {
            if (mapData.tile[y1][x2] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
            {
                isDead = true;
            }
        }
        else if (mVelX < 0)
        {
            if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y2][x1] != BLANK_TILE)
            {
                mBox.x = (x1 + 1)*PIXEL_WIDTH;
                mVelX = 0;
            }
        }
    }


    int width_min = PLAYER_WIDTH < PIXEL_WIDTH ? PLAYER_WIDTH : PIXEL_WIDTH;

    x1 = (mBox.x)/PIXEL_WIDTH;
    x2 = (mBox.x + width_min)/PIXEL_WIDTH;

    y1 = (mBox.y + mVelY)/PLAYER_HEIGHT;
    y2 = (mBox.y + mVelY + PLAYER_HEIGHT - 1)/PLAYER_HEIGHT;
    if (x1 >=0 && x2 < LEVEL_WIDTH/PIXEL_WIDTH && y1 >= 0 && y2 < LEVEL_HEIGHT/PIXEL_HEIGHT)
    {
        if (mVelY > 0)
        {
            if (mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
            {
                mBox.y = y2*PIXEL_HEIGHT;
                mBox.y -= (PLAYER_HEIGHT + 1);
                mVelY = 0;
                onGround = true;
                if ((mapData.tile[y2][x1] == SPIKE && mapData.tile[y2][x2] == BLANK_TILE) || (mapData.tile[y2][x1] == BLANK_TILE && mapData.tile[y2][x2] == SPIKE) || (mapData.tile[y2][x1] == SPIKE == mapData.tile[y2][x2] == SPIKE))
                {
                    isDead = true;
                }
            }
        }
        else if (mVelY < 0)
        {
            if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE)
            {
                isDead = true;
            }
        }
    }

    mBox.x += mVelX;
    mBox.y += mVelY;


    if (mBox.y + PLAYER_HEIGHT > LEVEL_HEIGHT)
        mBox.y = 0;

    if (mBox.x + PLAYER_WIDTH > LEVEL_WIDTH)
        winning = true;


}

void Player::render(LTexture l_player, SDL_Renderer* ren)
{
    l_player.render(mBox.x - map_x_, mBox.y - map_y_, NULL, ren);
}

void Player::loadMusic(Mix_Music* music)
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, -1);
    }
    if (isDead)
    {
        Mix_HaltMusic();
    }
}

void Player::dead()
{
    deadSound = Mix_LoadMUS("assets/sound/DeadSound.mp3");
    if (isDead)
    {
        Mix_PlayMusic(deadSound, -1);
        Sleep(1000);
        Mix_HaltMusic();
        mBox.x = 0;
        attempt++;
        isDead = false;
    }
}

bool Player::death()
{
    return isDead;
}

int Player::getAttempt()
{
    return attempt;
}

bool Player::status()
{
    return winning;
}

bool Player::checkGround()
{
    return onGround;//mBox.y + PLAYER_HEIGHT == GROUND;
}

void Player::setCamera(SDL_Rect& camera)
{
    camera.x = (mBox.x + PLAYER_WIDTH/2) - SCREEN_WIDTH/2;
    camera.y = (mBox.y + PLAYER_HEIGHT/2) - SCREEN_HEIGHT/2;

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > LEVEL_WIDTH - camera.w)
        camera.x = LEVEL_WIDTH - camera.w;
    if (camera.y > LEVEL_HEIGHT - camera.h)
        camera.y = LEVEL_HEIGHT - camera.h;
}

SDL_Rect Player::getBox()
{
    return mBox;
}

void Player::close()
{
    Mix_FreeMusic(deadSound);
    deadSound = NULL;


}
