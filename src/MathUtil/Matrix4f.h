#ifndef __MATRIX4F_H__
#define __MATRIX4F_H__

#include "Vec3f.h"

/*
 * Simple 4x4 float Matrix class used for transforming objects.
 */

class Matrix4f
{
public:

	// Constructors
	Matrix4f();
	Matrix4f(const Matrix4f& t);

	// Assignment
	Matrix4f& operator = (const Matrix4f& t);

	// Element access
	inline const float* operator [] (int row) const
	{
		return _Entries[row];
	}
	inline float* operator [] (int row)
	{
		return _Entries[row];
	}

	// Transformations
	static Matrix4f Identity();
	static Matrix4f Translation(float tx, float ty, float tz);
	static Matrix4f Scaling(float sx, float sy, float sz);
	static Matrix4f Rotation(float rx, float ry, float rz);

	Matrix4f Inverse() const;

	// Arithmetic
	static Vec3f vecMult(const Matrix4f& left, const Vec3f& right);
	static Vec3f pntMult(const Matrix4f& left, const Vec3f& right);
	Matrix4f& operator += (const Matrix4f& t);
	Matrix4f& operator -= (const Matrix4f& t);
	Matrix4f& operator *= (const Matrix4f& t);
	Matrix4f& operator *= (float s);
	Matrix4f& operator /= (float s);

	// linear algebra: determinant, transpose, inverse (copy from matt's code)
	// Linear Algebra

    Matrix4f Transpose() const;

private:
	float _Entries[4][4];
};

// Non in-place arithmetic operators
Matrix4f operator * (const Matrix4f& left, const Matrix4f& right);
Matrix4f operator * (const Matrix4f& left, float right);
Matrix4f operator * (float left, const Matrix4f& right);
Matrix4f operator / (const Matrix4f& left, float right);
Matrix4f operator + (const Matrix4f& left, const Matrix4f& right);
Matrix4f operator - (const Matrix4f& left, const Matrix4f& right);
//STVector3 operator * (const Matrix4f& left, const STVector3& right);
//STPoint3 operator * (const Matrix4f& left, const STPoint3& right);

#endif

