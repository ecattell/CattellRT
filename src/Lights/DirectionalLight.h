#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#include <float.h>

#include "Light.h"
#include "../MathUtil/Vec3f.h"

/*
 * Light type which represents a directional light. Light has no position. It is assumed to be infinitely far away.
 */

class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const Vec3f&, const Color3f&);
	virtual ~DirectionalLight(void);
	const Vec3f getDir(const Pnt3f&);
	const Vec3f getDir();
	const float getDist(const Pnt3f&);

private:
	// Direction of light
	Vec3f direction; 

	// Precomputed inverse of direction used to reduce lighting calculations
	Vec3f inverseDirection; 
};

#endif // __DIRECTIONALLIGHT_H__
