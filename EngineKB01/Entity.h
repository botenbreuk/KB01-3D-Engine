#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Renderer.h"

class Entity
{
public:
	~Entity();
	void Update();//Updates the entity.

private:

protected:
	float _xPos;
	float _yPos;
	float _zPos;
};

#endif