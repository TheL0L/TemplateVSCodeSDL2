#pragma once
#include "CustomTexture.hpp"

class CustomAnimation : public CustomTexture
{
public:
    CustomAnimation(SDL_Texture* texture, const SDL_Rect& srcRect, uint16_t keyFrames);
    ~CustomAnimation() = default;

    SDL_Rect getSrcRect() const;
    SDL_Rect getNextFrameSrcRect();
    void resetAnimation();

private:
    SDL_Rect _frameRect;
    const uint16_t _keyFrames;
    uint16_t _currentFrame;
};
