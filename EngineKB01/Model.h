#ifndef __MODEL_H__
#define __MODEL_H__

#include "entity.h"
class Model : public Entity
{
public:
	Model(void);
	~Model(void);
	void Render(Renderer* renderer);//Makes the Model render itself.

private:
	std::string _meshName;//The name of the Mesh this Model uses.
	std::string _textureName//The name of the Texture this model uses if it doesn't use a Mesh.
};

#endif