#include "Texture.h"


Texture::Texture(std::string filePath)
{
	FilePath = filePath;
}


Texture::~Texture(void)
{
}

std::string Texture::GetFilePath()
{
	return Rescource::GetFilePath();
}