#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "commonFunc.h"
#include "LTexture.h"
#include "Player.h"

#define MAX_TILE 17

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void loadMap(char* path);
    void loadTiles(SDL_Renderer* ren);
    void drawMap(SDL_Renderer* ren);

    Map getMap() const {return game_map_;}
    void setMap(Map& map_data) {game_map_ = map_data;}
private:
    Map game_map_;
    LTexture tile_map[MAX_TILE];
    SDL_Rect clip;
};

#endif

