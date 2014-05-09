#ifndef __MATRIXSTACK_H__
#define __MATRIXSTACK_H__

#include "../MathUtil/RTMath.h"
#include "../MathUtil/Matrix4f.h"

// Represents a matrix in the transform matrix stack

struct MatrixElement{
	Matrix4f T;
	MatrixElement * prev;
	MatrixElement(Matrix4f _T, MatrixElement * _prev)
	{
		T = _T;
		prev = _prev;
	}
	
	MatrixElement()
	{
		T = Matrix4f();
		prev = NULL;
	}
};

// Transform matrix stack

class MatrixStack
{
public:
	MatrixStack(void);
	~MatrixStack(void);
	
	void push(const Matrix4f&);
	void push(); // Duplicates top element and pushes to top of stack
	void pop(); // Does NOT return the top element, since this has no use for frontend

	void multiply(const Matrix4f&);
	void translate(float, float, float);
	void scale(float, float, float);
	void rotate(float, float, float);
	void loadIdentity();
	void replace(const Matrix4f&);
	const Matrix4f& getTop();

protected:
		MatrixElement * top;
};

#endif //__MATRIXSTACK_H__
