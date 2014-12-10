#pragma once
#include "Rescource.h"

class Mesh : Rescource
{
public:
	Mesh(std::string filePath);
	~Mesh(void);
	std::string GetFilePath();
};