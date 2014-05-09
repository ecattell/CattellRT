#include "Triangle.h"
#include <iostream>

Triangle::Triangle(const Pnt3f& _a, const Pnt3f& _b, const Pnt3f& _c, const Matrix4f& t, float _ua, float _va, float _ub, float _vb, float _uc, float _vc)
{
	a = _a;
	b = _b;
	c = _c;

	ua = _ua;
	va = _va;
	ub = _ub;
	vb = _vb;
	uc = _uc;
	vc = _vc;

	Initialize(t);
}


Triangle::Triangle(float px, float py, float pz, float qx, float qy, float qz, float rx, float ry, float rz, const Matrix4f& t, float _au, float _uv, float _bu, float _bv, float _cu, float _cv)
{
	a = Pnt3f(px,py,pz);
	b = Pnt3f(qx,qy,qz);
	c = Pnt3f(rx,ry,rz);
	
	Initialize(t);
}



// Functions all constructors have in common
void Triangle::Initialize(const Matrix4f& t)
{
	a = Matrix4f::pntMult(t,a);
	b = Matrix4f::pntMult(t,b);
	c = Matrix4f::pntMult(t,c);

	ab = b - a;
	ac = c - a;

	// TODO: Is this ever used now that I changed program?
	// Small optimization. Precomputing area so that it doesn't need to be recalculated in later steps
	area = Vec3f::Cross(ab,ac).Length()/2;

	// Precompute normal, since we're not interpolating between vertices
	N = Vec3f::Cross(ab,ac);
	N.Normalize();
}

Triangle::~Triangle(void)
{
}

// Detects if ray intersects triangle. If no collision, returns NULL.
// OPTIMIZE TODO: Reuse computations where are done more than once.
// EXPANSION TODO I can represent vertices as a vertices struct instead of as points so that normals can be interpolated, etc
Intersection* Triangle::hit(const Ray& r)
{
	if (!SameDirection(r.d,N)) return NULL; // Don't return backface

	Intersection* i;

	// Compute barycentric coordinates

	// I could precompute these with the consequence of greater memory usage.
	float Aa = a.x - b.x;
	float Ab = a.y - b.y;
	float Ac = a.z - b.z;
	float Ad = a.x - c.x;
	float Ae = a.y - c.y;
	float Af = a.z - c.z;

	float Ag = r.d.x;
	float Ah = r.d.y;
	float Ai = r.d.z;
	
	float j = a.x - r.e.x;
	float k = a.y - r.e.y;
	float l = a.z - r.e.z;

	// Caching computations done multiple times
	float akjb = Aa*k - j*Ab; 
	float jcjl = j*Ac-Aa*l;
	float eihf = Ae*Ai-Ah*Af;
	float gfdi = Ag*Af-Ad*Ai;
	float blkc = Ab*l-k*Ac;
	float dheg = Ad*Ah - Ae*Ag;

	float M = Aa*(eihf) + Ab*(gfdi) + Ac*(dheg);
	
	// compute t
	float t = -( Af*(akjb) + Ae*(jcjl) + Ad*(blkc) ) / M;

	if (t < r.min || t > r.max) 
	{
			// No collision because triangle not between min and max of ray	
			i = NULL;
			return i;
	}

	float gamma = ( Ai*(akjb) + Ah*(jcjl) + Ag*(blkc) ) / M;

	if (gamma < 0 || gamma > 1)
	{
		// No collision		
		i = NULL;
		return i;
	}

	float beta = ( j*(eihf) + k*(gfdi) + l*(dheg) ) / M;
	
	if (beta < 0 || beta > 1 - gamma)
	{
		// No collision		
		i = NULL;
		return i;
	}

	
	// If we made it this far, then the ray intersects the triangle.
	
	// Calculate UV texture coordinates
	float u = ua + beta * (ub - ua) + gamma * (uc - ua);
	float v = va + beta * (vb - va) + gamma * (vc - va);

	// Return intersection struct
	i = new Intersection(t, r.e+t*r.d, N, parent, u, v);
	return i;
}