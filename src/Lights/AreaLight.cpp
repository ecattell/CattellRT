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
}


AreaLight::~AreaLight(void)
{
}

// Returns a random position inside light
Pnt3f AreaLight::getRandomPos(int j, int k) const
{
	float s = numSamplesInverse*j+randFloat()*numSamplesInverse;
	float t = numSamplesInverse*k+randFloat()*numSamplesInverse;

	return lightCorner + vec1*s + vec2*t;
	
}

short AreaLight::getNumSamples() const
{
	return numSamples;
}