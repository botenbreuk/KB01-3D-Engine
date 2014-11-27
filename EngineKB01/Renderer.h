#pragma once
#include <string>

class Renderer
{
public:
	virtual ~Renderer(void);
	virtual void RenderMesh(std::string meshPath) = 0;
	virtual void RenderTexture(std::string texturePath) = 0;
};

