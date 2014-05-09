#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#include "../MathUtil/Matrix4f.h"
#include "../Shapes/Shape.h"

/*
 * Represents a shape, material, and its model transform.
 *
 */
class Material;

class SceneObject
{
public:
	//SceneObject();
	SceneObject(Shape*, Material*, const Matrix4f&);
	~SceneObject(void);

	Shape * s; // Shape before applying transform
	Material * m;

	Matrix4f t;

};

#endif // SCENEOBJECT_H
