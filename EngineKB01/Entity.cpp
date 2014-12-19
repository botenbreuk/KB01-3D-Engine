#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(std::string meshName, std::string textureName)
{
	MeshName = meshName;
	TextureName = textureName;
}


Entity::~Entity()
{
}

/*
Updates the Entity.
*/
void Entity::Update()
{

}