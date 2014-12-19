#include "Model.h"


Model::Model(void)
{
}


Model::~Model(void)
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
	renderer->RenderModel(modelMesh->GetFilePath());
}

void Model::SetMeshName(std::string meshName)
{
	_meshName = meshName;
}