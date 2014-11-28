#pragma once
#include "Renderer.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);
	void Render(Renderer* renderer);// Makes the entity render itself using a renderer.
};