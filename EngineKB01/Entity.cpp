#include "Entity.h"

Entity::~Entity()
{
}

///Updates the Entity.
void Entity::Update()
{

}

void Entity::SetPosition(float x, float y, float z)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_zPos = z;
}