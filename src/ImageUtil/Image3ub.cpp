// Image3ub.cpp
#include "Image3ub.h"

//#include "Displays/OpenGL.h"

#include <assert.h>
#include <stdio.h>
#include <string>


//
// Construct a new image of the specified width and height,
// filled completely with the specified pixel color.
//
Image3ub::Image3ub(int width, int height, Pixel color)
{
    Initialize(width, height);

    int numPixels = mWidth * mHeight;
    for (int ii = 0; ii < numPixels; ++ii) {
        mPixels[ii] = color;
    }
}

// Common initialization logic shared by all construcotrs.
void Image3ub::Initialize(int width, int height)
{
    if (width <= 0)
        throw std::runtime_error("Image3ub width must be positive");
    if (height <= 0)
        throw std::runtime_error("Image3ub height must be positive");

    mWidth = width;
    mHeight = height;

    int numPixels = mWidth * mHeight;
    mPixels = new Pixel[numPixels];
}

//
// Delete and clean up an existing image.
//
Image3ub::~Image3ub()
{
    if (mPixels != NULL) {
        delete [] mPixels;
    }
}

//
// Read a pixel value given its (x,y) location.
//
Image3ub::Pixel Image3ub::GetPixel(int x, int y) const
{
    // Check that (x,y) is in range.
    assert(x >= 0 && x < mWidth);
    assert(y >= 0 && y < mHeight);

    return mPixels[y*mWidth + x];
}

Color3f Image3ub::Interpolate(float u, float v) const
{

    // Check that the (u,v) coordinates are in range.
    assert(u >= 0 && u <= 1);
    assert(v >= 0 && v <= 1);

	float x = u*mWidth;
	float y = v*mHeight;

	// TODO: Do I need to use min/max here (prevents floating point arithmetic from giving negative or too large indices)?
	int xFloor = std::max((int)x,0);
	int yFloor = std::max((int)y,0);
	int xCeil = std::min(xFloor+1,mWidth-1);
	int yCeil = std::min(yFloor+1,mHeight-1);

	float xDif = xCeil-x;
	float yDif = yCeil-y;

	Color3f topLeft = Color3f(mPixels[yCeil*mWidth + xCeil]);
	Color3f topRight = Color3f(mPixels[yCeil*mWidth + xFloor]);
	Color3f bottomLeft = Color3f(mPixels[yFloor*mWidth + xCeil]);
	Color3f bottomRight = Color3f(mPixels[yFloor*mWidth + xFloor]);

	// Bilinear interpolation. TODO: Make this a utility function
	Color3f top = Color3f::lerp(topLeft,topRight,xDif);
	Color3f bottom = Color3f::lerp(bottomLeft,bottomRight,xDif);
	Color3f yLerp = Color3f::lerp(top,bottom,yDif);
	
	return yLerp;
}


//
// Write a pixel value given its (x,y) location.
//
void Image3ub::SetPixel(int x, int y, Pixel value)
{
    // Check that (x,y) is in range.
    assert(x >= 0 && x < mWidth);
    assert(y >= 0 && y < mHeight);

    mPixels[y*mWidth + x] = value;
}

// TODO: Temporarily unused because of GLUT requirement
//
// Draw the image to the OpenGL window using glDrawPixels.
// The bottom-left of the image will align with (0.0, 0.0)
// in object space.
//
void Image3ub::Draw() const
{
	/*
    glRasterPos2f(0.0f, 0.0f);
    glDrawPixels(mWidth, mHeight,
                 GL_RGBA, GL_UNSIGNED_BYTE,
                 (GLvoid*) mPixels);
	*/
}
