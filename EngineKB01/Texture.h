#pragma once
#include "Rescource.h"

class Texture : Rescource
{
public:
	Texture(std::string filePath);
	~Texture(void);
	std::string GetFilePath();
};