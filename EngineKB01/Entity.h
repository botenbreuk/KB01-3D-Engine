#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"

class Entity
{
public:
	~Entity();
	void Update();//Updates the entity.
};

#endif