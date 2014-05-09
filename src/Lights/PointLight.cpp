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

// given a surface point, returns the direction from the surface point to the light.
const Vec3f PointLight::getDir(const Pnt3f& p)
{
	Vec3f dir = loc-p;
	dir.Normalize();
	return dir;
}
