#include "Shape.h"
#include <iostream>

using namespace std;

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