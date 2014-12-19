#ifndef __MESHMANAGER_H__
#define __MESHMANAGER_H__

#include "Mesh.h"
#include "ResourceManager.h"
#include "DirectXRenderer.h"

class MeshManager : ResourceManager
{
public:
	MeshManager();
	MeshManager(Log* logger, DirectXRenderer* renderer);
	~MeshManager();
	Mesh* GetMesh(std::string meshName);//Returns a pointer to the Mesh with the given name.
	void LoadMesh(std::string meshName, std::string filePath);//Loads in a Mesh.

private:
	std::map<std::string, Mesh*> Meshes;//A Key Value pair list of meshes with the associated names.
	bool MeshLoadedIn(std::string filePath);//Checks if the specific Mesh is already loaded in.
	std::string GetMeshName(std::string filePath);//Gives the name of the loaded in Mesh.
	DirectXRenderer* Renderer;
};

#endif