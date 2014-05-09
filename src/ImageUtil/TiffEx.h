// TiffEx.h
#ifndef __TIFFEX_H__
#define __TIFFEX_H__

#include "Image3ub.h"
#include <cstring>
#include <stdio.h>
#include <iostream>
/*

Exports an uncompressed TIF file using an Image3ub

*/


class TiffEx
{
private:
	static void writeHeader(const Image3ub& image, FILE * s);
	static void writeBody(const Image3ub& image, FILE * s);
	static void writeFooter(const Image3ub& image, FILE * s);
	static void writeWord(unsigned int word, FILE * s);
	static void writeBytePair(unsigned short word, FILE * s);
	static void writeBuffer(FILE * s);

	static void writeIFDEntry(unsigned short hexTag, unsigned short fieldType, unsigned int value, FILE * s);
	static void writeIFDEntry(unsigned short hexTag, unsigned short fieldType, unsigned int numValues, unsigned int value, FILE * s);
	static void writeIFDEntry(unsigned short hexTag, unsigned short fieldType, unsigned int numValues, unsigned short value1, unsigned short value2, FILE * s);


public:
	static void generateTiff(const Image3ub& image, const std::string& fileName);

};

#endif //__TIFFEX_H__
