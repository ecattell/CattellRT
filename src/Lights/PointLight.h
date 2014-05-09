#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"

/*
 * Light type which represents a point light.
 */


class PointLight :
	public Light
{
public:
	PointLight(const Pnt3f&, const Color3f&);
	PointLight(float, float, float, const Color3f&);
	virtual ~PointLight(void);
	const virtual Vec3f getDir(const Pnt3f&);
	Pnt3f loc;

private:
};

#endif //__POINTLIGHT_H__
