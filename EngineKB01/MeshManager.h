#pragma once
#include "Mesh.h"
#include "RescourceManager.h"

class MeshManager : RescourceManager
{
public:
	MeshManager(void);
	~MeshManager(void);
	Mesh* GetMesh(std::string meshName);//Returns a pointer to the mesh with the given name.
	void AddMesh(std::string meshName, std::string filePath);//Loads in a mesh.

private:
	std::map<std::string, Mesh*> Meshes;//A Key Value pair list of meshes with the associated names.
};