#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "../MathUtil/Vec3f.h"
typedef Vec3f Pnt3f;

/*
Stores information about a ray-object intersection,
such as the t value at which the intersection occurred,
the intersection point, the uv coordinates of the intersection,
and the normal at the intersection point.
*/
class SceneObject;

struct Intersection
{
public:
	Intersection();
	Intersection(float, Pnt3f, Vec3f, SceneObject*, float u = 0, float v = 0);
	virtual ~Intersection(void); // TODO: Why is this virtual?

	float t;
	Pnt3f loc;
	Vec3f normal;
	SceneObject* obj;
	float u,v;
};

#endif // __INTERSECTION_H__
