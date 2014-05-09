#include "Intersection.h"


Intersection::Intersection()
{
}

Intersection::Intersection(float _t, Pnt3f _loc, Vec3f _normal, SceneObject* _obj, float _u, float _v)
{
	t = _t;
	loc = _loc;
	normal = _normal;
	obj = _obj;
	u = _u;
	v = _v;
}

Intersection::~Intersection(void)
{
}