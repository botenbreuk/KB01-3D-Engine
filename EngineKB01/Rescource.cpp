#include "Rescource.h"

Rescource::~Rescource(void)
{
}

std::string Rescource::GetFilepath()
{
	return filePath;
}

void Rescource::SetFilePath(std::string filePath)
{
	this->filePath = filePath;
}