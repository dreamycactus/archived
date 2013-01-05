#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include "MATH_Vec4.hpp"
#include "MATH_Vec3.hpp"
#include "MATH_Vec2.hpp"
#include "MATH_Matrix4x4.hpp"

namespace MATH
{

    inline Vec3f GETASDFASDDSFASDFVECTOR(const Vec3f& lhs, const Matrix4x4& rhs) // Rename later..
    {
        return Vec3f(   (lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
                        (lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
                        (lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
    }

    inline Vec4f GetVecMatProd4(const Vec4f& lhs, const Matrix4x4& rhs)
    {
        return Vec4f(   (lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]) + (lhs.w * rhs.mtx[3][0]),
                        (lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]) + (lhs.w * rhs.mtx[3][1]),
                        (lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]) + (lhs.w * rhs.mtx[3][2]),
                        (lhs.x * rhs.mtx[0][3]) + (lhs.y * rhs.mtx[1][3]) + (lhs.z * rhs.mtx[2][3]) + (lhs.w * rhs.mtx[3][3]));
    }

    inline Vec4f GetMatVecProd4(const Matrix4x4& lhs, const Vec4f& rhs)
    {
        return Vec4f(  (lhs.mtx[0][0] * rhs.x) + (lhs.mtx[0][1] * rhs.y) + (lhs.mtx[0][2] * rhs.z) + (lhs.mtx[0][3] * rhs.w),
                       (lhs.mtx[1][0] * rhs.x) + (lhs.mtx[1][1] * rhs.y) + (lhs.mtx[1][2] * rhs.z) + (lhs.mtx[1][3] * rhs.w),
                       (lhs.mtx[2][0] * rhs.x) + (lhs.mtx[2][1] * rhs.y) + (lhs.mtx[2][2] * rhs.z) + (lhs.mtx[2][3] * rhs.w),
                       (lhs.mtx[3][0] * rhs.x) + (lhs.mtx[3][1] * rhs.y) + (lhs.mtx[3][2] * rhs.z) + (lhs.mtx[3][3] * rhs.w));
    }

    inline void GetRotationMatrix4x4(Matrix4x4& mtx, const Vec3f& axis, float degrees)
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

        degrees = DegToRad(degrees); // Be careful, "degrees" is in radians after this line.

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

} // End namespace MATH

#endif // LINEARALGEBRA_H
