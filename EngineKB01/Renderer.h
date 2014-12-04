#pragma once
#include <string>

class Renderer
{
public:
	virtual ~Renderer(void);
	virtual void RenderMesh(std::string meshPath) = 0;//Method called to render a mesh, implementation happens in subclasses.
	virtual void RenderTexture(std::string texturePath) = 0;//Method called to render a texture, implementation happens in subclasses.
};