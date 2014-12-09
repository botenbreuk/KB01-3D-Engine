#include "Entity.h"
#include <iostream>

Entity::Entity()
{
}

Entity::Entity(std::string meshName)
{
	this->MeshName = meshName;
}


Entity::~Entity(void)
{
}

/*
Makes the entity render itself using a renderer.
renderer: A pointer to the renderer used.
rsm: A pointer to the rescource manager used
*/
void Entity::RenderEntity(Renderer* renderer, RescourceManager* rsm)
{
	//TOTO: Implement

	//Temporary testcode for the rescource manager.
	std::string test = rsm->GetMesh(this->MeshName)->GetFilePath();
	std::cout << test << std::endl;
}