#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Shape.h"

#include <float.h>

#include "../MathUtil/RTUtil.h"
typedef Vec3f Pnt3f;

// A simple triangle which extends the shape class.

class Triangle :
	public Shape
{
	public:
		Triangle(const Pnt3f& _a, const Pnt3f& _b, const Pnt3f& _c, const Matrix4f& t, float _ua = 0, float _va = 0, float _ub = 0, float _vb = 1, float _uc = 1, float _vc = 0);
		Triangle(float, float, float, float, float, float, float, float, float, const Matrix4f&, float _ua = 0, float _va = 0, float _ub = 0, float _vb = 1, float _uc = 1, float _vc = 0);
		~Triangle(void);
		Intersection* hit(const Ray&);
		void cacheBbox();

	private:
		// t1, t2, N
		Vec3f ab,ac,N; // Transformed vectors
		Pnt3f a,b,c; // Transformed points
		float ua, va, ub, vb, uc, vc; // Uv coordinates of each vertex

		void Initialize(const Matrix4f&);
		Vec3f computeNormal(const Pnt3f&, const Pnt3f&);

		float area;
	
	protected:
	
};

#endif // __TRIANGLE_H__
