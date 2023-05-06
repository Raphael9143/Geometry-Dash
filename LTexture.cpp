#include "LTexture.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* ren)
{
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load (path.c_str());

    if (loadedSurface == NULL)
        std::cout << "Failed to load surface. SDL Error: " << SDL_GetError() << std::endl;
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);

        if (newTexture == NULL)
            std::cout << "Failed to create texture. SDL Error: " << SDL_GetError() << std::endl;
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);

    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render(int x, int y, SDL_Rect* clip, SDL_Renderer* ren)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        renderQuad.w = mWidth;
        renderQuad.h = mHeight;
    }

    SDL_RenderCopy(ren, mTexture, clip, &renderQuad);
}

void LTexture::renderTiles(int x, int y, SDL_Renderer* ren)
{
    SDL_Rect renderQuad = {x, y, PIXEL_WIDTH, PIXEL_HEIGHT};
    SDL_RenderCopy(ren, mTexture, NULL, &renderQuad);
}

int LTexture::getHeight()
{
    return mHeight;
}

int LTexture::getWidth()
{
    return mWidth;
}
