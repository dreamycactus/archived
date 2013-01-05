#ifndef COLLISION2D_H
#define COLLISION2D_H

namespace MATH
{
    class cRectf;
    class Vec2f;

    Vec2f GetMinTranslationVectorRectRect(const cRectf& r1, const cRectf& r2);
}

#endif // COLLISION2D_H
