#include "Ray.h"

// Represents a 2d parametric line
Ray::Ray(const Pnt3f& _e, const Vec3f& _d, float _min, float _max)
{
	e = Pnt3f(_e);
	d = Vec3f(_d);
	min = _min;
	max = _max;
}

/*
Ray::Ray(const Ray& _r)
{
	e = Pnt3f(_r.e);
	d = Vec3f(_r.d);
	min = _r.min;
	max = _r.max;
}
*/

Ray::~Ray(void)
{
}
