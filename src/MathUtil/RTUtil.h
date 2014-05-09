// RTUtil.h
#ifndef __RTUTIL_H__
#define __RTUTIL_H__

/* Utility functions
 */

#include <string>
#include <stdlib.h>

#ifndef M_PI
#define M_PI   3.14159265
#endif

inline float randFloat()
{
	return (float)rand()/(float)RAND_MAX;
}

inline float convertToRadians(float degrees)
{
	return degrees*( M_PI/180 );
}

inline float convertToDegrees(float radians)
{
	return radians*(180/M_PI);
}

template<typename T>
inline T RTMin(const T& left, const T& right)
{
    return left < right ? left : right;
}

template<typename T>
inline T RTMax(const T& left, const T& right)
{
    return left > right ? left : right;
}


#endif //__RTUTIL_H__
