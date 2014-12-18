#include "Resource.h"

Resource::~Resource()
{
}

std::string Resource::GetFilePath()
{
	return FilePath;
}

void Resource::SetFilePath(std::string filePath)
{
	this->FilePath = filePath;
}