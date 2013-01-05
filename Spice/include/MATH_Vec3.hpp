#ifndef VEC3F_H
#define VEC3F_H

#include "MATH_MathHelper.hpp"

/**
 *	Contains source code for my 3D vector class
 *	\file		vec3.h
 *	\author		Hua Fei Yu 0951402
 *	\date		September 20, 2011
 *  \brief      Not the fastest, but it's mine. Originally based on vector template class for C++ found online somewhere..
 */

namespace MATH
{
    template <class T>
    class Vec3
    {
        public:

        //! horizontal and vertical components
            T x, y, z;
        //! Plain constructor
        inline                                  Vec3<T>() : x(0), y(0), z(0) {}

        //! Copy ctor
        inline                                  Vec3<T>(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z)  {}

        //! Constructor taking x, y arguments
        inline                                  Vec3<T>(const T x0, const T y0, const T z0)
                                                        : x(x0), y(y0), z(z0)  {}
        inline  Vec3<T>                         Set(float a, float b, float c) { x=a;y=b;z=c; }
        //! Zero a vector
                void                            Zero()      { x = y = z = 0;}

        //! Boolean equivalence compare vector
        inline bool operator==(const Vec3<T>& v) const
               { return (x == v.x && y == v.y && z == v.z); }

        //boolean non-equivalence compare vector
        inline bool operator!=(const Vec3<T>& v) { return !(this == v); }

        //assignment operator
        inline const Vec3<T>& operator=(const Vec3<T>& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        //subtract vector
        inline const Vec3<T>& operator-=(const Vec3<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        /// Format Rest Later... ///

        //add vector
        inline const Vec3<T>& operator+=(const Vec3<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        //scale vector (multiply)
        inline const Vec3<T>& operator*=(const T num)
        {
            x *= num;
            y *= num;
            z *= num;
            return *this;
        }

        //scale vector (divide)
        inline const Vec3<T>& operator/=(const T num)
        {
            x /= num;
            y /= num;
            z /= num;
            return *this;
        }

        //negation of vector
        inline const Vec3<T> operator-() const
        {
            return Vec3<T>(-x, -y, -z);
        }

        //subtract vector
        inline const Vec3<T> operator-(const Vec3<T>& v) const
        {
            Vec3<T> temp(*this);
            temp.x -= v.x;
            temp.y -= v.y;
            temp.z -= v.z;
            return temp;
        }

        //add vector
        inline const Vec3<T> operator+(const Vec3<T>& v) const
        {
            Vec3<T> temp(*this);
            temp.x += v.x;
            temp.y += v.y;
            temp.z += v.z;
            return temp;
        }

        //scale vector (mulitply); form: Vec * float
        inline const Vec3<T> operator*(const T num) const
        {
            Vec3<T> temp(*this);
            temp.x *= num;
            temp.y *= num;
            temp.z *= num;
            return temp;
        }

        //scale vector (multiply); form: float * Vec
        friend const Vec3<T> operator*(const T num, Vec3<T> v)
        {
            v.x *= num;
            v.y *= num;
            v.z *= num;
            return v; //value of v is unchanged
        }
        // Scale vector (divide)
        inline const Vec3<T> operator/(const T num) const
        {
            Vec3<T> temp(*this);
            temp.x /= num;
            temp.y /= num;
            temp.z /= num;
            return temp;
        }

        // Dot product
        inline T operator*(const Vec3<T>& v) const
        {
            return (x * v.x + y * v.y + z * v.z);
        }


        //cross product
        inline static Vec3<T> Cross(const Vec3<T>  &p, const Vec3<T> &v)
        {
            return Vec3<T>(p.y*v.z - v.y*p.z, p.z*v.x - v.z*p.x, p.x*v.y - v.x*p.y);
        }
        inline Vec3<T> operator ^(const Vec3<T>& v) const
        {
            return Vec3<T>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
        }
    };

    //macros for creating ctors for derived Vectors
    #define VECTOR3_CTORS(name, T)                        \
            name() {}                                     \
            name(const Vec3<T>& v) : Vec3<T>(v.x, v.y, v.z) {} \
            name(T x0, T y0, T z0) : Vec3<T>(x0, y0, z0) {}


    class Vec3i : public Vec3<int>
    {
    public:
        inline VECTOR3_CTORS(Vec3i, int);
    };

    class Vec3f : public Vec3<float>
    {
    public:
        inline VECTOR3_CTORS(Vec3f, float);

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
        Vec3f Normalized() const
        {
            return *this / Length();
        }

        //projects vector onto v
        void Project(const Vec3f& v)
        {
            *this = v * (*this * v)/(v * v);
        }

        // Projected vector onto v
        Vec3f Projected(const Vec3f& v)
        {
            Vec3f temp(*this);
            return v * (temp * v)/(v * v);
        }

        // Dot product
        inline float operator|(const Vec3f& v)
        {
            return x*v.x + y*v.y + z*v.z;
        }

        float const * GetVertex3fv() const      { return &x; }

	inline	operator	const float*() const	{ return &x; }
	inline	operator	float*()				{ return &x; }
    }; // End class Vec3f

} // End namespace MATH

#endif // VEC3F_H
