#include "CustomRect.hpp"

CustomRect::CustomRect()
    : SDL_Rect()
{}

CustomRect::CustomRect(int x, int y, int w, int h)
    : SDL_Rect()
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}
