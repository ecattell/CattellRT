// Vec3f.inl
#ifndef __Vec3f_INL__
#define __Vec3f_INL__

/**
* Inline file for Vec3f.h
*/

#include "RTUtil.h" // for RTMin, RTMax

//

inline Vec3f::Vec3f()
{
    x = 0;
    y = 0;
    z = 0;
}

inline Vec3f::Vec3f(float inX, float inY, float inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}

inline Vec3f::Vec3f(float s)
{
    x = s;
    y = s;
    z = s;
}

inline Vec3f::Vec3f(const Vec3f &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

/*
inline Vec3f::Vec3f(const STPoint3& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}
*/

inline Vec3f& Vec3f::operator=(const Vec3f &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

/**
* Length of vector
*/
inline float Vec3f::Length() const
{
    return sqrtf(LengthSq());
}

/**
* Length squared of vector
*/
inline float Vec3f::LengthSq() const
{
    return x * x + y * y + z * z;
}

/**
* True if all elements are real values
*/
inline bool Vec3f::Valid() const
{
    // For standard floating-point math, the
    // "not-a-number" (NaN) representation
    // will test as not-equal to every value,
    // including itself!
    return ((x == x) && (y == y) && (z == z));
}

/**
* Sets the length of vector to 1
*/
inline void Vec3f::Normalize()
{
    float len = Length();
    if (len != 0.0f) {
        (*this) /= len;
    }
}

/**
* Sets the length of vector to NewLength
*/
inline void Vec3f::SetLength(float newLength)
{
    float len = Length();
    if (len != 0.0f) {
        (*this) *= newLength / len;
    }
}

/**
* Returns cross product of two vectors
*/
inline Vec3f Vec3f::Cross(
    const Vec3f& left, const Vec3f& right)
{
    return Vec3f(left.y * right.z - left.z * right.y,
                     left.z * right.x - left.x * right.z,
                     left.x * right.y - left.y * right.x);
}

/**
* Returns dot product of two vectors
*/
inline float Vec3f::Dot(
    const Vec3f& left, const Vec3f& right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

/**
* Returns direct product of two vectors
*/
inline Vec3f Vec3f::DirectProduct(
    const Vec3f& left, const Vec3f& right)
{
    return Vec3f(left.x * right.x, left.y * right.y, left.z * right.z);
}

/**
* Linearly interpolates between two vectors;
* s = 0 returns left, s = 1 returns right
*/
inline Vec3f Vec3f::Lerp(
    const Vec3f& left, const Vec3f& right, float s)
{
    return left + s * (right - left);
}

/**
* Returns the vector that is the component-wise maximum of the given vectors
*/
inline Vec3f Vec3f::ComponentMax(
    const Vec3f& left, const Vec3f& right)
{
    return Vec3f(
        RTMax(left.x, right.x),
        RTMax(left.y, right.y),
        RTMax(left.z, right.z));
}

/**
* Returns the vector that is the component-wise minimum of the given vectors
*/
inline Vec3f Vec3f::ComponentMin(
    const Vec3f& left, const Vec3f& right)
{
    return Vec3f(
        RTMin(left.x, right.x),
        RTMin(left.y, right.y),
        RTMin(left.z, right.z));
}

inline Vec3f operator*(const Vec3f& left, float right)
{
    Vec3f result(left);
    result *= right;
    return result;
}

inline Vec3f operator*(float left, const Vec3f& right)
{
    Vec3f result(right);
    result *= left;
    return result;
}

inline Vec3f operator/(const Vec3f& left, float right)
{
    Vec3f result(left);
    result /= right;
    return result;
}

inline Vec3f operator+(const Vec3f& left, const Vec3f& right)
{
    Vec3f result(left);
    result += right;
    return result;
}

inline Vec3f operator-(const Vec3f& left, const Vec3f& right)
{
    Vec3f result(left);
    result -= right;
    return result;
}

inline Vec3f& Vec3f::operator*=(float right)
{
    x *= right;
    y *= right;
    z *= right;
    return *this;
}

inline Vec3f& Vec3f::operator/=(float right)
{
    x /= right;
    y /= right;
    z /= right;
    return *this;
}

inline Vec3f& Vec3f::operator+=(const Vec3f& right)
{
    x += right.x;
    y += right.y;
    z += right.z;
    return *this;
}

inline Vec3f& Vec3f::operator-=(const Vec3f& right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
    return *this;
}

inline Vec3f operator-(const Vec3f& v)
{
    return Vec3f(-v.x, -v.y, -v.z);
}

// Reflect vector. For example,
// direction that a light ray from the light source to this surface point would reflect to based on surface normal
inline Vec3f reflectVec(Vec3f a, Vec3f b)
{
		return (a - 2.0 * Vec3f::Dot(b, a) * b);
}

// If the sign of the dot is negative, they're pointing in different directions. If it's positive they're pointed in the same direction.
inline bool SameDirection(Vec3f d, Vec3f N)
{
	return (Vec3f::Dot(d,N) < 0);
}

#endif  // __Vec3f_INL__
