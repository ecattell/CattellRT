#ifndef __RAY_H__
#define __RAY_H__

#include "../MathUtil/RTMath.h"
#include "../MathUtil/Vec3f.h"
typedef Vec3f Pnt3f;

/*
 * Represents a 2d parametric line defined by e + t*d.
 * 
 * The ray's starting point is represented be e.
 * Its direction is represented by d.
 * 
 * Values less than 0 or greater than 1 for t are
 * out of range and won't cause intersections
 * 
 */

// TODO should I implement getters or setters (or make some values constants) to prevent other classes from modifying things by accident?
class Ray
{
public:
	Ray(const Pnt3f& e, const Vec3f& d, float min, float max);
	Ray(const Ray& _r);
	virtual ~Ray(void);
	Pnt3f e;
	Pnt3f multInverseDir;
	Vec3f d;
	float min;
	float max;

private:

};

#endif //__RAY_H__
