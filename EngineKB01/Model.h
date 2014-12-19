#pragma once
#include "entity.h"
class Model : public Entity
{
public:
	Model(void);
	~Model(void);
	void Render(Renderer* renderer);//Makes the Model render itself.
};

