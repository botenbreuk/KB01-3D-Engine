#include "MeshManager.h"


MeshManager::MeshManager(void)
{
}


MeshManager::~MeshManager(void)
{
}

/*
Returns a pointer to the mesh with the given name.
meshName: The name of the mesh to be returned.
*/
Mesh* MeshManager::GetMesh(std::string meshName)
{
	return Meshes[meshName];
}

/*
Loads in a mesh.
meshName: The Key name of the mesh.
filePath: The filepath to the mesh.
*/
void MeshManager::AddMesh(std::string meshName, std::string filePath)
{
	if(NULL == Meshes[meshName])
	{
		Mesh* m = new Mesh(filePath);
		Meshes[meshName] = m;
	}
}