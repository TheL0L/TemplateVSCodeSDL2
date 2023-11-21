#pragma once
#include <SDL2/SDL.h>

class CustomTexture
{
public:
    CustomTexture(SDL_Texture* texture, const SDL_Rect& srcRect);
    virtual ~CustomTexture();

    SDL_Texture* getTexture();
    virtual SDL_Rect getSrcRect() const;

protected:
    SDL_Texture* _texture;
    SDL_Rect _textureRect;
};
