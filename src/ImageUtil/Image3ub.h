// Image3ub.h
#ifndef __Image3ub_H__
#define __Image3ub_H__

#include "Color3ub.h"
#include <string>
#include <stdexcept>

/* Intermediate image format. Stores RGB color array of 8-bit unsigned values.
 *  
 * The bottom left corner is represented as coordinate 0,0 while the top right corner is represented as x,y
 *
 */

class Image3ub
{
public:
    //
    // Type of pixels in an Image3ub.
    //
    typedef Color3ub Pixel;

    //
    // Construct a new image of the specified width and height,
    // filled completely with the specified pixel color.
    //
    Image3ub(int width, int height, Pixel color = Pixel(0,0,0));

    //
    // Delete and clean up an existing image.
    //
    ~Image3ub();

    //
    // Get the width (in pixels) of the image.
    //
    int GetWidth() const { return mWidth; }

    //
    // Get the height (in pixels) of the image.
    //
    int GetHeight() const { return mHeight; }

    //
    // Read a pixel value given its (x,y) location.
    //
    Pixel GetPixel(int x, int y) const;

	// Read a pixel value given two floats representing uv coordinates 0-1. Interpolates value.
	Color3f Interpolate(float u, float v) const;

    //
    // Write a pixel value given its (x,y) location.
    //
    void SetPixel(int x, int y, Pixel value);

	void Draw() const;

private:
    // Image height, in pixels.
    int mHeight;

    // Image width, in pixels.
    int mWidth;

    // An array of mWidth*mHeight pixels, stored in row-major
    // left-to-right, bottom-to-top order.
    Pixel* mPixels;

    //
    void Initialize(int width, int height);

};

#endif // __Image3ub_H__
