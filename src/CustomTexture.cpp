#include <CustomTexture.hpp>

CustomTexture::CustomTexture(SDL_Texture* texture, const SDL_Rect& srcRect)
    : _texture(texture), _textureRect(srcRect)
{
}

CustomTexture::~CustomTexture()
{
    SDL_DestroyTexture(_texture);
}

SDL_Texture* CustomTexture::getTexture()
{
    return _texture;
}

SDL_Rect CustomTexture::getSrcRect() const
{
    return _textureRect;
}

