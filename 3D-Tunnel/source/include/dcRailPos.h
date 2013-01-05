#ifndef DCRAILPOS_H
#define DCRAILPOS_H

#include <cmath>
#include "dcMath.h"

class dcRailPos
{
    public:
        dcRailPos(){}
        virtual ~dcRailPos(){}
        Vec3f getVec3f() const
        {
            return Vec3f(radius*cos(dcMath::degreesToRadians(degree)),
                         radius*sin(dcMath::degreesToRadians(degree)),
                         depth);
        }

        float degree;
        float depth;
        static float radius;
};

#endif // DCRAILPOS_H
