// Include Guard
#ifndef DCMATH_H
#define DCMATH_H

// Headers
#include <cmath>
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/Matrix3.h"

#define EPSILON 0.0000001f
#define	PI					3.1415926535897932384626433832795028841971693993751f	//!< PI
#define	HALFPI				1.57079632679489661923f									//!< 0.5 * PI
#define	TWOPI				6.28318530717958647692f									//!< 2.0 * PI
#define	INVPI				0.31830988618379067154f									//!< 1.0 / PI

// Temporary matrix4 class taken from http://www.dhpoware.com.
// TODO: rewrite

class dcMath
{
    public:
        static bool closeTof(float a, float b)
        {
            return fabsf((a - b) / ((b == 0.0f) ? 1.0f : b)) < EPSILON;
        }
        static float degreesToRadians(float d)
        {
            return (d * PI) / 180.0f;
        }
        static float radiansToDegrees(float r)
        {
            return (r * 180.0f) / PI;
        }
};

class Matrix4
{
    friend Vec3f operator*(const Vec3f& lhs, const Matrix4& rhs);
    friend Matrix4 operator*(float scalar, const Matrix4& rhs);

public:

    Matrix4() {}
    Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);
    ~Matrix4() {}

    float *operator[](int row);
    const float *operator[](int row) const;

    bool operator==(const Matrix4& rhs) const;
    bool operator!=(const Matrix4& rhs) const;

    Matrix4& operator+=(const Matrix4& rhs);
    Matrix4& operator-=(const Matrix4& rhs);
    Matrix4& operator*=(const Matrix4& rhs);
    Matrix4& operator*=(float scalar);
    Matrix4& operator/=(float scalar);

    Matrix4 operator+(const Matrix4& rhs) const;
    Matrix4 operator-(const Matrix4& rhs) const;
    Matrix4 operator*(const Matrix4& rhs) const;
    Matrix4 operator*(float scalar) const;
    Matrix4 operator/(float scalar) const;

    void identity();
    void rotate(const Vec3f& axis, float degrees);

private:
    float mtx[4][4];
};

