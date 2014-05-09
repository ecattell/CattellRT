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

}; 

#endif // __LIGHT_H__
