#include "Resource.h"

Resource::~Resource()
{
}

std::string Resource::GetFilePath()
{
	return _filePath;
}

void Resource::SetFilePath(std::string filePath)
{
	_filePath = filePath;
}