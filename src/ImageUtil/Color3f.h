// Color3f.h
#ifndef __Color3f_H__
#define __Color3f_H__

#include "../MathUtil/MathForward.h"

/**
* Represents a color with three floating point values.
* Intended values 0.f to 1.f for conversion to Color3ub.
*/

struct Color3f
{
public:
	// Color values
    float r, g, b;

    // Constructors
    Color3f();
    explicit Color3f(float _c);
    Color3f(float _r, float _g, float _b);
    Color3f(const Color3f& c);
    explicit Color3f(const Color3ub& c);

    // Math operators

    Color3f operator+(const Color3f&) const;
    Color3f& operator+=(const Color3f&);

    Color3f operator-(const Color3f&) const;
    Color3f& operator-=(const Color3f&);

    Color3f operator*(const float) const;
    Color3f operator*(const Color3f&) const;
    Color3f& operator*=(const float);
    Color3f& operator*=(const Color3f&);

    Color3f operator/(const float) const;
    Color3f operator/(const Color3f&) const;

    Color3f& operator/=(const float);
    Color3f& operator/=(const Color3f&);

	// Lerp
	static Color3f lerp(Color3f, Color3f, float);
};

// Float * color operator
Color3f operator*(float, const Color3f);

#endif //__Color3f_H__

