////////////////////////////////////////////////////////////////////////////////
/**
 * \file    dcPlane.h
 * \author  Hua Fei Yu 0951402
 * \date    December 2, 2011
 * \brief   Plane class from Pierre Terdiman's IcePlane
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef DCPLANE_H
#define DCPLANE_H

// Headers
#include <math>
#include "vec3.h"

class dcPlane
{
    public:
    // Members
        Vec3f n; //!< Normal to plane
        float d; //!< Distance from origin

    inline          dcPlane() {}
    inline          dcPlane(float nx, float ny, float nz, float dist)   { setFromNormalDistance(nx, ny, nz, d); }
    inline          dcPlane(const Vec3f& normal, float dist)            { n = normal; d = dist; }
    inline          dcPlane(const Vec3f& p, const Vec3f& n);            { setFromPointNormal(p, n); }
    inline          dcPlane(const Vec3f& p0, Vec3f& p1, Vec3f& p2)      { setFromTriangle(p0, p1, p2); }

    inline virtual  dcPlane() {}

    inline dcPlane& zero()                                                          { n.zero(); d = 0.0f;           return *this; }
    inline dcPlane& setFromNormalDistance(float nx, float ny, float nz, float dist) { n.set(nx, ny, nz); d = dist;  return *this; }
    inline dcPlane& setFromPointNormal(const Vec3f& p, const Vec3f& normal)         { n = normal; d = -p | normal;  return *this; }
    inline dcPlane& setFromTriangle(const Vec3f& p0, Vec3f& p1, Vec3f& p2)
                    {
                        Vec3f edge0 = p1 - p0;
                        Vec3f edge1 = p2 - p0;

                        n = edge0 ^ edge1;
                        n.normalize();
                        d = -(p0 | n);
                        return	*this;
                    }

    inline float distance(const Vec3f& p) const { return (p | n) + d; }
    inline bool belongs(const Vec3f& p) const   { return fabs(distance(p)); }
    inline void normalize()
                {
                    float denom = 1.0f / n.length();
                    n.x *= denom; n.y *= denom; n.z *= denom;
                    d *= denom;

                }
};
