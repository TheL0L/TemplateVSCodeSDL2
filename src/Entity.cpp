#include "Entity.hpp"

Entity::Entity()
    : _position(), _texture(nullptr), _textureRect()
{
}

Entity::Entity(SDL_Texture* texture, SDL_Rect& textureRect)
    : _position(), _texture(texture), _textureRect(textureRect)
{
}

Entity::Entity(const Entity& other)
    : _position(other._position), _texture(other._texture), _textureRect(other._textureRect)
{
}

SDL_Texture* Entity::getTexture()
{
    return _texture;
}

SDL_Rect& Entity::getTextureRect()
{
    return _textureRect;
}

Vector2D Entity::getPosition() const
{
    return _position;
}

void Entity::setPosition(Vector2D position)
{
    _position = position;
}

void Entity::move(Vector2D direction)
{
    _position += direction;
}

SDL_FRect Entity::getBoundingBox() const
{
    static SDL_FRect bound;
    bound.x = _position.x;
    bound.y = _position.y;
    bound.w = _textureRect.w;
    bound.h = _textureRect.h;

    return bound;
}
