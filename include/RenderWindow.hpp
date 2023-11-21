#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Utils.hpp"
#include "Entity.hpp"
#include "Vector2D.hpp"

class RenderWindow
{
public:
    RenderWindow();
    RenderWindow(const char* title, int width, int height, bool vsync, int fpsCap = 60);
    ~RenderWindow();

    SDL_Texture* loadTexture(const char* filePath);

    void clear();

    void draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_FRect& dstRect);
    void draw(Entity& entity);

    void drawPoint(Vector2D point);
    void drawPoint(Vector2D point, const SDL_Color& color);

    void drawLine(Vector2D pointA, Vector2D pointB);
    void drawLine(Vector2D pointA, Vector2D pointB, const SDL_Color& color);

    void drawRect(SDL_FRect& rect);
    void drawRect(SDL_FRect& rect, const SDL_Color& color);

    void display();

    void setDrawColor(const SDL_Color& color);
    SDL_Color getDrawColor() const;

    void setTitle(const char* title);

    Vector2D getSize() const;

    int getFps() const;
    void setFpsCap(int cap);
    double getDeltaTime() const;
    void frameLimiter();

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    bool _vsync;

    int _fpsCap;
    int _fps;
    const uint32_t _clockFreq;
    uint32_t _frameTarget, _frameStart, _frameEnd;
    double _deltaTime;
};
