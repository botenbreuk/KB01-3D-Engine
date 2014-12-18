#ifndef __DIRECTXRENDERER_H__
#define __DIRECTXRENDERER_H__
#include "Renderer.h"
#include "Mesh.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <map>

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer(void);
	~DirectXRenderer(void);
	void RenderMesh(std::string meshPath);//Renders a given mesh using DirectX.
	void RenderTexture(std::string texturePath);//Renders a given texture using DirectX.

	HRESULT Init3D(HWND hWnd);
	HRESULT InitGeometry(std::list<Mesh*> meshes);

	LPDIRECT3DDEVICE9 Get3DDevice();

	void LoadMesh(std::string filePath, std::string name);
	void LoadMaterial(LPD3DXBUFFER pD3DXMtrlBuffer, std::string filePath);

	LPD3DXMESH* GetMesh(std::string name);

private:
	std::map<std::string, LPD3DXMESH> Meshes;
	std::map<std::string, LPDIRECT3DTEXTURE9*> Textures;
	std::map<std::string, D3DMATERIAL9*> Materials;
	
	LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering device

	std::map<std::string, DWORD> g_dwNumMaterials;

	std::wstring s2ws(const std::string& s);
};

#endif