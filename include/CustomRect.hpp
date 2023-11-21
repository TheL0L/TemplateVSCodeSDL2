#pragma once
#include <SDL2/SDL.h>

class CustomRect : public SDL_Rect
{
public:
    CustomRect();
    CustomRect(int x, int y, int w, int h);
};
