#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"

class Entity
{
public:
	Entity();
	Entity(std::string meshName, std::string textureName);
	~Entity();
	void Update();//Updates the entity.

private:
	std::string MeshName;//The name of the mesh this entity uses.
	std::string TextureName;//The name of the texture this entity uses.
};

#endif