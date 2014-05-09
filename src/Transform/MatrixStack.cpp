#include "MatrixStack.h"


MatrixStack::MatrixStack(void)
{
	top = new MatrixElement(Matrix4f::Identity(),NULL);
}

// TODO: What's broken here?
MatrixStack::~MatrixStack(void)
{
	/*
		// iterate through every object and deallocate them
	MatrixElement* currElement = top;
	while (currElement != NULL)
	{
		MatrixElement* prevElement = currElement->prev;
		delete currElement;
		currElement = prevElement;
	}
	*/
}

// push new matrix to top of stack
void MatrixStack::push(const Matrix4f& T)
{
	MatrixElement* newPrev = top;
	top = new MatrixElement(T,newPrev);
}

// duplicates top element, push to top
void MatrixStack::push()
{
	Matrix4f topTransform = top->T;
	push(topTransform);
}

void MatrixStack::pop()
{
	MatrixElement * newTop = top->prev;
	delete top;
	top = newTop;
}

void MatrixStack::loadIdentity()
{
	top->T = Matrix4f::Identity();
}

const Matrix4f& MatrixStack::getTop()
{
	return top->T;
}

void MatrixStack::translate(float tx, float ty, float tz)
{
	multiply(Matrix4f::Translation(tx, ty, tz));
}

void MatrixStack::scale(float sx, float sy, float sz)
{
	multiply(Matrix4f::Scaling(sx, sy, sz));
}

// assumes radian input
void MatrixStack::rotate(float rx, float ry, float rz)
{
	multiply(Matrix4f::Rotation(rx, ry, rz));
}

void MatrixStack::multiply(const Matrix4f& _T)
{
	top->T = _T*top->T;
}

// Replaces top matrix with argument
void MatrixStack::replace(const Matrix4f& _T)
{
	top->T = _T;
}