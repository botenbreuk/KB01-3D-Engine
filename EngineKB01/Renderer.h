#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <string>
#include <Windows.h>
#include "Mesh.h"
#include <list>

class Renderer
{
public:
	virtual ~Renderer();
	virtual void RenderMesh(std::string meshPath) = 0;//Method called to render a mesh, implementation happens in subclasses.
	virtual void RenderTexture(std::string texturePath) = 0;//Method called to render a texture, implementation happens in subclasses.
	//Setup matrices
	virtual void SetupMatrices() = 0;

	//Clear the backbuffer and the zbuffer
	virtual	void ClearScreen() = 0;

	//Begin and end rendering
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	
	//Present the backbuffer contents to the display
	virtual void Present() = 0;
	
	virtual void RenderModel(std::string filePath) = 0;

	virtual void Init3D(HWND hWnd) = 0;
	virtual void InitGeometry(std::list<Mesh*> meshes) = 0;
};

#endif