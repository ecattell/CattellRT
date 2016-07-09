#include "SimpleAccelerator.h"
#include <iostream>

// Constructor
SimpleAccelerator::SimpleAccelerator(std::vector<SceneObject*> & _objects)
{
	std::vector<SceneObject*> objects = _objects;
}

SimpleAccelerator::SimpleAccelerator()
{
}

// Destructor
SimpleAccelerator::~SimpleAccelerator(void)
{
	//TODO
}

// Detects if ray intersects bvh. If no collision, returns NULL.
Intersection* SimpleAccelerator::hit(const Ray& r)
{
	Intersection* i = NULL;
	for(std::vector<SceneObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {


		Shape * currShape = (*it)->s;
		Intersection* currIntersect = currShape->hit(r);
		// TODO: triangle already does this check. make sphere do this check and you can ignore it.
		// if intersect hits something AND is within the min and max range of the ray
		if(currIntersect != NULL && currIntersect->t < r.max && currIntersect->t > r.min)
		{
			// if intersect is closer than previous closest intersect, update previous
			if (i == NULL || currIntersect->t < i->t)
			{
				delete i;
				i = currIntersect;
			}
			else delete currIntersect;
		}
		else delete currIntersect;
	}
	return i;
}
