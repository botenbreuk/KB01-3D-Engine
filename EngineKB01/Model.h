#ifndef __MODEL_H__
#define __MODEL_H__

#include "entity.h"
#include "MeshManager.h"
class Model : public Entity
{
public:
	Model();
	~Model();
	void Render(Renderer* renderer, MeshManager* msm);//Makes the Model render itself.
	void SetMeshName(std::string meshName);

private:
	std::string _meshName;//The name of the Mesh this Model uses.
	std::string _textureName;//The name of the Texture this model uses if it doesn't use a Mesh.

	void PrepareModel(std::string filePath, Renderer* renderer, DWORD i);
};

#endif