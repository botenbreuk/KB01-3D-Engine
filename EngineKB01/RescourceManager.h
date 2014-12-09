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
	void AddMesh(std::string meshName, std::string filePath);//Loads in a mesh.
	Texture* GetTexture(std::string textureName);//Returns a pointer to the texture with the given name.
	void AddTexture(std::string textureName, std::string filePath);//Loads in a texture.
	
private:
	std::map<std::string, Texture*> Textures;//A Key Value pair list of textures with the associated names.
	std::map<std::string, Mesh*> Meshes;//A Key Value pair list of meshes with the associated names.
};