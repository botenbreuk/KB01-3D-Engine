#pragma once
#include <vector>
#include "Rescource.h"
#include "Texture.h"
#include <map>
#include <utility>
#include "Mesh.h"

class RescourceManager
{
public:
	RescourceManager(void);
	~RescourceManager(void);
	Mesh* GetMesh(std::string meshName);//Returns a pointer to the mesh with the given name.
	
private:
	std::vector<Texture> textures;
	std::map<std::string, Mesh*> Meshes;//A Key Value pair list of meshes with the associated names.
};

