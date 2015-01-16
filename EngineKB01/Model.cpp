#include "Model.h"

Model::Model(ResourceManager* rsm, std::string meshName, bool check)
{
	_meshName = meshName;
	rsm->LoadMesh(_meshName, _meshName);
	this->_rotate = check;
}

Model::Model()
{

}

Model::~Model()
{
}

/// Makes the Model render itself.
/// renderer: A pointer to the renderer used.
/// msm: A pointer to the Mesh Manager used.
void Model::Render(Renderer* renderer, ResourceManager* msm)
{
	Mesh* modelMesh = msm->GetMesh(_meshName);
	for( DWORD i = 0; i < renderer->GetNumberOfMaterials(modelMesh->GetFilePath()); i++ )
	{
		Prepare(modelMesh->GetFilePath(), renderer, i);
		renderer->DrawSubset(modelMesh->GetFilePath(), i);
	}
}

void Model::SetMeshName(std::string meshName)
{
	_meshName = meshName;
}

/// Sets the position of an Model
/// return: void
void Model::SetPosition(float x, float y, float z)
{
	this->Entity::SetPosition(x, y, z);
}

///Prepares this Model for rendering by setting the Materials and Textures.
///filePath: filePath to the Mesh, which is the key for the Materials and the Textures.
///renderer: A pointer to the renderer used.
///i: Index of the Material and Texture to be used.
void Model::Prepare(std::string filePath, Renderer* renderer, DWORD i)
{
	// Set the material and texture for this subset
	renderer->SetMaterial(filePath, i);
	renderer->SetTexture(filePath, i);
	renderer->SetModelMatrix(_xPos, _yPos, _zPos, 1, _rotate);
}