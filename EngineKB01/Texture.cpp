#include "Texture.h"


Texture::Texture(std::string filePath)
{
	_filePath = filePath;
}


Texture::~Texture()
{
}

std::string Texture::GetFilePath()
{
	return Resource::GetFilePath();
}