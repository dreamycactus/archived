#ifndef VEC4F_H
#define VEC4F_H

#include "MATH_MathHelper.hpp"

/**
 *	Contains source code for my 3D vector class
 *	\file		vec4.h
 *	\author		Lewen Yu
 *	\date		May 2, 2012
 *  \brief      Vec4 based on Vec3. I am the master of copy-paste.
 */

namespace MATH
{
    template <class T>
    class Vec4
    {
        public:

        //! horizontal and vertical components
            T x, y, z, w;
        //! Plain constructor
        inline                                  Vec4<T>() : x(0), y(0), z(0), w(0) {}

        //! Copy ctor
        inline                                  Vec4<T>(const Vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w)  {}

        //! Constructor taking x, y arguments
        inline                                  Vec4<T>(const T x0, const T y0, const T z0, const T w0)
                                                        : x(x0), y(y0), z(z0), w(w0)  {}
        inline  Vec4<T>                         Set(float a, float b, float c, float d) { x=a;y=b;z=c;w=d; }
        //! Zero a vector
                void                            Zero()      { x = y = z = w = 0;}

        //! Boolean equivalence compare vector
        inline bool operator==(const Vec4<T>& v) const
               { return (x == v.x && y == v.y && z == v.z && w == v.w); }

        //boolean non-equivalence compare vector
        inline bool operator!=(const Vec4<T>& v) { return !(this == v); }

        //assignment operator
        inline const Vec4<T>& operator=(const Vec4<T>& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
            return *this;
        }

        //subtract vector
        inline const Vec4<T>& operator-=(const Vec4<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        /// Format Rest Later... ///

        //add vector
        inline const Vec4<T>& operator+=(const Vec4<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }
        //scale vector (multiply)
        inline const Vec4<T>& operator*=(const T num)
        {
            x *= num;
            y *= num;
            z *= num;
            w *= num;
            return *this;
        }

        //scale vector (divide)
        inline const Vec4<T>& operator/=(const T num)
        {
            x /= num;
            y /= num;
            z /= num;
            w /= num;
            return *this;
        }

        //negation of vector
        inline const Vec4<T> operator-() const
        {
            return Vec4<T>(-x, -y, -z, -w);
        }

        //subtract vector
        inline const Vec4<T> operator-(const Vec4<T>& v) const
        {
            Vec4<T> temp(*this);
            temp.x -= v.x;
            temp.y -= v.y;
            temp.z -= v.z;
            temp.w -= v.w;
            return temp;
        }

        //add vector
        inline const Vec4<T> operator+(const Vec4<T>& v) const
        {
            Vec4<T> temp(*this);
            temp.x += v.x;
            temp.y += v.y;
            temp.z += v.z;
            temp.w += v.w;
            return temp;
        }

        //scale vector (mulitply); form: Vec * float
        inline const Vec4<T> operator*(const T num) const
        {
            Vec4<T> temp(*this);
            temp.x *= num;
            temp.y *= num;
            temp.z *= num;
            temp.w *= num;
            return temp;
        }

        //scale vector (multiply); form: float * Vec
        friend const Vec4<T> operator*(const T num, Vec4<T> v)
        {
            v.x *= num;
            v.y *= num;
            v.z *= num;
            v.w *= num;
            return v; //value of v is unchanged
        }
        // Scale vector (divide)
        inline const Vec4<T> operator/(const T num) const
        {
            Vec4<T> temp(*this);
            temp.x /= num;
            temp.y /= num;
            temp.z /= num;
            temp.w /= num;
            return temp;
        }

        // Dot product
        inline T operator*(const Vec4<T>& v) const
        {
            return (x * v.x + y * v.y + z * v.z + w * v.w);
        }


        //cross product
        inline static Vec4<T> Cross(const Vec4<T>  &p, const Vec4<T> &v)
        {
            return Vec4<T>(p.y*v.z - p.z*v.y,
                           p.z*v.w - p.w*v.z,
                           p.w*v.x - p.x*v.w,
                           p.x*v.y - p.y*v.x);
        }
        inline Vec4<T> operator ^(const Vec4<T>& v) const
        {
            return Vec4<T>(y*v.z - z*v.y,
                           z*v.w - w*v.z,
                           w*v.x - x*v.w,
                           x*v.y - y*v.x);
        }
    };

    //macros for creating ctors for derived Vectors
    #define VECTOR4_CTORS(name, T)                        \
            name() {}                                     \
            name(const Vec4<T>& v) : Vec4<T>(v.x, v.y, v.z, v.w) {} \
            name(T x0, T y0, T z0, T w0) : Vec4<T>(x0, y0, z0, w0) {}


    class Vec4i : public Vec4<int>
    {
    public:
        inline VECTOR4_CTORS(Vec4i, int);
    };

    class Vec4f : public Vec4<float>
    {
    public:
        inline VECTOR4_CTORS(Vec4f, float);

        //gets squared length of the vector (fast) (Euclidean)
        inline float LengthSquared() const
        {
            return (float)(*this * *this);
        }

        //gets length of vector (Euclidean)
        inline float Length() const
        {
            return (float)sqrt(*this * *this);
        }

        //normalize the vector
        void Normalize()
        {
            *this /= Length();
        }

        //returns normalized vector
        Vec4f Normalized() const
        {
            return *this / Length();
        }

        //projects vector onto v
        void Project(const Vec4f& v)
        {
            *this = v * (*this * v)/(v * v);
        }

        // Projected vector onto v
        Vec4f Projected(const Vec4f& v)
        {
            Vec4f temp(*this);
            return v * (temp * v)/(v * v);
        }

        // Dot product
        inline float operator|(const Vec4f& v)
        {
            return x*v.x + y*v.y + z*v.z + w*v.w;
        }

        float const * GetVertex4fv() const      { return &x; }

	inline	operator	const float*() const	{ return &x; }
	inline	operator	float*()				{ return &x; }
    }; // End class Vec4f

} // End namespace MATH

#endif // VEC4řF_H
