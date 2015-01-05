#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}

/*
Makes the Model render itself.
renderer: A pointer to the renderer used.
*/
void Model::Render(Renderer* renderer, MeshManager* msm)
{
	//TOTO: Implement
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

void Model::Prepare(std::string filePath, Renderer* renderer, DWORD i)
{
	// Set the material and texture for this subset
	renderer->SetMaterial(filePath, i);
	renderer->SetTexture(filePath, i);
}