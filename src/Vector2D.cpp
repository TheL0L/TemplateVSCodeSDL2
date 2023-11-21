#include "Vector2D.hpp"

Vector2D::Vector2D()
    : x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y)
    : x(x), y(y)
{
}

Vector2D::Vector2D(const Vector2D& other)
    : x(other.x), y(other.y)
{
}

Vector2D Vector2D::operator+ (const Vector2D& other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator- (const Vector2D& other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator* (float scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/ (float scalar) const
{
    return this->operator* (1 / scalar);
}

bool Vector2D::operator== (const Vector2D& other) const
{
    return (x == other.x) && (y == other.y);
}

Vector2D& Vector2D::operator= (const Vector2D& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }

    return *this;
}

void Vector2D::operator+= (const Vector2D& other)
{
    x += other.x;
    y += other.y;
}

void Vector2D::operator-= (const Vector2D& other)
{
    x -= other.x;
    y -= other.y;
}

void Vector2D::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
}

void Vector2D::operator/= (float scalar)
{
    this->operator*= (1 / scalar);
}

float Vector2D::dotProduct(const Vector2D& other) const
{
    return x * other.x + y * other.y;
}
