#pragma once
#include "Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"

class Entity
{
public:
	Entity();
	Entity(std::string meshName, std::string textureName);
	~Entity(void);
	void RenderEntity(Renderer* renderer, MeshManager* msm, TextureManager* txm);// Makes the entity render itself.

private:
	std::string MeshName;//The name of the mesh this entity uses.
	std::string TextureName;//The name of the texture this entity uses.
};