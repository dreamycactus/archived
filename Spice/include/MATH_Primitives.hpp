#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "MATH_Vec2.hpp"

namespace MATH
{
    class cRectf
    {
    public:
        cRectf() : m_Topleft(), m_Dim() {}
        cRectf(float left, float top, float width, float height)
        : m_Topleft(Vec2f(left, top)), m_Dim(Vec2f(width, height)) {}

        //copy ctor
        inline cRectf(const cRectf& r) : m_Topleft(r.Left(), r.Top()), m_Dim(r.Width(), r.Height()) {}

        inline const float Left() const { return m_Topleft.x; }
        inline const float Right() const { return (m_Topleft.x+m_Dim.x); }
        inline const float Bottom() const { return m_Topleft.y+m_Dim.y; }
        inline const float Top() const { return m_Topleft.y; }
        inline const float Width() const { return m_Dim.x; }
        inline const float Height() const { return m_Dim.y; }

        inline void SetTop(float y) { m_Topleft.y = y; }
        inline void SetLeft(float x) { m_Topleft.x = x; }
        inline void SetWidth(float w) { m_Dim.x = w; }
        inline void SetHeight(float h) { m_Dim.y = h; }

        inline bool IsCollidedRect(const cRectf& rect)
        {
            return (!((Right()<rect.Left())
                  ||(Left()>rect.Right())
                  ||(Top()>rect.Bottom())
                  ||(Bottom()<rect.Top())));
        }
        static cRectf GetShiftedRect(const cRectf& r, const Vec2f& v)
        {
            return cRectf(v.x+r.Left(), v.y+r.Top(), r.Width(), r.Height());
        }


    private:
        Vec2f m_Topleft, m_Dim;
    };

}

#endif // PRIMITIVES_H
