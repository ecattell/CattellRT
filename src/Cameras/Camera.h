#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "math.h"
#include "float.h"
#include <iostream>
#include "../Ray/Ray.h"
#include "../MathUtil/RTMath.h"
#include "../MathUtil/Vec3f.h"
#include "../MathUtil/RTUtil.h"

/*
Represents the virtual scene camera.
Generates viewing rays to a point on the image plane.
*/

class Camera
{
public:
	Camera();
	Camera(const Pnt3f&, const Vec3f&, const Pnt3f&, float, float);
	virtual ~Camera(void);
	void Initialize(int imgWidth, int imgHeight);

	// Get camera placement information
	Pnt3f getPos() const;
	Pnt3f getLookDir() const;
	Vec3f getUp() const;
	
	// Get vertical FOV in radians
	float getFovY() const;

	// Get horizontal FOV in radians
	float getFovX() const;

	// Aspect ratio
	float getAspect() const;

	// Get number of DOF samples
	short getSamples() const;

	// Move the camera
	void Move(Pnt3f&);
	void Pan(Pnt3f& lookAt);

	// Generate and manipulate rays
	Ray generateViewRay(float, float);
	Ray defocusRay(Ray& before, int, int);

	// Change focus settings
	void setFocus(short _numDOFSamples, float _apertureSize, const Pnt3f& _focusPoint);
	void setFocusPoint(Pnt3f& _focusPoint);

	float width,height;
	int pixWidth,pixHeight;

	// DOF settings
	short numDOFSamples;
	float apertureSize;
	float focusDistance;
	bool DOF; // DOF enabled

private:
	Pnt3f loc; // Camera position
	Vec3f lookAt;
	Vec3f up; // Up vector
	float fovy; // Vertical field of view in radians
	float fovx; // Horizontal field of view in radians
	float aspect; // Aspect ratio
	Vec3f U,V,W;
	float pixelHeight, pixelWidth;
	Pnt3f upperLeftCorner;
	float DOFPixWidth,DOFPixHeight; // Size of a sub-area inside the box formed by aperture size. This is used for stratified sampling, and is precomputed.
};

#endif //__CAMERA_H__
