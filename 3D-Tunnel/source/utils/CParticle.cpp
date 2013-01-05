// Headers
#include "misc/CParticle.h"

CParticle::CParticle()
{

}

CParticle::CParticle(const Vec3f& p, const Vec3f& v) :
pos(p),
vel(v),
accel(Vec3f(0.0f, 0.0f, 0.0f))
{

}

CParticle::~CParticle()
{

}

void CParticle::init(float l, float r, float g, float b)
{
    max_life_ = l;
    life_ = l;
    col_r = r;
    col_g = g;
    col_b = b;
}

void CParticle::tick(float delta)
{
    vel     += accel * delta;
    pos     += vel * delta;
    life_   -= delta;
}
