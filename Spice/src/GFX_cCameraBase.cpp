/**
 *
 */
#include "GFX_cCameraBase.hpp"

using namespace GFX;

cCameraBase::cCameraBase()
            :m_Pos(), m_Dir(), m_Viewport_W(100.0f), m_Viewport_H(100.0f), m_Aspect_Ratio(1.0f), m_Near(1.0f), m_Far(0.0f), m_Projection(), m_View(), m_Combined()
{
    //ctor
}

cCameraBase::~cCameraBase()
{
    //dtor
}

void cCameraBase::Translatef(float x, float y, float z)
{
    m_Pos += Vec3f(x, y, z);
}

void cCameraBase::TranslateTof(float x, float y, float z)
{
    Vec3f diff = Vec3f(x, y, z) - m_Pos;
    m_Pos += diff;
}
