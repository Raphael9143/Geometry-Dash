#ifndef L_TEXTURE_H
#define L_TEXTURE_H
#include "commonFunc.h"

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path, SDL_Renderer* ren);

    void free();
    void render(int x, int y, SDL_Rect* clip, SDL_Renderer* ren);
    void renderTiles(int x, int y, SDL_Renderer* ren);

    int getWidth();
    int getHeight();

    SDL_Texture* getTexture() const {return mTexture;}
private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};


#endif // L_TEXTURE_H
