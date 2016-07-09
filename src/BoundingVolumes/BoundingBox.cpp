#include "BoundingBox.h"
#include <iostream>
#include <algorithm>

BoundingBox::BoundingBox(Pnt3f _minPnt, Pnt3f _maxPnt)
{
	minPnt = _minPnt;
	maxPnt = _maxPnt;
	
	float centerX = (minPnt.x + maxPnt.x)/2.0f;
	float centerY = (minPnt.y + maxPnt.y)/2.0f;
	float centerZ = (minPnt.z + maxPnt.z)/2.0f;
	center = Pnt3f(centerX, centerY, centerZ);
}

BoundingBox::BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	minPnt = Pnt3f(minX,minY,minZ);
	maxPnt = Pnt3f(maxX,maxY,maxZ);
}

BoundingBox::BoundingBox(std::vector<SceneObject*> objects)
{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	
	float maxX = -FLT_MAX;
	float maxY = -FLT_MAX;
	float maxZ = -FLT_MAX;
	

	// for object in objects
	for(std::vector<SceneObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		Shape * currShape = (*it)->s;
		BoundingBox* currBbox = currShape->getBbox();
		
		Pnt3f curMin = currBbox->minPnt;
		Pnt3f curMax = currBbox->maxPnt;
		if (curMin.x < minX) { minX = curMin.x; }
		if (curMin.y < minY) { minY = curMin.y; }
		if (curMin.z < minZ) { minZ = curMin.z; }
		if (curMax.x > maxX) { maxX = curMax.x; }
		if (curMax.y > maxY) { maxY = curMax.y; }
		if (curMax.z > maxZ) { maxZ = curMax.z; }
	}
	
	minPnt = Pnt3f(minX,minY,minZ);
	maxPnt = Pnt3f(maxX,maxY,maxZ);
}

// Destructor
BoundingBox::~BoundingBox(void)
{
	//TODO
}

// Returns boolean whether or not theres a hit
bool BoundingBox::rayCollides(const Ray& r)
{
	// Get t value for intersection with each plane
	float ta = (minPnt.x - r.e.x) * r.multInverseDir.x;
	float tb = (maxPnt.x - r.e.x) * r.multInverseDir.x;
	float tc = (minPnt.y - r.e.y) * r.multInverseDir.y;
	float td = (maxPnt.y - r.e.y) * r.multInverseDir.y;
	float te = (minPnt.z - r.e.z) * r.multInverseDir.z;
	float tf = (maxPnt.z - r.e.z) * r.multInverseDir.z;

	// Find largest/smallest t values
	float tmin = std::max(std::max(std::min(ta, tb), std::min(tc, td)), std::min(te, tf));
	float tmax = std::min(std::min(std::max(ta, tb), std::max(tc, td)), std::max(te, tf));

	
	// check if bounding box is behind ray
	if (tmax < 0)
	{
		return false;
	}
	// ray does not intersect
	else if (tmin > tmax)
	{
		return false;
	}
	// ray intersects!
	else
	{
		return true;
	}
}