inline Vec3f operator*(const Vec3f& lhs, const Matrix4& rhs)
{
    return Vec3f((lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
        (lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
        (lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
}

inline Matrix4 operator*(float scalar, const Matrix4& rhs)
{
    return rhs * scalar;
}

inline Matrix4::Matrix4(float m11, float m12, float m13, float m14,
                      float m21, float m22, float m23, float m24,
                      float m31, float m32, float m33, float m34,
                      float m41, float m42, float m43, float m44)
{
    mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13, mtx[0][3] = m14;
    mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23, mtx[1][3] = m24;
    mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33, mtx[2][3] = m34;
    mtx[3][0] = m41, mtx[3][1] = m42, mtx[3][2] = m43, mtx[3][3] = m44;
}

inline float *Matrix4::operator[](int row)
{
    return mtx[row];
}

inline const float *Matrix4::operator[](int row) const
{
    return mtx[row];
}

inline bool Matrix4::operator==(const Matrix4& rhs) const
{
    return dcMath::closeTof(mtx[0][0], rhs.mtx[0][0])
        && dcMath::closeTof(mtx[0][1], rhs.mtx[0][1])
        && dcMath::closeTof(mtx[0][2], rhs.mtx[0][2])
        && dcMath::closeTof(mtx[0][3], rhs.mtx[0][3])
        && dcMath::closeTof(mtx[1][0], rhs.mtx[1][0])
        && dcMath::closeTof(mtx[1][1], rhs.mtx[1][1])
        && dcMath::closeTof(mtx[1][2], rhs.mtx[1][2])
        && dcMath::closeTof(mtx[1][3], rhs.mtx[1][3])
        && dcMath::closeTof(mtx[2][0], rhs.mtx[2][0])
        && dcMath::closeTof(mtx[2][1], rhs.mtx[2][1])
        && dcMath::closeTof(mtx[2][2], rhs.mtx[2][2])
        && dcMath::closeTof(mtx[2][3], rhs.mtx[2][3])
        && dcMath::closeTof(mtx[3][0], rhs.mtx[3][0])
        && dcMath::closeTof(mtx[3][1], rhs.mtx[3][1])
        && dcMath::closeTof(mtx[3][2], rhs.mtx[3][2])
        && dcMath::closeTof(mtx[3][3], rhs.mtx[3][3]);
}

inline bool Matrix4::operator!=(const Matrix4& rhs) const
{
    return !(*this == rhs);
}

inline Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    mtx[0][0] += rhs.mtx[0][0], mtx[0][1] += rhs.mtx[0][1], mtx[0][2] += rhs.mtx[0][2], mtx[0][3] += rhs.mtx[0][3];
    mtx[1][0] += rhs.mtx[1][0], mtx[1][1] += rhs.mtx[1][1], mtx[1][2] += rhs.mtx[1][2], mtx[1][3] += rhs.mtx[1][3];
    mtx[2][0] += rhs.mtx[2][0], mtx[2][1] += rhs.mtx[2][1], mtx[2][2] += rhs.mtx[2][2], mtx[2][3] += rhs.mtx[2][3];
    mtx[3][0] += rhs.mtx[3][0], mtx[3][1] += rhs.mtx[3][1], mtx[3][2] += rhs.mtx[3][2], mtx[3][3] += rhs.mtx[3][3];
    return *this;
}

inline Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    mtx[0][0] -= rhs.mtx[0][0], mtx[0][1] -= rhs.mtx[0][1], mtx[0][2] -= rhs.mtx[0][2], mtx[0][3] -= rhs.mtx[0][3];
    mtx[1][0] -= rhs.mtx[1][0], mtx[1][1] -= rhs.mtx[1][1], mtx[1][2] -= rhs.mtx[1][2], mtx[1][3] -= rhs.mtx[1][3];
    mtx[2][0] -= rhs.mtx[2][0], mtx[2][1] -= rhs.mtx[2][1], mtx[2][2] -= rhs.mtx[2][2], mtx[2][3] -= rhs.mtx[2][3];
    mtx[3][0] -= rhs.mtx[3][0], mtx[3][1] -= rhs.mtx[3][1], mtx[3][2] -= rhs.mtx[3][2], mtx[3][3] -= rhs.mtx[3][3];
    return *this;
}

inline Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    Matrix4 tmp;

    // Row 1.
    tmp.mtx[0][0] = (mtx[0][0] * rhs.mtx[0][0]) + (mtx[0][1] * rhs.mtx[1][0]) + (mtx[0][2] * rhs.mtx[2][0]) + (mtx[0][3] * rhs.mtx[3][0]);
    tmp.mtx[0][1] = (mtx[0][0] * rhs.mtx[0][1]) + (mtx[0][1] * rhs.mtx[1][1]) + (mtx[0][2] * rhs.mtx[2][1]) + (mtx[0][3] * rhs.mtx[3][1]);
    tmp.mtx[0][2] = (mtx[0][0] * rhs.mtx[0][2]) + (mtx[0][1] * rhs.mtx[1][2]) + (mtx[0][2] * rhs.mtx[2][2]) + (mtx[0][3] * rhs.mtx[3][2]);
    tmp.mtx[0][3] = (mtx[0][0] * rhs.mtx[0][3]) + (mtx[0][1] * rhs.mtx[1][3]) + (mtx[0][2] * rhs.mtx[2][3]) + (mtx[0][3] * rhs.mtx[3][3]);

    // Row 2.
    tmp.mtx[1][0] = (mtx[1][0] * rhs.mtx[0][0]) + (mtx[1][1] * rhs.mtx[1][0]) + (mtx[1][2] * rhs.mtx[2][0]) + (mtx[1][3] * rhs.mtx[3][0]);
    tmp.mtx[1][1] = (mtx[1][0] * rhs.mtx[0][1]) + (mtx[1][1] * rhs.mtx[1][1]) + (mtx[1][2] * rhs.mtx[2][1]) + (mtx[1][3] * rhs.mtx[3][1]);
    tmp.mtx[1][2] = (mtx[1][0] * rhs.mtx[0][2]) + (mtx[1][1] * rhs.mtx[1][2]) + (mtx[1][2] * rhs.mtx[2][2]) + (mtx[1][3] * rhs.mtx[3][2]);
    tmp.mtx[1][3] = (mtx[1][0] * rhs.mtx[0][3]) + (mtx[1][1] * rhs.mtx[1][3]) + (mtx[1][2] * rhs.mtx[2][3]) + (mtx[1][3] * rhs.mtx[3][3]);

    // Row 3.
    tmp.mtx[2][0] = (mtx[2][0] * rhs.mtx[0][0]) + (mtx[2][1] * rhs.mtx[1][0]) + (mtx[2][2] * rhs.mtx[2][0]) + (mtx[2][3] * rhs.mtx[3][0]);
    tmp.mtx[2][1] = (mtx[2][0] * rhs.mtx[0][1]) + (mtx[2][1] * rhs.mtx[1][1]) + (mtx[2][2] * rhs.mtx[2][1]) + (mtx[2][3] * rhs.mtx[3][1]);
    tmp.mtx[2][2] = (mtx[2][0] * rhs.mtx[0][2]) + (mtx[2][1] * rhs.mtx[1][2]) + (mtx[2][2] * rhs.mtx[2][2]) + (mtx[2][3] * rhs.mtx[3][2]);
    tmp.mtx[2][3] = (mtx[2][0] * rhs.mtx[0][3]) + (mtx[2][1] * rhs.mtx[1][3]) + (mtx[2][2] * rhs.mtx[2][3]) + (mtx[2][3] * rhs.mtx[3][3]);

    // Row 4.
    tmp.mtx[3][0] = (mtx[3][0] * rhs.mtx[0][0]) + (mtx[3][1] * rhs.mtx[1][0]) + (mtx[3][2] * rhs.mtx[2][0]) + (mtx[3][3] * rhs.mtx[3][0]);
    tmp.mtx[3][1] = (mtx[3][0] * rhs.mtx[0][1]) + (mtx[3][1] * rhs.mtx[1][1]) + (mtx[3][2] * rhs.mtx[2][1]) + (mtx[3][3] * rhs.mtx[3][1]);
    tmp.mtx[3][2] = (mtx[3][0] * rhs.mtx[0][2]) + (mtx[3][1] * rhs.mtx[1][2]) + (mtx[3][2] * rhs.mtx[2][2]) + (mtx[3][3] * rhs.mtx[3][2]);
    tmp.mtx[3][3] = (mtx[3][0] * rhs.mtx[0][3]) + (mtx[3][1] * rhs.mtx[1][3]) + (mtx[3][2] * rhs.mtx[2][3]) + (mtx[3][3] * rhs.mtx[3][3]);

    *this = tmp;
    return *this;
}

inline Matrix4& Matrix4::operator*=(float scalar)
{
    mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar, mtx[0][3] *= scalar;
    mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar, mtx[1][3] *= scalar;
    mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar, mtx[2][3] *= scalar;
    mtx[3][0] *= scalar, mtx[3][1] *= scalar, mtx[3][2] *= scalar, mtx[3][3] *= scalar;
    return *this;
}

inline Matrix4& Matrix4::operator/=(float scalar)
{
    mtx[0][0] /= scalar, mtx[0][1] /= scalar, mtx[0][2] /= scalar, mtx[0][3] /= scalar;
    mtx[1][0] /= scalar, mtx[1][1] /= scalar, mtx[1][2] /= scalar, mtx[1][3] /= scalar;
    mtx[2][0] /= scalar, mtx[2][1] /= scalar, mtx[2][2] /= scalar, mtx[2][3] /= scalar;
    mtx[3][0] /= scalar, mtx[3][1] /= scalar, mtx[3][2] /= scalar, mtx[3][3] /= scalar;
    return *this;
}

inline Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
    Matrix4 tmp(*this);
    tmp += rhs;
    return tmp;
}

