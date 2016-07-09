#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include <vector>
#include <float.h>
#include <algorithm>

#include "../MathUtil/Vec3f.h"
#include "../Ray/Ray.h"
#include "../Objects/SceneObject.h"

/*
 * Represents a bounding box
 */
class BoundingBox
{
	public:
		BoundingBox(std::vector<SceneObject*> objects); // Create a bbox that encompasses multiple objects
		BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		BoundingBox(Pnt3f _minPnt, Pnt3f _maxPnt);
		~BoundingBox(void);
		bool rayCollides(const Ray& r);
		Pnt3f minPnt;
		Pnt3f maxPnt;
		Pnt3f center; // Caching this for now 
};

#endif // __BOUNDINGBOX_H__
