#include "Skybox.h"


Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}

///Renders skybox
void Skybox::Render(Renderer* renderer)
{
	renderer->SetModelMatrix(25, 25, 25, 1, 0);
	renderer->SetSkyboxTexture();
	renderer->InitSkybox();
	renderer->DrawSkybox();
}