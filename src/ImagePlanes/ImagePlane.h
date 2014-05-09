#ifndef __IMAGEPLANE_H__
#define __IMAGEPLANE_H__

#include <string>
#include "../MathUtil/RTMath.h"

/*
Represents image plane
*/

class ImagePlane
{
public:
	ImagePlane();
	ImagePlane(int, int);
	~ImagePlane(void);

	int getWidthSamples() const;
	int getHeightSamples() const;

private:
	// Resolution of output image
	int imgWidth, imgHeight;

	int width, height;

};

#endif // __IMAGEPLANE_H__
