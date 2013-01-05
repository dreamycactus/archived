#ifndef CORTHOCAM_H
#define CORTHOCAM_H

#include "GFX_cCameraBase.hpp"
#include "MATH_LinearAlgebra.hpp"

#include <iostream>
using namespace std;

using namespace MATH;

namespace GFX
{
    class cOrthoCamera : public cCameraBase
    {
    public:
        cOrthoCamera();
        cOrthoCamera(cRectf& vp);
        ~cOrthoCamera();
        void Translatef(float x, float y);
        void TranslateTof(float x, float y);

        const Vec2f& GetPos() const;
        cRectf* GetViewportRect();
        void    SetViewportRect(cRectf& vp) { m_Viewport = vp; }

    private:
        cRectf m_Viewport;
    };

    inline const Vec2f& cOrthoCamera::GetPos() const
    {
        return Vec2f(cCameraBase::m_Pos.x, cCameraBase::m_Pos.y);
    }

    inline cRectf* cOrthoCamera::GetViewportRect()
    {
        return new cRectf(cCameraBase::m_Pos.x, cCameraBase::m_Pos.y,
                      cCameraBase::m_Viewport_W, cCameraBase::m_Viewport_H);
    }
}

#endif // CORTHOCAM_H
