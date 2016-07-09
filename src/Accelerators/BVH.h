#ifndef __BVH_H__
#define __BVH_H__

#include <vector>
#include <algorithm>

#include "Accelerator.h"
#include "../Objects/SceneObject.h"
#include "../BoundingVolumes/BoundingBox.h"

/*
 * A bounding box hierarchy accelerator structure 
 */
class BVH /*:
	public Accelerator*/
{
	public:
		//BVH(std::vector<SceneObject*> & objects);
		BVH(std::vector<SceneObject*> & objects, char axis);
		BVH();
		~BVH(void);

		Intersection* hit(const Ray& r);
		static bool sortByX(const SceneObject* i, const SceneObject* j);
		static bool sortByY(const SceneObject* i, const SceneObject* j);
		static bool sortByZ(const SceneObject* i, const SceneObject* j);

	protected:
		SceneObject* object;
		BoundingBox* bbox;
		BVH* leftChild;
		BVH* rightChild;
};

#endif // __BVH_H__
