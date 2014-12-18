#ifndef __MESH_H__
#define __MESH_H__

#include "Resource.h"

class Mesh : Resource
{
public:
	Mesh(std::string filePath);
	~Mesh();
	std::string GetFilePath();
};

#endif