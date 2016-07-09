#include "Camera.h"

Camera::Camera(const Pnt3f& _loc, const Vec3f& _up, const Pnt3f& _look, float _fovy, float _aspect)
	: loc(_loc)
	, up(_up)
{
	lookAt = (_look-loc); // TODO: Positive or negative?
	aspect = _aspect;

	// Convert vertical FOV to radians
	fovy = _fovy * (M_PI/180.0);

	// Calculate horizontal FOV from vertical FOV
	fovx = 2*atan(aspect*tan(fovy/2));

	// Calculate unit vectors for UVW coordinate space
	W = Vec3f(lookAt);
	V = Vec3f(up);
	W.Normalize();
	V.Normalize();
	U = Vec3f::Cross(W,V);

	width = 2*tan(fovx/2);
	height = 2*tan(fovy/2);

	DOF = false;
	numDOFSamples = 1;

}

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

Pnt3f Camera::getPos() const {return loc;}
Pnt3f Camera::getLookDir() const {return lookAt;}
Vec3f Camera::getUp() const {return up;}
float Camera::getFovY() const {return fovy;}
float Camera::getFovX() const {return fovx;}
float Camera::getAspect() const {return aspect;}
short Camera::getSamples() const {return numDOFSamples;}

void Camera::Initialize(int imgWidth, int imgHeight)
{
	pixWidth = imgWidth;
	pixHeight = imgHeight;
	pixelHeight = 2*tan(fovy/2)*1/imgHeight;
	pixelWidth = 2*tan(fovx/2)*1/imgWidth;
	upperLeftCorner = loc + W - (imgWidth/2)*pixelWidth*U - (imgHeight/2)*pixelHeight *V + (pixelWidth/2)*U + (pixelHeight/2)*V; // last two expressions used to center pixel
}

void Camera::setFocus(short _numDOFSamples, float _apertureSize, const Pnt3f& _focusPoint)
{
	DOF = true;
	numDOFSamples = _numDOFSamples;
	apertureSize = _apertureSize;
	focusDistance = Vec3f(_focusPoint-loc).Length();
	
	// Size of a sub-area inside the box formed by aperture size. This is used for stratified sampling, and is precomputed.
	DOFPixWidth = apertureSize/numDOFSamples;
	DOFPixHeight = DOFPixWidth; // I differentiated pixHeight and pixWidth to allow for expansion with non-square aperture.
}

void Camera::setFocusPoint(Pnt3f& _focusPoint)
{
	focusDistance = Vec3f(_focusPoint-loc).Length();
}

// Should this be in a different class?
Ray Camera::generateViewRay(float x, float y)
{
		
	Pnt3f destination = upperLeftCorner + x*pixelWidth*U + y*pixelWidth*V;

	Pnt3f s = destination; // Convert from uvw space to xyz
	Pnt3f e = loc;
	Vec3f dir = (s-e);
	dir.Normalize();

	return Ray(e, dir, 1, FLT_MAX);
}

Ray Camera::defocusRay(Ray& ray, int i, int j)
{	
	Pnt3f aim = ray.e+ray.d*focusDistance;

	// Stratified sampling
	float xJitter = DOFPixWidth*i + (randFloat()-1)*DOFPixWidth;
	float yJitter = DOFPixHeight*j + (randFloat()-1)*DOFPixHeight;
	
	// Jitter start position
	Pnt3f newOrigin = Pnt3f(ray.e.x + xJitter, ray.e.y + yJitter, ray.e.z);

	// Recalculate direction
	Vec3f newDir = aim-newOrigin;

	// Renormalize
	newDir.Normalize();

	return Ray(newOrigin,newDir,ray.min,ray.max);
}

void Camera::Pan(Pnt3f& _look)
{
	lookAt = (_look-loc);
	W = Vec3f(lookAt);
	W.Normalize();
	U = Vec3f::Cross(W,V);
	upperLeftCorner = loc + W - (pixWidth/2)*pixelWidth*U - (pixHeight/2)*pixelHeight *V + (pixelWidth/2)*U + (pixelHeight/2)*V; // last two expressions used to center pixel

}

void Camera::Move(Pnt3f& _loc)
{
	loc = Pnt3f(_loc);
	upperLeftCorner = loc + W - (pixWidth/2)*pixelWidth*U - (pixHeight/2)*pixelHeight *V + (pixelWidth/2)*U + (pixelHeight/2)*V; // last two expressions used to center pixel
}
