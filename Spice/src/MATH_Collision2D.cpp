#include "MATH_Collision2D.hpp"
#include "MATH_MathHelper.hpp"
#include "MATH_Vec2.hpp"
#include "MATH_Primitives.hpp"

namespace MATH
{
    float IntervalDistance(float minA, float maxA, float minB, float maxB)
    {
        if (minA < minB) {
            return minB - maxA;
        } else {
            return minA - maxB;
        }
    }

    Vec2f GetMinTranslationVectorRectRect(const cRectf& r1, const cRectf& r2)
    {
        const float xIntervalDistance = IntervalDistance(r1.Left(), r1.Right(), r2.Left(), r2.Right());
        const float yIntervalDistance = IntervalDistance(r1.Top(), r1.Bottom(), r2.Top(), r2.Bottom());
        bool isAxisHorizontal;

        if (xIntervalDistance>=0.0f&&yIntervalDistance>=0.0f) {
            return Vec2f(0.0f, 0.0f);
        }

        if (fabs(xIntervalDistance)<fabs(yIntervalDistance)) {
            if (r1.Left()<r2.Left()) {
                return Vec2f(-fabs(xIntervalDistance), 0.0f);
            } else {
                return Vec2f(fabs(xIntervalDistance), 0.0f);
            }
        } else {
            if (r1.Top()<r2.Top()) {
                return Vec2f(0.0f, -fabs(yIntervalDistance));
            } else {
                return Vec2f(0.0f, fabs(yIntervalDistance));
            }
        }




    }
}


