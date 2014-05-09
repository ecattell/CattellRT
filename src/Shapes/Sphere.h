#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Shape.h"
#include "../MathUtil/RTUtil.h"

// A simple sphere which extends the shape class.

class Sphere :
	public Shape
{
public:
	Sphere(const Pnt3f&, float, const Matrix4f&);
	~Sphere(void);
	Intersection* hit(const Ray&);

private:
	Pnt3f cntr;
	float rad;
	Matrix4f T; // Transform matrix
	Matrix4f Ti; // Inverse of transform matrix
	Matrix4f Tt; // Transpose of transform matrix
	Matrix4f Tti; // Transpose of inverse transform matrix
	// boundingBox (min,max) // Vec3f min = center - Vec3f(radius,radius,radius) // Vec3f max = center + Vec3f(radius,radius,radius)
};

#endif // __SPHERE_H__
