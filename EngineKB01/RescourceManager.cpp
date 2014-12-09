#include "RescourceManager.h"


RescourceManager::RescourceManager(void)
{
	Mesh* tiger = new Mesh("C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Samples\\C++\\Direct3D\\Tutorials\\Tut06_Meshes\\tiger.x");
	Meshes["tiger"] = tiger;
}


RescourceManager::~RescourceManager(void)
{
}

/*
Returns a pointer to the mesh with the given name.
meshName: The name of the mesh to be returned.
*/
Mesh* RescourceManager::GetMesh(std::string meshName)
{
	return Meshes[meshName];
}