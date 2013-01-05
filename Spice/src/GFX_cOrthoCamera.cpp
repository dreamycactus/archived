#include "GFX_cOrthoCamera.hpp"

using namespace GFX;

cOrthoCamera::cOrthoCamera()
             :m_Viewport()
{}

cOrthoCamera::cOrthoCamera(cRectf& vp)
             :m_Viewport(vp)
{
    cCameraBase::m_Pos = Vec3f(vp.Left(), vp.Top(), 1.0f);
    cCameraBase::m_Viewport_W = vp.Width();
    cCameraBase::m_Viewport_H = vp.Height();
}

cOrthoCamera::~cOrthoCamera() {}

void cOrthoCamera::Translatef(float x, float y)
{
    cCameraBase::Translatef(x, y, 0);
    //m_Viewport.SetTop(m_Pos.y);
    //m_Viewport.SetLeft(m_Pos.x);
}

void cOrthoCamera::TranslateTof(float x, float y)
{
    cCameraBase::TranslateTof(x, y, 0);
    //m_Viewport.SetTop(m_Pos.y);
    //m_Viewport.SetLeft(m_Pos.x);
}
