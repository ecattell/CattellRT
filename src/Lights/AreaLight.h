#ifndef __AREALIGHT_H__
#define __AREALIGHT_H__

#include "Light.h"
#include "../MathUtil/RTUtil.h"

/*
 * Light type which represents an area light. Sampled multiple times to calculate area light through monte carlo integration.
 */

class AreaLight :
	public Light
{
public:
	// TODO Possible expansion: implement circular and rectangular area lights as subclasses
	AreaLight();
	AreaLight(const Pnt3f&, const Vec3f&, const Vec3f&, const Color3f&, short numSamples, float _falloff);
	~AreaLight(void);
	Pnt3f getRandomPos(int i, int k) const;
	short getNumSamples() const;

	// Controls how quickly light falls off over distance
	float falloff;

private:
	
	// Point determining location of light
	Pnt3f lightCorner;

	// Vector forming first edge of parallelogram
	Vec3f vec1;

	// Vector forming second edge of parallelogram
	Vec3f vec2;

	short numSamples;
	float numSamplesInverse; // Precomputed and used for stratified sampling. This is essentially the width/height of a sample area along the vector
};
#endif //__AREALIGHT_H__
