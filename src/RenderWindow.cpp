#include "RenderWindow.hpp"
#include <iostream>

RenderWindow::RenderWindow()
    : _window(nullptr), _renderer(nullptr), _vsync(true), _fpsCap(60),
    _clockFreq(SDL_GetPerformanceFrequency()), _deltaTime(0)
{
    const uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    const uint32_t rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    _window = SDL_CreateWindow(
        "SDL2 window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        windowFlags
    );

    if (_window == nullptr)
    {
        std::cerr << "SDL window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    _renderer = SDL_CreateRenderer(_window, -1, rendererFlags);

    if (_renderer == nullptr)
    {
        std::cerr << "SDL renderer failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    setFpsCap(_fpsCap);
    _frameStart = SDL_GetPerformanceCounter();
}

RenderWindow::RenderWindow(const char* title, int width, int height, bool vsync, int fpsCap)
    : _window(nullptr), _renderer(nullptr), _vsync(vsync), _fpsCap(fpsCap),
    _clockFreq(SDL_GetPerformanceFrequency()), _deltaTime(0)
{
    const uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    const uint32_t rendererFlags = SDL_RENDERER_ACCELERATED;

    _window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        windowFlags
    );

    if (_window == nullptr)
    {
        std::cerr << "SDL window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    _renderer = SDL_CreateRenderer(_window, -1, _vsync ? SDL_RENDERER_PRESENTVSYNC | rendererFlags : rendererFlags);

    if (_renderer == nullptr)
    {
        std::cerr << "SDL renderer failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    setFpsCap(_fpsCap);
    _frameStart = SDL_GetPerformanceCounter();
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(_renderer, filePath);

    if (texture == nullptr)
    {
        std::cerr << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(_renderer);
}

void RenderWindow::draw(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_FRect& dstRect)
{
    SDL_RenderCopyF(_renderer, texture, &srcRect, &dstRect);
}

void RenderWindow::draw(Entity& entity)
{
    SDL_FRect dstRect;
    dstRect.x = entity.getPosition().x;
    dstRect.y = entity.getPosition().y;
    dstRect.w = entity.getTextureRect().w;
    dstRect.h = entity.getTextureRect().h;

    SDL_RenderCopyF(_renderer, entity.getTexture(), &entity.getTextureRect(), &dstRect);
}

void RenderWindow::drawPoint(Vector2D point)
{
    SDL_RenderDrawPointF(_renderer, point.x, point.y);
}

void RenderWindow::drawPoint(Vector2D point, const SDL_Color& color)
{
    SDL_Color oldColor = getDrawColor();
    setDrawColor(color);
    SDL_RenderDrawPointF(_renderer, point.x, point.y);
    setDrawColor(oldColor);
}

void RenderWindow::drawLine(Vector2D pointA, Vector2D pointB)
{
    SDL_RenderDrawLineF(_renderer, pointA.x, pointA.y, pointB.x, pointB.y);
}

void RenderWindow::drawLine(Vector2D pointA, Vector2D pointB, const SDL_Color& color)
{
    SDL_Color oldColor = getDrawColor();
    setDrawColor(color);
    SDL_RenderDrawLineF(_renderer, pointA.x, pointA.y, pointB.x, pointB.y);
    setDrawColor(oldColor);
}

void RenderWindow::drawRect(SDL_FRect& rect)
{
    SDL_RenderDrawRectF(_renderer, &rect);
}

void RenderWindow::drawRect(SDL_FRect& rect, const SDL_Color& color)
{
    SDL_Color oldColor = getDrawColor();
    setDrawColor(color);
    SDL_RenderDrawRectF(_renderer, &rect);
    setDrawColor(oldColor);
}

void RenderWindow::display()
{
    SDL_RenderPresent(_renderer);
}

void RenderWindow::setDrawColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

SDL_Color RenderWindow::getDrawColor() const
{
    SDL_Color color;
    SDL_GetRenderDrawColor(_renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

void RenderWindow::setTitle(const char* title)
{
    SDL_SetWindowTitle(_window, title);
}

Vector2D RenderWindow::getSize() const
{
    int width, height;
    SDL_GetWindowSizeInPixels(_window, &width, &height);
    return Vector2D(width, height);
}

int RenderWindow::getFps() const
{
    return _fps;
}

void RenderWindow::setFpsCap(int cap)
{
    if (cap > 0)
    {
        _fpsCap = cap;
        _frameTarget = _clockFreq / _fpsCap;
    }
}

double RenderWindow::getDeltaTime() const
{
    return _deltaTime;
}

void RenderWindow::frameLimiter()
{
    static uint32_t frameElapsed, frameGap;
    _frameEnd = SDL_GetPerformanceCounter();
    frameElapsed = _frameEnd - _frameStart;
    frameGap = _frameTarget - frameElapsed;

    if (frameElapsed < _frameTarget)
    {
        SDL_Delay(frameGap * 0.0001);
        frameElapsed = _frameTarget;
    }

    _deltaTime = frameElapsed / (double)_clockFreq;
    _fps = _clockFreq / frameElapsed;

    _frameStart = _frameEnd;
}
