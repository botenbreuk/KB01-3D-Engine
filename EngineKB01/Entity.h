#pragma once
#include "Renderer.h"
#include "RescourceManager.h"

class Entity
{
public:
	Entity();
	Entity(std::string meshName, std::string textureName);
	~Entity(void);
	void RenderEntity(Renderer* renderer, RescourceManager* rsm);// Makes the entity render itself using a renderer.

private:
	std::string MeshName;//The name of the mesh this entity uses.
	std::string TextureName;//The name of the texture this entity uses.
};