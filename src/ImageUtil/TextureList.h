// TextureList.h
#ifndef __TEXTURELIST_H__
#define __TEXTURELIST_H__

#include "Image3ub.h"
#include "Bmp.h"
#include <cstring>

using namespace std;

/*
 * Struct representing a texture. Includes a filename and an image.
 */

struct Texture
{
	Image3ub* image;
	string fileName;
	Texture* next;

	Texture(Image3ub* _image, string _fileName)
	{
		image = _image;
		fileName = _fileName;
		next = NULL;
	}

	// TODO: Implement deconstructor for textures
	~Texture()
	{
		//delete image;
		
	}
};


/*
 * A list of all textures used for allocating memory if there are duplicate texture filenames.
 * Also used for deallocating memory.
 */

class TextureList
{
public:
	TextureList();
	~TextureList();

	Image3ub* add(string _fileName);
	int numElements();

private:
	Texture* head;
	Texture* createTexture(const string _filename);

};

#endif // __TEXTURELIST_H__
