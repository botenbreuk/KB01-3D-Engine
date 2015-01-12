#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <string>
#include <Windows.h>
#include <list>

#include "Mesh.h"
#include "Logger.h"

class Renderer
{
public:
	virtual ~Renderer();

	virtual void SetupMatrices() = 0;//Setup matrices

	virtual	void ClearScreen() = 0;//Clear the backbuffer and the zbuffer

	
	virtual void BeginScene() = 0;//Begin rendering.
	virtual void EndScene() = 0;//End rendering.
	
	virtual void Present() = 0;//Present the backbuffer contents to the display

	virtual void Init3D(HWND hWnd) = 0;//Initialises the 3D.
	virtual void InitGeometry(std::list<Mesh*> meshes) = 0;//Initialises the geometry of a Scene.

	virtual DWORD GetNumberOfMaterials(std::string filePath) = 0;//Returns the number of Materials in a Mesh.

	virtual void SetTexture(std::string filePath, DWORD i) = 0;//Prepares a Texture for rendering.
	virtual void SetMaterial(std::string filePath, DWORD i) = 0;//Prepares a Material for rendering.

	virtual void DrawSubset(std::string filePath, DWORD i) = 0;//Draws a Mesh and its subsets.

protected:
	Logger* _logger;//A logger for writing to the logfile.
};

#endif