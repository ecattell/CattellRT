#include "BVH.h"
#include <iostream>

// Constructors

/*
BVH::BVH(std::vector<SceneObject*>& objects)
{
	BVH(objects, 'x');
}*/

BVH::BVH(std::vector<SceneObject*> & objects, char axis)
{
	// Build bounding box around all objects	
	bbox = new BoundingBox( objects );

	if (objects.size() == 1 )
	{
		// this is a leaf
		leftChild  = NULL;
		rightChild = NULL;
		object     = objects[0];
	}
	else
	{
		// We don't store objects on non-leaf nodes
		object = NULL;
		
		// Sort objects by position on axis using center of bounding box
		if (axis == 'x') {std::sort(objects.begin(), objects.end(), sortByX);}
		if (axis == 'y') {std::sort(objects.begin(), objects.end(), sortByY);}
		if (axis == 'z') {std::sort(objects.begin(), objects.end(), sortByZ);}
			
		// Put objects into left and right buckets based on position
		std::size_t const midpoint = objects.size() / 2;
		std::vector<SceneObject*> leftObjects(objects.begin(), objects.begin() + midpoint);
		std::vector<SceneObject*> rightObjects(objects.begin() + midpoint, objects.end());
			
		// Advance axis for next iteration
		char newAxis = axis++;
		if (axis > 'z') { axis = 'x'; }
		
		// Insert tree node with half of objects on left and half on right
		if (leftObjects.size() > 0 ) leftChild  = new BVH(leftObjects, newAxis);
		else { leftChild = NULL; }
		
		if (rightObjects.size() > 0 ) rightChild = new BVH(rightObjects, newAxis);
		else { rightChild = NULL; }
	}
}

BVH::BVH()
{
	leftChild = NULL;
	rightChild = NULL;
}

// Destructor
BVH::~BVH(void)
{
	//TODO
}

// Sorting variations (alternates between these)
bool BVH::sortByX(const SceneObject* i, const SceneObject* j) {return i->s->bbox->center.x > j->s->bbox->center.x;}
bool BVH::sortByY(const SceneObject* i, const SceneObject* j) {return i->s->bbox->center.y > j->s->bbox->center.y;}
bool BVH::sortByZ(const SceneObject* i, const SceneObject* j) {return i->s->bbox->center.z > j->s->bbox->center.z;}

// Detects if ray intersects bvh. If no collision, returns NULL.
Intersection* BVH::hit(const Ray& r)
{
	if (object != NULL)
	{
		// Handle leaf nodes
		return object->s->hit(r);
	}
	else
	{
		// Handle other nodes
		// Check if the bounding box was hit
		if ( bbox->rayCollides(r) )
		{
			Intersection* leftHit  = leftChild->hit(r);
			Intersection* rightHit = rightChild->hit(r);
			
			if (leftHit != NULL)
			{
				// Check if both hit
				if (rightHit != NULL)
				{
					if (leftHit->t < rightHit->t)
					{
						delete rightHit;
						return leftHit;
					}
					else
					{
						delete leftHit;
						return rightHit;
					}
				}
				// Only the left box was hit
				else
				{
					delete rightHit;
					return leftHit;
				}
			}
			// Only the right box was hit
			else if (rightHit != NULL)
			{
				delete leftHit;
				return rightHit;
			}
			// The outer bounding box was hit, but neither children were
			else
			{
				delete leftHit;
				delete rightHit;
				return NULL;
			}
		}
		// The bounding box was not hit
		else
		{
			return NULL;
		}
	}
}
