#ifndef __DIRECTXRENDERER_H__
#define __DIRECTXRENDERER_H__

#include "Renderer.h"
#include <d3d9.h>
#include <d3dx9.h>

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer();
	~DirectXRenderer();
	void RenderMesh(std::string meshPath);//Renders a given mesh using DirectX.
	void RenderTexture(std::string texturePath);//Renders a given texture using DirectX.
};

#endif