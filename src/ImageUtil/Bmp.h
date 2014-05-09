// Bmp.h
#ifndef __BMP_H__
#define __BMP_H__

#include "Image3ub.h"
#include <cstring>
#include <stdio.h>
#include <iostream>
/*

Parses a V3 bmp file and returns an intermediate Image3ub

*/

class Bmp
{
private:
	static Image3ub* error(const std::string& fn, const std::string& message);
	static inline int readInt(unsigned char* address);
	static void writeFileHeader();

public:
	static Image3ub* readBmp(const std::string& fn);

};

#endif //__BMP_H__
