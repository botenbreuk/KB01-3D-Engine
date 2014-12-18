#include "Texture.h"


Texture::Texture(std::string filePath)
{
	FilePath = filePath;
}


Texture::~Texture()
{
}

std::string Texture::GetFilePath()
{
	return Resource::GetFilePath();
}