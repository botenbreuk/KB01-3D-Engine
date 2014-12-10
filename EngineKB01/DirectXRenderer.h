#pragma once
#include "Renderer.h"
#include <d3d9.h>
#include <d3dx9.h>

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer(void);
	~DirectXRenderer(void);
	void RenderMesh(std::string meshPath);//Renders a given mesh using DirectX.
	void RenderTexture(std::string texturePath);//Renders a given texture using DirectX.
};