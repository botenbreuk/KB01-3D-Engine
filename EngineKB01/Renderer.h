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
	//Setup matrices
	virtual void SetupMatrices() = 0;

	//Clear the backbuffer and the zbuffer
	virtual	void ClearScreen() = 0;

	//Begin and end rendering
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	
	//Present the backbuffer contents to the display
	virtual void Present() = 0;

	virtual void Init3D(HWND hWnd) = 0;
	virtual void InitGeometry(std::list<Mesh*> meshes) = 0;

	virtual DWORD GetNumberOfMaterials(std::string filePath) = 0;

	virtual void SetTexture(std::string filePath, DWORD i) = 0;
	virtual void SetMaterial(std::string filePath, DWORD i) = 0;

	virtual void DrawSubset(std::string filePath, DWORD i) = 0;
};

#endif