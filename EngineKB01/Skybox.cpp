#include "Skybox.h"


Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}

void Skybox::Render(Renderer* renderer)
{
	renderer->SetSkyboxTexture();
	renderer->InitSkybox();
	renderer->DrawSkybox();
}