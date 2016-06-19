#include "PointLight.h"

PointLight::PointLight(const Pnt3f& _loc, const Color3f& _color)
{
	loc = Pnt3f(_loc);
	color = Color3f(_color);
}

PointLight::PointLight(float x, float y, float z, const Color3f& _color)
{
	loc = Pnt3f(x,y,z);
	color = Color3f(_color);
}

PointLight::~PointLight(void)
{

}

// given a surface point, returns the direction from the surface point to the point.
const Vec3f PointLight::getDir(const Pnt3f& p)
{
	Vec3f dir = loc-p;
	dir.Normalize();
	return dir;
}

// given a surface point, returns the distance to the point.
const float PointLight::getDist(const Pnt3f& p)
{
	Vec3f dir = loc-p;
	float dist = dir.Length();
	return dist;
}
