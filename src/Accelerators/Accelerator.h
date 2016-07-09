#ifndef __ACCELERATOR_H__
#define __ACCELERATOR_H__

#include <vector>
#include <algorithm>
#include "../Objects/SceneObject.h"

/*
 * A bounding box hierarchy accelerator structure 
 */
class Accelerator
{
	public:
		Accelerator(std::vector<SceneObject*> & _objects);
		Accelerator();
		virtual ~Accelerator(void);

		virtual Intersection* hit(const Ray& r) =0;
};
#endif // __ACCELERATOR_H__
