#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <string>
#include "Mesh.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <list>

class Renderer
{
public:

	//virtual 3DDEVICE WIP: not directx only.
	
	virtual ~Renderer(void);
	virtual void RenderMesh(std::string meshPath) = 0;//Method called to render a mesh, implementation happens in subclasses.
	virtual void RenderTexture(std::string texturePath) = 0;//Method called to render a texture, implementation happens in subclasses.

	virtual HRESULT Init3D(HWND hWnd) = 0;
	virtual HRESULT InitGeometry(std::list<Mesh*> meshes) = 0;

	virtual LPDIRECT3DDEVICE9 Get3DDevice() = 0;
protected:
	//LPDIRECT3DDEVICE9   g_pd3dDevice;
};

#endif