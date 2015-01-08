#include "Mesh.h"


Mesh::Mesh(std::string filePath)
{
	this->_filePath = filePath;
}


Mesh::~Mesh()
{
}

std::string Mesh::GetFilePath()
{
	return Resource::GetFilePath();
}