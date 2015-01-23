#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "Model.h"

class Skybox : Entity
{
public:
	Skybox();
	~Skybox();

	void Render(Renderer* renderer);
};

#endif