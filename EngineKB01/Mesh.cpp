#include "Mesh.h"


Mesh::Mesh(std::string filePath)
{
	this->FilePath = filePath;
}


Mesh::~Mesh()
{
}

std::string Mesh::GetFilePath()
{
	return Resource::GetFilePath();
}