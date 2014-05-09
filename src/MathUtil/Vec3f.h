// Vec3f.h
#ifndef __Vec3f_H__
#define __Vec3f_H__

//#include "MathForward.h"

#include <math.h>

/**
* Vec3f represents a 3-vector
*/
struct Vec3f
{
    //
    // Initalization
    //
    inline Vec3f();
    inline Vec3f(const Vec3f& v);
    inline Vec3f(float x, float y, float z);
    inline Vec3f(float s);

    //
    // Assignment
    //
    inline Vec3f& operator=(const Vec3f& v);

    //
    // Overloaded operators
    //
    inline Vec3f& operator*=(float right);
    inline Vec3f& operator/=(float right);
    inline Vec3f& operator+=(const Vec3f& right);
    inline Vec3f& operator-=(const Vec3f& right);

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
    float x, y, z;

    //
    // Constants
    //
    static const Vec3f Zero;
    static const Vec3f eX;
    static const Vec3f eY;
    static const Vec3f eZ;

    //
    // Static math functions
    //
    inline static Vec3f Cross(const Vec3f& left, const Vec3f& right);
    inline static float Dot(const Vec3f& left, const Vec3f& right);
    inline static Vec3f DirectProduct(const Vec3f& left, const Vec3f& right);
    inline static Vec3f Lerp(const Vec3f& left, const Vec3f& right, float s);
    inline static Vec3f ComponentMax(const Vec3f& left, const Vec3f& right);
    inline static Vec3f ComponentMin(const Vec3f& left, const Vec3f& right);
};

inline Vec3f operator*(const Vec3f& left, float right);
inline Vec3f operator*(float left, const Vec3f& right);
inline Vec3f operator/(const Vec3f& left, float right);
inline Vec3f operator+(const Vec3f& left, const Vec3f& right);
inline Vec3f operator-(const Vec3f& left, const Vec3f& right);
inline Vec3f operator-(const Vec3f& v);

#include "Vec3f.inl"

#endif  // __Vec3f_H__

