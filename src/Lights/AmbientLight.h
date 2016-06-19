#ifndef __AMBIENTLIGHT_H__
#define __AMBIENTLIGHT_H__

#include "Light.h"

/*
 * Light type which gives equal illumination to all surfaces regardless of orientation or position.
 */

class AmbientLight :
	public Light
{
public:
	AmbientLight(const Color3f&);
	virtual ~AmbientLight(void);
	const Vec3f getDir(const Pnt3f&);
	const float getDist(const Pnt3f&);
};

#endif
