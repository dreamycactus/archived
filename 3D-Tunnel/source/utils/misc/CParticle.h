////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CParticile.h
 * \author  Hua Fei Yu 0951402
 * \date    September 22, 2011
 * \brief   Simple particles class
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef CPARTICLE_H
#define CPARTICLE_H

// Headers
#include "dcmath.h"

class CParticle
{
    public:
                                CParticle();
                                CParticle(const Vec3f& p, const Vec3f& v);
    virtual                     ~CParticle();

            void                init(float l, float r=0.0f, float g=0.0f, float b=0.0f);
            void                tick(float delta);

// Getter / Setter

            bool                isVisible()                 { return visible_; }
            void                set_visible(bool b)         { visible_ = b; }


        // Members
            Vec3f               pos;
            Vec3f               vel;
            Vec3f               accel;
            float               col_r, col_g, col_b;
    protected:
            float               life_;
            float               max_life_;
            bool                visible_;

};

#endif // CPARTICLE_H
