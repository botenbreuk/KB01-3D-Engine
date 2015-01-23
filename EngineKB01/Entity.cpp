#include "Entity.h"

Entity::~Entity()
{
}

/// Updates the Entity.
void Entity::Update()
{

}

/// Sets the position of an Entity
/// \param x,y,z Coordinates of the position in 3D space.
void Entity::SetPosition(float x, float y, float z)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_zPos = z;
}