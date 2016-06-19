// Vec2f.inl
#ifndef __Vec2f_INL__
#define __Vec2f_INL__

/**
* Inline file for Vec2f.h
*/

#include "RTUtil.h" // for RTMin, RTMax

//

inline Vec2f::Vec2f()
{
    x = 0;
    y = 0;
}

inline Vec2f::Vec2f(float inX, float inY)
{
    x = inX;
    y = inY;
}

inline Vec2f::Vec2f(float s)
{
    x = s;
    y = s;
}

inline Vec2f::Vec2f(const Vec2f &v)
{
    x = v.x;
    y = v.y;
}

inline Vec2f& Vec2f::operator=(const Vec2f &v)
{
    x = v.x;
    y = v.y;
    return *this;
}

/**
* Length of vector
*/
inline float Vec2f::Length() const
{
    return sqrtf(LengthSq());
}

/**
* Length squared of vector
*/
inline float Vec2f::LengthSq() const
{
    return x * x + y * y;
}

/**
* True if all elements are real values
*/
inline bool Vec2f::Valid() const
{
    // For standard floating-point math, the
    // "not-a-number" (NaN) representation
    // will test as not-equal to every value,
    // including itself!
    return ((x == x) && (y == y));
}

/**
* Sets the length of vector to 1
*/
inline void Vec2f::Normalize()
{
    float len = Length();
    if (len != 0.0f) {
        (*this) /= len;
    }
}

/**
* Sets the length of vector to NewLength
*/
inline void Vec2f::SetLength(float newLength)
{
    float len = Length();
    if (len != 0.0f) {
        (*this) *= newLength / len;
    }
}

/**
* Returns dot product of two vectors
*/
inline float Vec2f::Dot(
    const Vec2f& left, const Vec2f& right)
{
    return left.x * right.x + left.y * right.y;
}

/**
* Returns direct product of two vectors
*/
inline Vec2f Vec2f::DirectProduct(
    const Vec2f& left, const Vec2f& right)
{
    return Vec2f(left.x * right.x, left.y * right.y);
}

/**
* Linearly interpolates between two vectors;
* s = 0 returns left, s = 1 returns right
*/
inline Vec2f Vec2f::Lerp(
    const Vec2f& left, const Vec2f& right, float s)
{
    return left + s * (right - left);
}

/**
* Returns the vector that is the component-wise maximum of the given vectors
*/
inline Vec2f Vec2f::ComponentMax(
    const Vec2f& left, const Vec2f& right)
{
    return Vec2f(
        RTMax(left.x, right.x),
        RTMax(left.y, right.y));
}

/**
* Returns the vector that is the component-wise minimum of the given vectors
*/
inline Vec2f Vec2f::ComponentMin(
    const Vec2f& left, const Vec2f& right)
{
    return Vec2f(
        RTMin(left.x, right.x),
        RTMin(left.y, right.y));
}

inline Vec2f operator*(const Vec2f& left, float right)
{
    Vec2f result(left);
    result *= right;
    return result;
}

inline Vec2f operator*(float left, const Vec2f& right)
{
    Vec2f result(right);
    result *= left;
    return result;
}

inline Vec2f operator/(const Vec2f& left, float right)
{
    Vec2f result(left);
    result /= right;
    return result;
}

inline Vec2f operator+(const Vec2f& left, const Vec2f& right)
{
    Vec2f result(left);
    result += right;
    return result;
}

inline Vec2f operator-(const Vec2f& left, const Vec2f& right)
{
    Vec2f result(left);
    result -= right;
    return result;
}

inline Vec2f& Vec2f::operator*=(float right)
{
    x *= right;
    y *= right;
    return *this;
}

inline Vec2f& Vec2f::operator/=(float right)
{
    x /= right;
    y /= right;
    return *this;
}

inline Vec2f& Vec2f::operator+=(const Vec2f& right)
{
    x += right.x;
    y += right.y;
    return *this;
}

inline Vec2f& Vec2f::operator-=(const Vec2f& right)
{
    x -= right.x;
    y -= right.y;
    return *this;
}

inline Vec2f operator-(const Vec2f& v)
{
    return Vec2f(-v.x, -v.y);
}

// Reflect vector. For example,
// direction that a light ray from the light source to this surface point would reflect to based on surface normal
inline Vec2f reflectVec(Vec2f a, Vec2f b)
{
		return (a - 2.0 * Vec2f::Dot(b, a) * b);
}

// If the sign of the dot is negative, they're pointing in different directions. If it's positive they're pointed in the same direction.
inline bool SameDirection(Vec2f d, Vec2f N)
{
	return (Vec2f::Dot(d,N) < 0);
}

#endif  // __Vec2f_INL__
