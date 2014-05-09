#include "SceneObject.h"



SceneObject::SceneObject(Shape * _s, Material * _m, const Matrix4f& _t)
	: s(_s)
	, m(_m)
	, t(_t)
{
}


SceneObject::~SceneObject(void)
{
	delete s;
}