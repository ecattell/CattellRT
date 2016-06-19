#include "Light.h"

Light::Light(void)
{
}


Light::~Light(void)
{
}

const Vec3f Light::getDir(const Pnt3f& p)
{
	throw "getDir for your light class should be overriden!";
}

const float Light::getDist(const Pnt3f& p)
{
	throw "getDist for your light class should be overriden!";
}
