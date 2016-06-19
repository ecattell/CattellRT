// Vec2f.h
#ifndef __Vec2f_H__
#define __Vec2f_H__

//#include "MathForward.h"
#include <math.h>

/**
* Vec2f represents a 2-vector
*/
struct Vec2f
{
    //
    // Initalization
    //
    inline Vec2f();
    inline Vec2f(const Vec2f& v);
    inline Vec2f(float x, float y);
    inline Vec2f(float s);

    //
    // Assignment
    //
    inline Vec2f& operator=(const Vec2f& v);

    //
    // Overloaded operators
    //
    inline Vec2f& operator*=(float right);
    inline Vec2f& operator/=(float right);
    inline Vec2f& operator+=(const Vec2f& right);
    inline Vec2f& operator-=(const Vec2f& right);

    //
    // Normalization
    //
    inline void Normalize();
    inline void SetLength(float newLength);

    //
    // Math
    //
    inline float Length() const;
    inline float LengthSq() const;

    //
    // Validation
    //
    inline bool Valid() const;

    //
    // Component accessors
    //
    inline float& Component(unsigned int index)
    {
        return ((float *)this)[index];
    }

    inline float Component(unsigned int index) const
    {
        return ((const float *)this)[index];
    }

    //
    // Local members
    //
    float x, y;

    //
    // Constants
    //
    static const Vec2f Zero;
    static const Vec2f eX;
    static const Vec2f eY;

    //
    // Static math functions
    //
    inline static Vec2f Cross(const Vec2f& left, const Vec2f& right);
    inline static float Dot(const Vec2f& left, const Vec2f& right);
    inline static Vec2f DirectProduct(const Vec2f& left, const Vec2f& right);
    inline static Vec2f Lerp(const Vec2f& left, const Vec2f& right, float s);
    inline static Vec2f ComponentMax(const Vec2f& left, const Vec2f& right);
    inline static Vec2f ComponentMin(const Vec2f& left, const Vec2f& right);
};

inline Vec2f operator*(const Vec2f& left, float right);
inline Vec2f operator*(float left, const Vec2f& right);
inline Vec2f operator/(const Vec2f& left, float right);
inline Vec2f operator+(const Vec2f& left, const Vec2f& right);
inline Vec2f operator-(const Vec2f& left, const Vec2f& right);
inline Vec2f operator-(const Vec2f& v);

#include "Vec2f.inl"

#endif  // __Vec2f_H__

