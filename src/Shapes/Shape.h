#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "../MathUtil/RTMath.h"
#include "../Ray/Ray.h"
#include "../Ray/Intersection.h"
#include <math.h>

class SceneObject;

/*
 * An abstract class that represents a geometric primitive.
 * Used to calculate collisions of objects with rays.
 */
class Shape
{
protected:
	SceneObject* parent;

public:
	virtual Intersection* hit(const Ray&) =0;

	Shape(void);
	virtual ~Shape(void);

	void setSceneObject(SceneObject*);
	SceneObject* getSceneObject();
};

#endif // __SHAPE_H__
