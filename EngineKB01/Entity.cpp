#include "Entity.h"
#include <iostream>

Entity::Entity()
{
}

Entity::Entity(std::string meshName, std::string textureName)
{
	MeshName = meshName;
	TextureName = textureName;
}


Entity::~Entity(void)
{
}

/*
Makes the entity render itself using a renderer.
renderer: A pointer to the renderer used.
msm: A pointer to the MeshManager used.
tsm: A pointer to the TextureManager used

*/
void Entity::RenderEntity(Renderer* renderer, MeshManager* msm, TextureManager* txm)
{
	//TOTO: Implement

	//Temporary testcode for the RescourceManager.
	//Tests the mesh getting part of the RescourceManager.
	std::string meshTest = msm->GetMesh(this->MeshName)->GetFilePath();
	std::cout << "Mesh: " << meshTest << std::endl;

	//Tests the texture getting part of the RescourceManager.
	std::string textureTest =txm->GetTexture(this->TextureName)->GetFilePath();
	std::cout << "Texture: " << textureTest << std::endl;
}