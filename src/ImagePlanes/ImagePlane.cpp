#include "ImagePlane.h"

// TODO: do I need this const?
ImagePlane::ImagePlane(int _imgWidth, int _imgHeight)
{
	imgWidth = _imgWidth;
	imgHeight = _imgHeight;
}

ImagePlane::ImagePlane(void)
{
}

ImagePlane::~ImagePlane(void)
{
}

int ImagePlane::getWidthSamples() const
{
	return imgWidth;
}

int ImagePlane::getHeightSamples() const
{
	return imgHeight;
}
