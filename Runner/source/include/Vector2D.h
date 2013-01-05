#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{
    public:
        Vector2D();
        Vector2D(double x, double y);

        int lensq();

        Vector2D& operator=(const Vector2D &rhs);

        Vector2D operator+=(const Vector2D &other);
        Vector2D operator-=(const Vector2D &other);
        Vector2D operator*=(int num);

        Vector2D operator+(const Vector2D &other) const;
        Vector2D operator-(const Vector2D &other) const;
        Vector2D operator*(double num) const;
        int intx();
        int inty();


        double x, y;
    private:

};

#endif // VECTOR2D_H
