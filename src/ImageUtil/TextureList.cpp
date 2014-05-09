// TextureList.cpp
#include "TextureList.h"

TextureList::TextureList()
{
	head = NULL;
}

TextureList::~TextureList()
{
	Texture* current = head;

	while (current != NULL)
	{
		Texture* next = current->next;
		// TODO implement delete
		//delete current;
		current = next;
	}
}

// Returns total number of textures
int TextureList::numElements()
{
	int total = 0;

	Texture* current = head;

	while (current != NULL)
	{
		total++;
		current = current->next;
	}
	return total;
}

// Imports a texture given a filename
Image3ub* TextureList::add(string _fileName)
{
	if (head == NULL)
	{
		head = createTexture(_fileName);
		return head->image;
	}
	else 
	{
		Texture* current = head;

		// Iterate through list for texture
		while (true)
		{
			if (current->fileName == _fileName) return current->image;

			else if (current->next == NULL)
			{
				Texture* newTex = createTexture(_fileName);
				current->next = newTex;
				return newTex->image;
			}

			current = current->next;
		}

	}
}

Texture* TextureList::createTexture(const string _filename)
{
	Image3ub *image = Bmp::readBmp(_filename);
	return new Texture(image, _filename);
}
