#include "Sphere.h"
#include <iostream>

Sphere::Sphere(const Pnt3f& center, float radius, const Matrix4f& _t)
{
	cntr = Pnt3f(center);
	rad = radius;
	T = Matrix4f(_t);
	Ti = T.Inverse();
	Tti = Ti.Transpose();
	Tt = T.Transpose();
	cacheBbox();
}

Sphere::~Sphere(void)
{
}

// Detects if ray intersects sphere.
// TODO: Manage special case for transformed spheres by transforming vector.
Intersection* Sphere::hit(const Ray& r)
{		
	// Transform vector to use inverse of sphere's transformation matrix

	Vec3f e = Matrix4f::pntMult(Ti,r.e);
	Vec3f d = Matrix4f::vecMult(Ti,r.d);

	// Calculate coefficients of quadratic
	//Isn't this always 1?
	float a = Vec3f::Dot(d,d);
	float b = Vec3f::Dot(2*d,e-cntr);
	float c = Vec3f::Dot(e-cntr,e-cntr)-pow(rad,2);

	float discriminant = b*b-4*a*c;

	if (discriminant<0)
	{
		return NULL;
	}
	float t = RTMin((-b + sqrt(discriminant))/(2*a),(-b - sqrt(discriminant))/(2*a));

	Pnt3f p = Matrix4f::pntMult(T,e+t*d); // transform point  back to world coordinates
	Vec3f n = Matrix4f::vecMult(Tti,(p-cntr)/rad); // transform normal back to world coordinates
	n.Normalize();

	if (!SameDirection(d,n)) return NULL;  // Backface culling
	
	if (t > r.max || t < r.min) return NULL; // check range
	return new Intersection(t, p, n, parent);
}

void Sphere::cacheBbox()
{	
	float minX = cntr.x-rad;
	float minY = cntr.y-rad;
	float minZ = cntr.z-rad;
	
	float maxX = cntr.x+rad;
	float maxY = cntr.y+rad;
	float maxZ = cntr.z+rad;

	Pnt3f minPnt = Pnt3f(minX, minY, minZ);
	Pnt3f maxPnt = Pnt3f(maxX, maxY, maxZ);

	this->bbox = new BoundingBox(minPnt, maxPnt);
}
