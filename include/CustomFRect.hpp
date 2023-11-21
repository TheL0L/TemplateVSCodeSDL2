#pragma once
#include <SDL2/SDL.h>

class CustomFRect : public SDL_FRect
{
public:
    CustomFRect();
    CustomFRect(float x, float y, float w, float h);
};
