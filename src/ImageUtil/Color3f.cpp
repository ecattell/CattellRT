// Color3f.cpp
#include "Color3f.h"

#include "Color3ub.h"

#include <math.h>

//

/* Constructors */
Color3f::Color3f() 
: r(0.f), g(0.f), b(0.f)
{
}

Color3f::Color3f(float _c)
: r(_c), g(_c), b(_c)
{
}

Color3f::Color3f(float _r, float _g, float _b) 
: r(_r), g(_g), b(_b)
{
}

Color3f::Color3f(const Color3f& c) 
: r(c.r), g(c.g), b(c.b)
{
}

Color3f::Color3f(const Color3ub& c) 
{
    this->r = c.r / 255.f;
    this->g = c.g / 255.f;
    this->b = c.b / 255.f;
}

/* Math operators */
Color3f Color3f::operator+(const Color3f& rhs) const
{
    Color3f rval;
    rval.r = this->r + rhs.r;
    rval.g = this->g + rhs.g;
    rval.b = this->b + rhs.b;
    return rval;
}

Color3f& Color3f::operator+=(const Color3f& rhs)
{
    this->r += rhs.r;
    this->g += rhs.g;
    this->b += rhs.b;
    return *this;
}

Color3f Color3f::operator-(const Color3f& rhs) const
{
    Color3f rval;
    rval.r = this->r - rhs.r;
    rval.g = this->g - rhs.g;
    rval.b = this->b - rhs.b;
    return rval;
}

Color3f& Color3f::operator-=(const Color3f& rhs)
{
    this->r -= rhs.r;
    this->g -= rhs.g;
    this->b -= rhs.b;
    return *this;
}

Color3f Color3f::operator*(const float s) const
{
    Color3f rval;
    rval.r = this->r * s;
    rval.g = this->g * s;
    rval.b = this->b * s;
    return rval;
}

Color3f Color3f::operator*(const Color3f& s) const
{
    Color3f rval;
    rval.r = this->r * s.r;
    rval.g = this->g * s.g;
    rval.b = this->b * s.b;
    return rval;
}

Color3f& Color3f::operator*=(const float s)
{
    this->r *= s;
    this->b *= s;
    this->g *= s;
    return *this;
}

Color3f& Color3f::operator*=(const Color3f& s)
{
    this->r *= s.r;
    this->g *= s.g;
    this->b *= s.b;
    return *this;
}

Color3f Color3f::operator/(const float s) const
{
    return *this * (1.f / s);
}

Color3f Color3f::operator/(const Color3f& s) const
{
    Color3f result;
    result.r = this->r / s.r;
    result.g = this->g / s.g;
    result.b = this->b / s.b;
    return result;
}
Color3f& Color3f::operator/=(const float s)
{
    this->r /= s;
    this->g /= s;
    this->b /= s;
    return *this;
}
Color3f& Color3f::operator/=(const Color3f& s)
{
    this->r /= s.r;
    this->g /= s.g;
    this->b /= s.b;
    return *this;
}


// Float * color
Color3f operator*(float lhs, Color3f &rhs)
{
    return rhs * lhs;
}

Color3f Color3f::lerp(Color3f c0, Color3f c1, float t)
{
	return c0+(c1-c0)*t;
}
