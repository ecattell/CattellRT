#include "AreaLight.h"

AreaLight::AreaLight(const Pnt3f& _lightCorner, const Vec3f& _vec1, const Vec3f& _vec2, const Color3f& _color, short _numSamples, float _falloff)
{
	lightCorner = Pnt3f(_lightCorner);
	vec1 = Vec3f(_vec1);
	vec2 = Vec3f(_vec2);
	color = Color3f(_color);
	numSamples = _numSamples;
	falloff = _falloff;
	numSamplesInverse = 1/(float)numSamples; // precomputing for use in stratification
	updateSample(0,0);
}


AreaLight::~AreaLight(void)
{
}

// DEPRECATED
// Returns a random position inside light
Pnt3f AreaLight::getRandomPos(int j, int k) const
{
	float s = numSamplesInverse*j+randFloat()*numSamplesInverse;
	float t = numSamplesInverse*k+randFloat()*numSamplesInverse;

	return lightCorner + vec1*s + vec2*t;
}

// Chooses a new random sample given an index in the area light
// This position is used for getDist and getDir.
// This might pose some issue when multithreading.
void AreaLight::updateSample(int j, int k)
{
	float s = numSamplesInverse*j+randFloat()*numSamplesInverse;
	float t = numSamplesInverse*k+randFloat()*numSamplesInverse;

	loc = lightCorner + vec1*s + vec2*t;
}


short AreaLight::getNumSamples() const
{
	return numSamples;
}

// given a surface point, returns the direction from the surface point to the point.
const Vec3f AreaLight::getDir(const Pnt3f& p)
{
	Vec3f dir = loc-p;
	dir.Normalize();
	return dir;
}

// given a surface point, returns the distance to the point.
const float AreaLight::getDist(const Pnt3f& p)
{
	Vec3f dir = loc-p;
	float dist = dir.Length();
	return dist;
}
