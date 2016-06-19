#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "../MathUtil/RTMath.h"
#include "../MathUtil/Vec3f.h"
typedef Vec3f Pnt3f;
#include "../ImageUtil/Color3f.h"

/*
 * Base class for lights. Inherited by other light classes (e.g. AmbientLight, AreaLight, DirectionalLight, and PointLight)
 */

class Light
{

protected:
	Light(void);

public:
	virtual ~Light(void);
	Color3f color;
	const virtual Vec3f getDir(const Pnt3f&);//  = 0;
	const virtual float getDist(const Pnt3f&);// = 0;

}; 

#endif // __LIGHT_H__