inline Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
    Matrix4 tmp(*this);
    tmp -= rhs;
    return tmp;
}

inline Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
    Matrix4 tmp(*this);
    tmp *= rhs;
    return tmp;
}

inline Matrix4 Matrix4::operator*(float scalar) const
{
    Matrix4 tmp(*this);
    tmp *= scalar;
    return tmp;
}

inline Matrix4 Matrix4::operator/(float scalar) const
{
    Matrix4 tmp(*this);
    tmp /= scalar;
    return tmp;
}

inline void Matrix4::identity()
{
    mtx[0][0] = 1.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f, mtx[0][3] = 0.0f;
    mtx[1][0] = 0.0f, mtx[1][1] = 1.0f, mtx[1][2] = 0.0f, mtx[1][3] = 0.0f;
    mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 1.0f, mtx[2][3] = 0.0f;
    mtx[3][0] = 0.0f, mtx[3][1] = 0.0f, mtx[3][2] = 0.0f, mtx[3][3] = 1.0f;
}

inline void Matrix4::rotate(const Vec3f& axis, float degrees)
{
    // Creates a rotation matrix about the specified axis.
    // The axis must be a unit vector. The angle must be in degrees.
    //
    // Let u = axis of rotation = (x, y, z)
    //
    //             | x^2(1 - c) + c  xy(1 - c) + zs  xz(1 - c) - ys   0 |
    // Ru(angle) = | yx(1 - c) - zs  y^2(1 - c) + c  yz(1 - c) + xs   0 |
    //             | zx(1 - c) - ys  zy(1 - c) - xs  z^2(1 - c) + c   0 |
    //             |      0              0                0           1 |
    //
    // where,
    //	c = cos(angle)
    //  s = sin(angle)

    degrees = dcMath::degreesToRadians(degrees);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float c = cosf(degrees);
    float s = sinf(degrees);

    mtx[0][0] = (x * x) * (1.0f - c) + c;
    mtx[0][1] = (x * y) * (1.0f - c) + (z * s);
    mtx[0][2] = (x * z) * (1.0f - c) - (y * s);
    mtx[0][3] = 0.0f;

    mtx[1][0] = (y * x) * (1.0f - c) - (z * s);
    mtx[1][1] = (y * y) * (1.0f - c) + c;
    mtx[1][2] = (y * z) * (1.0f - c) + (x * s);
    mtx[1][3] = 0.0f;

    mtx[2][0] = (z * x) * (1.0f - c) + (y * s);
    mtx[2][1] = (z * y) * (1.0f - c) - (x * s);
    mtx[2][2] = (z * z) * (1.0f - c) + c;
    mtx[2][3] = 0.0f;

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = 0.0f;
    mtx[3][3] = 1.0f;
}

#endif // DCMATH
