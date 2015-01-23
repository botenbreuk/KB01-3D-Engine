#ifndef __MODEL_H__
#define __MODEL_H__

#include "entity.h"
#include "ResourceManager.h"

class Model : public Entity
{
public:
	Model();
	Model(ResourceManager* rsm, std::string meshName, bool check);
	~Model();
	void Render(Renderer* renderer, ResourceManager* msm);//Makes the Model render itself.
	void SetMeshName(std::string meshName);//Sets the meshname
	void SetPosition(float x = 0, float y = 0, float z = 0);//Sets the x, y, z coordinates
	void SetScale(float scale);//Sets the scale of an Model
	void SetRotation(float rotation);//Sets the rotation of an Model
	
private:
	float _scale;
	float _rotation;
	std::string _textureName;//The name of the Texture this model uses if it doesn't use a Mesh.
	std::string _meshName;//The name of the Mesh this Model uses.

	void Prepare(std::string filePath, Renderer* renderer, DWORD i);//Prepares this Model for rendering by setting the Materials and Textures.
};

#endif