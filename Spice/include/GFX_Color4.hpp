// I bite my lip, and omit the "u"
#ifndef COLOR4_H
#define COLOR4_H


struct Color4
{
    Color4(float vr, float vg, float vb, float va)
    : r(vr), g(vg), b(vb), a(va) {}
    Color4()
    : r(0.0f), g(0.0f), b(0.0f), a(0.0f){}
    float r,g,b,a;
    void set(float vr, float vg, float vb, float va)
    { r = vr; g = vg, b=vb, a=va; }
};

#endif // COLOR4_H
