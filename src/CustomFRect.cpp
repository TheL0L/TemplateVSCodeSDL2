#include "CustomFRect.hpp"

CustomFRect::CustomFRect()
    : SDL_FRect()
{}

CustomFRect::CustomFRect(float x, float y, float w, float h)
    : SDL_FRect()
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}
