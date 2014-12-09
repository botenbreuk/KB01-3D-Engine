#include "RescourceManager.h"


RescourceManager::RescourceManager(void)
{
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

/*
Loads in a mesh.
meshName: The Key name of the mesh.
filePath: The filepath to the mesh.
*/
void RescourceManager::AddMesh(std::string meshName, std::string filePath)
{
	if(NULL == Meshes[meshName])
	{
		Mesh* m = new Mesh(filePath);
		Meshes[meshName] = m;
	}
}

/*
Returns a pointer to the texture with the given name.
textureName: The name of the texture to be returned.
*/
Texture* RescourceManager::GetTexture(std::string textureName)
{
	return Textures[textureName];
}

/*
Loads in a texture.
textureName: The Key name of the texture.
filePath: The filepath to the textrue.
*/
void RescourceManager::AddTexture(std::string textureName, std::string filePath)
{
	if(NULL == Textures[textureName])
	{
		Texture* t = new Texture(filePath);
		Textures[textureName] = t;
	}
}