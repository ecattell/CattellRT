#include "AmbientLight.h"


AmbientLight::AmbientLight(const Color3f& _col)
{
	color = Color3f(_col);
}


AmbientLight::~AmbientLight(void)
{
}

// given a surface point, returns the direction from the surface point to the point.
const Vec3f AmbientLight::getDir(const Pnt3f& p)
{
	throw "Direction can not be called on an AreaLight.";
}

// given a surface point, returns the distance to the point.
const float AmbientLight::getDist(const Pnt3f& p)
{
	return 0.0;
}
