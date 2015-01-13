#ifndef __MODEL_H__
#define __MODEL_H__

#include "entity.h"
#include "ResourceManager.h"

class Model : public Entity
{
public:
	Model(ResourceManager* rsm, std::string meshName, bool check);
	~Model();
	void Render(Renderer* renderer, ResourceManager* msm);//Makes the Model render itself.
	void SetMeshName(std::string meshName);
	void SetPosistion(float x = 0, float y = 0, float z = 0);
	
	std::string _meshName;//The name of the Mesh this Model uses.
private:
	bool _rotate;
	std::string _textureName;//The name of the Texture this model uses if it doesn't use a Mesh.

	void Prepare(std::string filePath, Renderer* renderer, DWORD i);//Prepares this Model for rendering by setting the Materials and Textures.
};

#endif