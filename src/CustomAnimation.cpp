#include "CustomAnimation.hpp"

CustomAnimation::CustomAnimation(SDL_Texture* texture, const SDL_Rect& srcRect, uint16_t keyFrames)
    : CustomTexture(texture, srcRect), _frameRect(srcRect), _keyFrames(keyFrames), _currentFrame(0)
{
}

SDL_Rect CustomAnimation::getSrcRect() const
{
    return _frameRect;
}

SDL_Rect CustomAnimation::getNextFrameSrcRect()
{
    _currentFrame = (_currentFrame + 1) % _keyFrames;

    _frameRect.x = _textureRect.x + _textureRect.w * _currentFrame;

    return _frameRect;
}

void CustomAnimation::resetAnimation()
{
    _currentFrame = 0;

    _frameRect.x = _textureRect.x;
}
