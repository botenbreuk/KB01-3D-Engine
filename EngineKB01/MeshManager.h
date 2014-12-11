#pragma once
#include "Mesh.h"
#include "RescourceManager.h"

class MeshManager : RescourceManager
{
public:
	MeshManager(Log* logger);
	~MeshManager(void);
	Mesh* GetMesh(std::string meshName);//Returns a pointer to the mesh with the given name.
	void AddMesh(std::string meshName, std::string filePath);//Loads in a mesh.

private:
	std::map<std::string, Mesh*> Meshes;//A Key Value pair list of meshes with the associated names.
	bool MeshLoadedIn(std::string filePath);//Checks if the specific Mesh is already loaded in.
	std::string GetMeshName(std::string filePath);//Gives the name of the loaded in 
};