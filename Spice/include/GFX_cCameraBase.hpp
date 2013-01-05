#ifndef CCAMERABASE_H
#define CCAMERABASE_H

#include "MATH_LinearAlgebra.hpp"
#include "MATH_Primitives.hpp"

using namespace MATH;

namespace GFX
{
    class cCameraBase
    {
    public:
        cCameraBase();
        virtual ~cCameraBase();

        // Apply the projection and view matricies
        void ApplyMatricies() {};
        inline void LoadIdentity() { m_Pos = Vec3f(0.0f,0.0f,0.0f); }
        void Translatef(float x, float y, float z);
        void TranslateTof(float x, float y, float z);
        void Unproject(const Vec3f& vec) {};
        void UnprojectCustom(const Vec3f& vec, float viewport_x, float viewport_y, float viewport_w, float viewport_h) {};

        const Vec3f& GetPos() const     { return m_Pos;  }
        float GetAspectRatio() const    { return m_Aspect_Ratio; }
        float GetNear() const           { return m_Near; }
        float GetFar()  const           { return m_Far;  }
        float GetViewportWidth() const  { return m_Viewport_W; }
        float GetViewportHeight() const { return m_Viewport_H; }


    protected:
        Vec3f m_Pos;
        Vec3f m_Dir;

        Matrix4x4 m_Projection;
        Matrix4x4 m_View;
        Matrix4x4 m_Combined;

        float m_Near, m_Far;
        float m_Viewport_W, m_Viewport_H;
        float m_Aspect_Ratio;

    private:

    }; // End class cCameraBase

} // End namespace GFX

#endif // CCAMERABASE_H
