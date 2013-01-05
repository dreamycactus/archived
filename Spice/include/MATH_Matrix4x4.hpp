#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "MATH_MathHelper.hpp"

namespace MATH
{

    class Matrix4x4
    {
        friend Matrix4x4 operator*(float scalar, const Matrix4x4& rhs);

    public:

        Matrix4x4() {}
        Matrix4x4(  float m11, float m12, float m13, float m14,
                    float m21, float m22, float m23, float m24,
                    float m31, float m32, float m33, float m34,
                    float m41, float m42, float m43, float m44);
        ~Matrix4x4() {}

        float *operator[](int row);
        const float *operator[](int row) const;

        bool operator==(const Matrix4x4& rhs) const;
        bool operator!=(const Matrix4x4& rhs) const;

        Matrix4x4& operator+=(const Matrix4x4& rhs);
        Matrix4x4& operator-=(const Matrix4x4& rhs);
        Matrix4x4& operator*=(const Matrix4x4& rhs);
        Matrix4x4& operator*=(float scalar);
        Matrix4x4& operator/=(float scalar);

        Matrix4x4 operator+(const Matrix4x4& rhs) const;
        Matrix4x4 operator-(const Matrix4x4& rhs) const;
        Matrix4x4 operator*(const Matrix4x4& rhs) const;
        Matrix4x4 operator*(float scalar) const;
        Matrix4x4 operator/(float scalar) const;

        void Identity();

        float mtx[4][4];
    };

    inline Matrix4x4 operator*(float scalar, const Matrix4x4& rhs)
    {
        return rhs * scalar;
    }

