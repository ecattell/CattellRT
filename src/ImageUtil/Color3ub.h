// Color3ub.h
#ifndef __COLOR3UB_H__
#define __COLOR3UB_H__

// Forward-declare libst types.
#include "Color3f.h"

/**
*  8-bits per channel RGB color.
*  Accepts values [0, 255]
*/
struct Color3ub
{
public:
    typedef unsigned char Component;
    Component r, g, b, a;

    /* Constructors */
    Color3ub();
    Color3ub(const Color3ub& c);
    Color3ub(Component r, Component g, Component b);
    explicit Color3ub(const Color3f& c);
};



#endif //__COLOR3UB_H__

