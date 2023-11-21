#pragma once
#include <SDL2/SDL.h>
#include "Vector2D.hpp"

class Entity
{
public:
    Entity();
    Entity(SDL_Texture* texture, SDL_Rect& textureRect);
    Entity(const Entity& other);
    ~Entity() = default;

    SDL_Texture* getTexture();
    SDL_Rect& getTextureRect();

    Vector2D getPosition() const;
    void setPosition(Vector2D position);

    SDL_FRect getBoundingBox() const;

    void move(Vector2D direction);

private:
    Vector2D _position;
    SDL_Texture* _texture;
    SDL_Rect _textureRect;
};
