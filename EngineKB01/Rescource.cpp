#include "Rescource.h"

Rescource::~Rescource(void)
{
}

std::string Rescource::GetFilePath()
{
	return FilePath;
}

void Rescource::SetFilePath(std::string filePath)
{
	this->FilePath = filePath;
}