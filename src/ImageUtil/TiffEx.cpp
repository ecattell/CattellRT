// TiffEx.cpp

#include "TiffEx.h"

// Generates big endian TIFF file

// Generates 24-bit TIFF file and saves to filename
void TiffEx::generateTiff(const Image3ub& image, const std::string& fn)
{
	FILE * file;

	char *fileName = new char[fn.length() + 1];
	strcpy(fileName, fn.c_str());

	// TODO: Do I need to catch an exception here?
	file = fopen (fileName,"wb");

	if(file==NULL) {
		printf ( "Couldn't write file. Error code 1.\n" );
		return;
	}

	writeHeader(image, file);

	writeBody(image, file);

	writeFooter(image, file);

	if (ferror (file)) printf ("Couldn't write file. Error code 2.\n");

	if (fflush(file)) printf ( "Couldn't flush file\n" );

	fclose(file);
}

// Write 8 byte header
void TiffEx::writeHeader(const Image3ub& image, FILE * file)
{

	// Signifies big endian
	writeBytePair(0x4d4d, file);

	// Identifies as TIFF
	writeBytePair(0x002a, file);

	// Calculate offset to IFD
	unsigned int IFDOffset = image.GetWidth() * image.GetHeight() * 3 + 8;
	writeWord(IFDOffset, file);

}

// Writes 4 bytes
void TiffEx::writeWord(unsigned int word, FILE * file)
{
	// Masks word to remove and write one byte at a time
	// to make program run properly on both big endian and little endian systems
	putc((word & 0xff000000) / 16777216,file);
	putc((word & 0x00ff0000) / 65536,file);
	putc((word & 0x0000ff00) / 256,file);
	putc((word & 0x000000ff),file);
}

// Writes 2 bytes
void TiffEx::writeBytePair(unsigned short word, FILE * file)
{
	putc((word & 0xff00) / 256,file);
	putc((word & 0x00ff),file);
}

// Writes 2 byte buffer
void TiffEx::writeBuffer(FILE * file)
{
	writeBytePair(0,file);
}

// Writes image data to file
void TiffEx::writeBody(const Image3ub& image, FILE * s)
{
	//TODO cache GetWidth and GetHeight

	int height = image.GetHeight();
	int width = image.GetWidth();

	for (int y = height-1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{	
			Color3ub col = image.GetPixel(x,y);
			
			unsigned char red = col.r;
			putc(red,s);
	
			unsigned char green = col.g;
			putc(green,s);
				
			unsigned char blue = col.b;
			putc(blue,s);

		}
	}

}


// Writes IFD from int
void TiffEx::writeIFDEntry(unsigned short hexTag, unsigned short fieldType, unsigned int value, FILE * s)
{
	writeBytePair(hexTag,s);
	writeBytePair(fieldType,s);
	writeWord(value,s);
}

// Writes IFD from two ints
void TiffEx::writeIFDEntry(unsigned short hexTag, unsigned short fieldType, unsigned int numValues, unsigned int value, FILE * s)
{
	writeBytePair(hexTag,s);
	writeBytePair(fieldType,s);
	writeWord(numValues,s);
	writeWord(value,s);
}

// Writes 12 byte image file directory. Uses two unsigned shorts for value
void TiffEx::writeIFDEntry(unsigned short hexTag, unsigned short fieldType, unsigned int numValues, unsigned short value1, unsigned short value2, FILE * s)
{
	writeBytePair(hexTag,s);
	writeBytePair(fieldType,s);
	writeWord(numValues,s);
	writeBytePair(value1,s);
	writeBytePair(value2,s);
}

void TiffEx::writeFooter(const Image3ub& image, FILE * file)
{
	
	int imgWidth = image.GetWidth();
	int imgLength = image.GetHeight();

	// Write number of directory entries / meta data entries
	writeBytePair(14,file);

	// ImageWidth - Label 0100
	writeIFDEntry(0x0100,3,1,file);
	writeBytePair(imgWidth,file);
	writeBuffer(file);

	// ImageLength - Label 0101
	writeIFDEntry(0x0101,3,1,file);
	writeBytePair(imgLength,file);
	writeBuffer(file);

	// Bits per sample - Label 0102
	writeIFDEntry(0x0102,3,3,file);

	int offset = imgWidth * imgLength * 3 + 182;
	writeWord(offset,file);

	// Compression - Label 0103
   	// Uncompressed (1)
	writeIFDEntry(0x0103,3,1,1,0,file);

	// PhotometricInterpretation - Label 0106
	// RGB (2)
	writeIFDEntry(0x0106,3,1,2,0,file);

	// Strip Offsets - Label 0111
	writeIFDEntry(0x0111,4,1,8,file);

	// Orientation - Label 0112 - OPTIONAL
	// (1)
	writeIFDEntry(0x0112,3,1,1,0,file);

	// SamplesPerPixel - Label 0115 
	//(3) (RGB)
	writeIFDEntry(0x0115,3,1,3,0,file);

	// Rows per strip - Label 0116 
	// Only using one strip, so value is image length
	writeIFDEntry(0x0116,3,1,file);
	writeBytePair(imgLength,file);
	writeBuffer(file);

	// Strip Byte Counts - Label 0117
	// Width * Height * 3
	writeIFDEntry(0x0117,4,1,file);
	unsigned int byteCount = image.GetWidth()*image.GetHeight()*3;
	writeWord(byteCount, file);

	// Minimum sample value - Label 0118 - OPTIONAL
	writeIFDEntry(0x0118,3,3,file);
	offset = imgWidth * imgLength * 3 + 188;
	writeWord(offset,file);

	// Maximum sample value - Label 0119 - OPTIONAL
	writeIFDEntry(0x0119,3,3,file);
	offset = imgWidth * imgLength * 3 + 194;
	writeWord(offset,file);

	// Planar configuration - Label 011c - OPTIONAL
	// (1) Chunky format
	writeIFDEntry(0x011c,3,1,1,0,file);

	// Sample format - Label 0153 - OPTIONAL
	writeIFDEntry(0x0153,3,3,file);
	offset = imgWidth * imgLength * 3 + 200;
	writeWord(offset,file);

   // Signify end of directory entries
	writeBuffer(file);
	writeBuffer(file);

   // Bits for each colour channel
	writeBytePair(8,file); //R
	writeBytePair(8,file); //G
	writeBytePair(8,file); //B

   // Minimum value for each component
	writeBytePair(0,file); //R
	writeBytePair(0,file); //G
	writeBytePair(0,file); //B

   // Maximum value per channel
	writeBytePair(255,file); //R
	writeBytePair(255,file); //G
	writeBytePair(255,file); //B

   // Samples per pixel for each channel
	writeBytePair(1,file); //R
	writeBytePair(1,file); //G
	writeBytePair(1,file); //B


}

// Notes for expansion:
// Custom footer element: ExtraSamples used to specify alpha value
   
	// 06A6 Software “Software name" - OPTIONAL

	// The format is: “YYYY:MM:DD HH:MM:SS”, with hours like those on a 24-hour
	// clock, and one space character between the date and the time. The length of the
	// string, including the terminating NUL, is 20 bytes.
	
	// 0132 DateTime “1988:02:18 13:59:59”