    inline Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
                            float m21, float m22, float m23, float m24,
                            float m31, float m32, float m33, float m34,
                            float m41, float m42, float m43, float m44)
    {
        mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13, mtx[0][3] = m14;
        mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23, mtx[1][3] = m24;
        mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33, mtx[2][3] = m34;
        mtx[3][0] = m41, mtx[3][1] = m42, mtx[3][2] = m43, mtx[3][3] = m44;
    }

    inline float *Matrix4x4::operator[](int row)
    {
        return mtx[row];
    }

    inline const float *Matrix4x4::operator[](int row) const
    {
        return mtx[row];
    }

    inline bool Matrix4x4::operator==(const Matrix4x4& rhs) const
    {
        return CloseTof(mtx[0][0], rhs.mtx[0][0])
            && CloseTof(mtx[0][1], rhs.mtx[0][1])
            && CloseTof(mtx[0][2], rhs.mtx[0][2])
            && CloseTof(mtx[0][3], rhs.mtx[0][3])
            && CloseTof(mtx[1][0], rhs.mtx[1][0])
            && CloseTof(mtx[1][1], rhs.mtx[1][1])
            && CloseTof(mtx[1][2], rhs.mtx[1][2])
            && CloseTof(mtx[1][3], rhs.mtx[1][3])
            && CloseTof(mtx[2][0], rhs.mtx[2][0])
            && CloseTof(mtx[2][1], rhs.mtx[2][1])
            && CloseTof(mtx[2][2], rhs.mtx[2][2])
            && CloseTof(mtx[2][3], rhs.mtx[2][3])
            && CloseTof(mtx[3][0], rhs.mtx[3][0])
            && CloseTof(mtx[3][1], rhs.mtx[3][1])
            && CloseTof(mtx[3][2], rhs.mtx[3][2])
            && CloseTof(mtx[3][3], rhs.mtx[3][3]);
    }

    inline bool Matrix4x4::operator!=(const Matrix4x4& rhs) const
    {
        return !(*this == rhs);
    }

    inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
    {
        mtx[0][0] += rhs.mtx[0][0], mtx[0][1] += rhs.mtx[0][1], mtx[0][2] += rhs.mtx[0][2], mtx[0][3] += rhs.mtx[0][3];
        mtx[1][0] += rhs.mtx[1][0], mtx[1][1] += rhs.mtx[1][1], mtx[1][2] += rhs.mtx[1][2], mtx[1][3] += rhs.mtx[1][3];
        mtx[2][0] += rhs.mtx[2][0], mtx[2][1] += rhs.mtx[2][1], mtx[2][2] += rhs.mtx[2][2], mtx[2][3] += rhs.mtx[2][3];
        mtx[3][0] += rhs.mtx[3][0], mtx[3][1] += rhs.mtx[3][1], mtx[3][2] += rhs.mtx[3][2], mtx[3][3] += rhs.mtx[3][3];
        return *this;
    }

    inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
    {
        mtx[0][0] -= rhs.mtx[0][0], mtx[0][1] -= rhs.mtx[0][1], mtx[0][2] -= rhs.mtx[0][2], mtx[0][3] -= rhs.mtx[0][3];
        mtx[1][0] -= rhs.mtx[1][0], mtx[1][1] -= rhs.mtx[1][1], mtx[1][2] -= rhs.mtx[1][2], mtx[1][3] -= rhs.mtx[1][3];
        mtx[2][0] -= rhs.mtx[2][0], mtx[2][1] -= rhs.mtx[2][1], mtx[2][2] -= rhs.mtx[2][2], mtx[2][3] -= rhs.mtx[2][3];
        mtx[3][0] -= rhs.mtx[3][0], mtx[3][1] -= rhs.mtx[3][1], mtx[3][2] -= rhs.mtx[3][2], mtx[3][3] -= rhs.mtx[3][3];
        return *this;
    }

    inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
    {
        Matrix4x4 tmp;

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

    inline Matrix4x4& Matrix4x4::operator*=(float scalar)
    {
        mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar, mtx[0][3] *= scalar;
        mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar, mtx[1][3] *= scalar;
        mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar, mtx[2][3] *= scalar;
        mtx[3][0] *= scalar, mtx[3][1] *= scalar, mtx[3][2] *= scalar, mtx[3][3] *= scalar;
        return *this;
    }

    inline Matrix4x4& Matrix4x4::operator/=(float scalar)
    {
        mtx[0][0] /= scalar, mtx[0][1] /= scalar, mtx[0][2] /= scalar, mtx[0][3] /= scalar;
        mtx[1][0] /= scalar, mtx[1][1] /= scalar, mtx[1][2] /= scalar, mtx[1][3] /= scalar;
        mtx[2][0] /= scalar, mtx[2][1] /= scalar, mtx[2][2] /= scalar, mtx[2][3] /= scalar;
        mtx[3][0] /= scalar, mtx[3][1] /= scalar, mtx[3][2] /= scalar, mtx[3][3] /= scalar;
        return *this;
    }

    inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const
    {
        Matrix4x4 tmp(*this);
        tmp += rhs;
        return tmp;
    }

    inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const
    {
        Matrix4x4 tmp(*this);
        tmp -= rhs;
        return tmp;
    }

    inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
    {
        Matrix4x4 tmp(*this);
        tmp *= rhs;
        return tmp;
    }

    inline Matrix4x4 Matrix4x4::operator*(float scalar) const
    {
        Matrix4x4 tmp(*this);
        tmp *= scalar;
        return tmp;
    }

    inline Matrix4x4 Matrix4x4::operator/(float scalar) const
    {
        Matrix4x4 tmp(*this);
        tmp /= scalar;
        return tmp;
    }

    inline void Matrix4x4::Identity()
    {
        mtx[0][0] = 1.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f, mtx[0][3] = 0.0f;
        mtx[1][0] = 0.0f, mtx[1][1] = 1.0f, mtx[1][2] = 0.0f, mtx[1][3] = 0.0f;
        mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 1.0f, mtx[2][3] = 0.0f;
        mtx[3][0] = 0.0f, mtx[3][1] = 0.0f, mtx[3][2] = 0.0f, mtx[3][3] = 1.0f;
    }

} // End namespace MATH

#endif // MATRIX4X4_H
