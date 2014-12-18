#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Resource.h"

class Texture : Resource
{
public:
	Texture(std::string filePath);
	~Texture();
	std::string GetFilePath();
};

#endif