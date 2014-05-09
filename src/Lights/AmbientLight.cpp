#include "AmbientLight.h"


AmbientLight::AmbientLight(const Color3f& _col)
{
	color = Color3f(_col);
}


AmbientLight::~AmbientLight(void)
{
}

const Vec3f AmbientLight::getDir(const Pnt3f& p)
{
	return Vec3f(0.0,0.0,0.0);
}