#pragma once
#include <SDL2/SDL.h>

class CustomColor : public SDL_Color
{
public:
    CustomColor();
    CustomColor(uint8_t r, uint8_t g, uint8_t b);
    CustomColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    CustomColor(uint32_t rgba);
    CustomColor(const CustomColor& other);

    void operator= (const CustomColor& other);

    static const CustomColor RED;
    static const CustomColor GREEN;
    static const CustomColor BLUE;
    static const CustomColor WHITE;
    static const CustomColor BLACK;
    static const CustomColor YELLOW;
    static const CustomColor CYAN;
    static const CustomColor MAGENTA;
    static const CustomColor GRAY;
    static const CustomColor ORANGE;
    static const CustomColor BROWN;
    static const CustomColor PINK;
    static const CustomColor PURPLE;
    static const CustomColor LIME;
    static const CustomColor TEAL;
    static const CustomColor NAVY;
};
