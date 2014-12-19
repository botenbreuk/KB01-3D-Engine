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
	DirectXRenderer();
	~DirectXRenderer();
	void RenderMesh(std::string meshPath);//Renders a given mesh using DirectX.
	void RenderTexture(std::string texturePath);//Renders a given texture using DirectX.

	void Init3D(HWND hWnd);
	void InitGeometry(std::list<Mesh*> meshes);

	LPDIRECT3DDEVICE9 Get3DDevice();

	void LoadMesh(std::string filePath, std::string name, D3DXMATERIAL* d3dxMaterials, LPD3DXBUFFER* pD3DXMtrlBuffer);
	void LoadMaterial(LPD3DXBUFFER pD3DXMtrlBuffer, std::string filePath, D3DXMATERIAL* d3dxMaterials);
	void LoadTextures(std::string filePath, D3DXMATERIAL* d3dxMaterials);
	
	//Setup matrices
	void SetupMatrices();
	
	//Clear the backbuffer and the zbuffer
	void ClearScreen();

	//Begin and end rendering
	void BeginScene();
	void EndScene();

	//Present the backbuffer contents to the display
	void Present();

	void RenderModel(std::string filePath);

	LPD3DXMESH* GetMesh(std::string name);

private:
	std::map<std::string, LPD3DXMESH> Meshes;
	std::map<std::string, LPDIRECT3DTEXTURE9*> Textures;
	std::map<std::string, D3DMATERIAL9*> Materials;
	
	LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering device
	LPD3DXBUFFER pD3DXMtrlBuffer;
	std::map<std::string, DWORD> g_dwNumMaterials;

	std::wstring s2ws(const std::string& s);
};

#endif