#include "math/vec3.h"
#include "math/Matrix3.h"
Vec3f& Vec3f::transform(const Vec3f& r, const Matrix3& rotpos, const Vec3f& l)
{
    x = r.x * rotpos.m[0][0] + r.y * rotpos.m[0][1] + r.z * rotpos.m[0][2] + l.x;
    y = r.x * rotpos.m[1][0] + r.y * rotpos.m[1][1] + r.z * rotpos.m[1][2] + l.y;
    z = r.x * rotpos.m[2][0] + r.y * rotpos.m[2][1] + r.z * rotpos.m[2][2] + l.z;
    return *this;
}
