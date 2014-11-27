#pragma once
#include "Renderer.h"
#include <string>

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer(void);
	~DirectXRenderer(void);
	void RenderMesh(std::string meshPath);
	void RenderTexture(std::string texturePath);
};

