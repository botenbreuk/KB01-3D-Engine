#include "Mesh.h"


Mesh::Mesh(std::string filePath)
{
	this->FilePath = filePath;
}


Mesh::~Mesh(void)
{
}

std::string Mesh::GetFilePath()
{
	return Rescource::GetFilePath();
}