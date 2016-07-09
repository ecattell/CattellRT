#include "Shape.h"

Shape::Shape(void)
{
}


Shape::~Shape(void)
{
}

void Shape::setSceneObject(SceneObject* _parent)
{
	parent = _parent;
}

SceneObject* Shape::getSceneObject()
{
	return parent;
}

BoundingBox* Shape::getBbox()
{
	return bbox;
}
