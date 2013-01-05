#include "../include/Vector2D.h"

Vector2D::Vector2D()
{
    //ctor
}

Vector2D::Vector2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

int Vector2D::lensq()
{
    return (this->x * this->x + this->y * this->y);
}

Vector2D& Vector2D::operator=(const Vector2D &rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

Vector2D Vector2D::operator+=(const Vector2D &other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D Vector2D::operator-=(const Vector2D &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector2D Vector2D::operator*=(int num)
{
    this->x *= num;
    this->y *= num;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D &other) const
{
    Vector2D result = *this;
    result += other;
    return result;
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    Vector2D result = *this;
    result -= other;
    return result;
}

Vector2D Vector2D::operator*(double num) const
{
    Vector2D result = *this;
    result *= num;
    return result;
}

int Vector2D::intx()
{
    return int(x + 0.5);
}

int Vector2D::inty()
{
    return int(y + 0.5);
}
