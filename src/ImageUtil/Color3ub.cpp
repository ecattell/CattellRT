// Color3ub.cpp
#include "Color3ub.h"
#include "../MathUtil/RTUtil.h"

// Clamps color values
static unsigned char clamp(float c)
{
    return (unsigned char) RTMax(0.f, RTMin(255.f, c * 255.f));
}

// Constructors
Color3ub::Color3ub()
    : r(0), g(0), b(0), a(0)
{
}

Color3ub::Color3ub(const Color3ub& c)
    : r(c.r), g(c.g), b(c.b), a(c.a)
{
}


Color3ub::Color3ub(Component _r, Component _g, Component _b)
    : r(_r), g(_g), b(_b)
{
}


Color3ub::Color3ub(const Color3f& c)
    : r(clamp(c.r))
    , g(clamp(c.g))
    , b(clamp(c.b))
{
}
