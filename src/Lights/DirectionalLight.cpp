#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(const Vec3f& _dir,const Color3f& _col)
{
	direction = Vec3f(_dir);
	color = Color3f(_col);
	inverseDirection = direction*(-1);
}


DirectionalLight::~DirectionalLight(void)
{
}

// Returns inverse direction to match other lights where getDir returns direction to light.
const Vec3f DirectionalLight::getDir(const Pnt3f& p)
{
	return inverseDirection;
}

// Returns inverse direction
const Vec3f DirectionalLight::getDir()
{
	return inverseDirection;
}