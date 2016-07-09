#ifndef __SIMPLE_ACCELERATOR_H__
#define __SIMPLE_ACCELERATOR_H__

#include <vector>
#include <algorithm>

#include "Accelerator.h"
#include "../Objects/SceneObject.h"
#include "../BoundingVolumes/BoundingBox.h"

/*
 * A bounding box hierarchy accelerator structure 
 */
class SimpleAccelerator :
	public Accelerator
{
	public:
		SimpleAccelerator(std::vector<SceneObject*> & _objects);
		SimpleAccelerator();
		~SimpleAccelerator(void);

		Intersection* hit(const Ray& r);

	protected:
		std::vector<SceneObject*> objects;
};
#endif // __SIMPLE_ACCELERATOR_H__
