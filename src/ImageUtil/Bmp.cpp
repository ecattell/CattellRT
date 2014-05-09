// Bmp.cpp

#include "Bmp.h"

#define ERROR_COLOR Color3ub(255,0,255)
#define ERROR_IMAGE Image3ub(10,10,ERROR_COLOR)
#define HEADER_SIZE 54
#define NUM_CHANNELS 3
#define PADDING 4 // Pad row size to multiple of x bytes
#define BITS_PER_CHANNEL 8

// Reads 24-bit BMP file
Image3ub* Bmp::readBmp(const std::string& fn)
{
	char *fileName = new char[fn.length() + 1]; // TODO: Tiny memory leak. fileName never deleted
	strcpy(fileName, fn.c_str());

	FILE* file = fopen(fileName, "r");

	if(file==NULL) {
		return error(fn, "File could not be found.");
	}

	// Read header - 54 bytes
	unsigned char header[HEADER_SIZE];

	fread(header, 1, HEADER_SIZE, file); // read the 54-byte header
	if (header == NULL)
	{
		return error(fn, "Memory error.\n");
	}

	// Check if file is a BMP
	if (header[0] != 'B' || header[1] != 'M') {
		return error(fn, "File is not a BMP.");
	}

	// Read file size
	unsigned int fileSize = readInt(&header[2]);

	// Check if the file is a V3 BMP.
	unsigned int offset = readInt(&header[10]);
	if (offset != HEADER_SIZE) {
		return error(fn, "File is not a compatible V3 BMP.");
	}

	// Extract image width and height
	unsigned int width = readInt(&header[18]);
    unsigned int height = readInt(&header[22]);

	// Check number of color planes
	unsigned short numColorPlanes = readInt(&header[26]);
	if (numColorPlanes != 1) {
		return error(fn, "BMP is limited to one image plane.");
	}

	// Check if file has 24-bit color
	short bitsPerPixel = readInt(&header[28]);
	if (bitsPerPixel != BITS_PER_CHANNEL*NUM_CHANNELS) {
		return error(fn, "BMP must have 24-bit color.");
	}

	// Check if file is right size / expected file size
	unsigned int rowSize = width*NUM_CHANNELS; // Compute row size
	rowSize = ( (rowSize+PADDING-1)/PADDING) * PADDING; // Account for padding
	unsigned int expectedSize = HEADER_SIZE + rowSize * height;
	if (expectedSize != fileSize) {
		return error(fn, "File corrupt.\n");
	}

	// Put pixel data in buffer

	unsigned char* imageBuffer = new unsigned char [rowSize * height];
	if (imageBuffer == NULL)
	{
		return error(fn, "Memory error.\n");
	}

	unsigned int readSize = fread(imageBuffer, 1, fileSize - HEADER_SIZE, file);

	if (readSize != fileSize-HEADER_SIZE) {
		return error(fn, "File corrupt.\n");
	}

	fclose(file);

	// Put pixel data in texture

	Image3ub* texture = new Image3ub(width,height,ERROR_COLOR); // TODO: Is it bad style to return a pointer here?
	
	int sizeOfPixel = (BITS_PER_CHANNEL*NUM_CHANNELS)/8;
	
	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; y < height; y++)
		{

			unsigned char r = imageBuffer[sizeOfPixel*x+(BITS_PER_CHANNEL/8)*2+y*rowSize];
			unsigned char g = imageBuffer[sizeOfPixel*x+BITS_PER_CHANNEL/8+y*rowSize];
			unsigned char b = imageBuffer[sizeOfPixel*x+y*rowSize];
			

			Color3ub col = Color3ub(r,g,b);
			//std::cout << "(" << x << ","<< y << ")" << ":" << (short)r << "|" << (short)g << "|" << (short)b << "\n";
			texture->SetPixel(x,y,col); // TODO: should this be x and y? which corner is which?
		}
	}
	
	delete[] imageBuffer;
	return texture;
}

Image3ub* Bmp::error(const std::string& fn, const std::string& message)
{
	std::cout << "Coud not read texture file: " << fn << "\n" << message << "\n";
	return new ERROR_IMAGE; // Return magenta if texture not readable
}

inline int Bmp::readInt(unsigned char* address)
{
	return *(int*)address;
}

// TODO: Unused. This is for Bmp writer
void Bmp::writeFileHeader()
{
	// bfType 
	// WORD (16-bit)
	// Specifies that file is BMP
	//write16(0x4D42);

	// bfSize
	// DWORD (32-bit)
	// Size in bytes of the bitmap
	//int size = 54 + w*h*3;
	//write32(size);

	// bfReserved1
	// WORD (16-bit)
	// Reserved. Unused.
	//writeBuffer(); // Write 0x0000

	// bfReserved2
	// WORD (16-bit)
	// Reserved. Unused.
	//writeBuffer(); // Write 0x0000

	// bfOffBits
	// DWORD (32-bit)
	// File offset to PixelArray
	//int offset = ;
	//write32(offset) ;

}
