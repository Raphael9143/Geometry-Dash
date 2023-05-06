#include "GameMap.h"

void GameMap::loadMap(char* path)
{
    FILE* fp = NULL;
    fopen_s(&fp, path, "rb");
    if (fp == NULL)
        return;

    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;

    for (int i=0; i<LEVEL_HEIGHT/PIXEL_HEIGHT; i++)
    {
        for (int j=0; j<LEVEL_WIDTH/PIXEL_WIDTH; j++)
        {
            fscanf(fp, "%d", &game_map_.tile[i][j]);
            int val = game_map_.tile[i][j];
            if (val > 0)
            {
                if (j > game_map_.max_x_)
                    game_map_.max_x_ = j;
                if (i > game_map_.max_y_)
                    game_map_.max_y_ = i;
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ + 1)*PIXEL_WIDTH;
    game_map_.max_y_ = (game_map_.max_y_ + 1)*PIXEL_HEIGHT;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = path;
    fclose(fp);
}

void GameMap::loadTiles(SDL_Renderer* ren)
{
    char file_img[30];
    FILE* fp = NULL;

    for (int i=0; i<MAX_TILE; i++)
    {
        sprintf_s(file_img, "map/%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if (fp == NULL)
            continue;
        fclose(fp);
        tile_map[i].loadFromFile(file_img, ren);
    }
}

void GameMap::drawMap(SDL_Renderer* ren)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_/TILE_WIDTH;
    x1 = (game_map_.start_x_ % TILE_WIDTH)*(-1);
    x2 = x1 + SCREEN_WIDTH  + (x1 == 0 ? 0 : TILE_WIDTH);

    map_y = game_map_.start_y_/TILE_HEIGHT;
    y1 = (game_map_.start_y_ % TILE_WIDTH)*(-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_HEIGHT);

    for (int i=y1; i<y2; i+=TILE_HEIGHT)
    {
        map_x = game_map_.start_x_/TILE_WIDTH;
        for (int j=x1; j<x2; j+=TILE_WIDTH)
        {
            int val = game_map_.tile[map_y][map_x];
            if (val > 0)
            {
                tile_map[val].renderTiles(j, i, ren);
            }
            map_x++;
        }
        map_y++;
    }
}
