#include "CustomColor.hpp"

const CustomColor CustomColor::RED{ 255, 0, 0 };
const CustomColor CustomColor::GREEN{ 0, 255, 0 };
const CustomColor CustomColor::BLUE{ 0, 0, 255 };
const CustomColor CustomColor::WHITE{ 255, 255, 255 };
const CustomColor CustomColor::BLACK{ 0, 0, 0 };
const CustomColor CustomColor::YELLOW{ 255, 255, 0 };
const CustomColor CustomColor::CYAN{ 0, 255, 255 };
const CustomColor CustomColor::MAGENTA{ 255, 0, 255 };
const CustomColor CustomColor::GRAY{ 128, 128, 128 };
const CustomColor CustomColor::ORANGE{ 255, 165, 0 };
const CustomColor CustomColor::BROWN{ 165, 42, 42 };
const CustomColor CustomColor::PINK{ 255, 192, 203 };
const CustomColor CustomColor::PURPLE{ 128, 0, 128 };
const CustomColor CustomColor::LIME{ 0, 255, 0 };
const CustomColor CustomColor::TEAL{ 0, 128, 128 };
const CustomColor CustomColor::NAVY{ 0, 0, 128 };

CustomColor::CustomColor()
    : SDL_Color()
{
    this->r = this->g = this->b = this->a = 0;
}

CustomColor::CustomColor(uint8_t r, uint8_t g, uint8_t b)
    : SDL_Color()
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 0xFF;
}

CustomColor::CustomColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : SDL_Color()
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

CustomColor::CustomColor(uint32_t rgba)
    : SDL_Color()
{
    this->r = (rgba >> 24) & 0xFF;
    this->g = (rgba >> 16) & 0xFF;
    this->b = (rgba >> 8) & 0xFF;
    this->a = rgba & 0xFF;
}

CustomColor::CustomColor(const CustomColor& other)
    : SDL_Color()
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
}

void CustomColor::operator= (const CustomColor& other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
}
