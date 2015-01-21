#ifndef __DIRECTXRENDERER_H__
#define __DIRECTXRENDERER_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <map>
#include <vector>

#include "Renderer.h"
#include "Mesh.h"
#include "LoggerPool.h"
#include "CustomVertex.h"

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer();
	~DirectXRenderer();

	void Init3D(HWND hWnd);//Initialises DirectX.
	void InitGeometry(std::list<Mesh*> meshes);//Initialises the geometry for a Scene.
	void CreateSwapChain(HWND hWND); //Creates new swap chain for a window

	void InitSkybox();
	void DrawSkybox();

	void CreateSkyboxTexture();
	void SetSkyboxTexture();

	LPDIRECT3DDEVICE9 Get3DDevice();//Returns the 3DDevice.

	void LoadMesh(std::string filePath, std::string name);//Loads in a Mesh.
	void LoadMaterial(std::string filePath, D3DXMATERIAL* d3dxMaterials);//Loads in a Material.
	void LoadTextures(std::string filePath, D3DXMATERIAL* d3dxMaterials);//Loads in a Texture
	
	void SetupMatrices();//Setup matrices.

	void SetupWorldMatrix();
	void SetupViewMatrix(float z = -5.0f);
	void SetupProjectionMatrix();

	void SetModelMatrix(float x, float y, float z, float scale, float rotation = 0);

	void ClearScreen();//Clear the backbuffer and the zbuffer.
	void SetTargetSwapChain(HWND hWND);
	void BeginScene();//Begin rendering.
	void EndScene();//End rendering.

	void Present(HWND hWND);//Present the backbuffer contents to the display.

	LPD3DXMESH* GetMesh(std::string name);//Returns the Mesh belonging with the name.
	
	void SetVertexBuffer(CUSTOMVERTEX* vertices, int size); //Prepares a vertex buffer for rendering.
	void SetIndexBuffer(short* indices, int vertexSize, int size); //Prepares a index buffer for rendering.

	void SetMaterial(std::string filePath, DWORD i);//Prepares a Material for rendering.
	void SetTexture(std::string filePath, DWORD i);//Prepares a Texture for rendering.

	void DrawSubset(std::string filePath, DWORD i);//Draws a Mesh and its subsets.

	DWORD GetNumberOfMaterials(std::string filePath);//Gives back the number of Materials in a Mesh.

private:
	std::map<std::string, LPD3DXMESH> _meshes;//A list of DirectX-specific Meshes.
	std::map<std::string, LPDIRECT3DTEXTURE9*> _textures;//A list of DirectX-specific Textures.
	std::map<std::string, D3DMATERIAL9*> _materials;//A list of DirectX-specific Materials.
	
	std::map<HWND, LPDIRECT3DSWAPCHAIN9> _swapchains; //lookup list of swapchains and corresponding windows.
	
	D3DPRESENT_PARAMETERS d3dpp;
	
	LPDIRECT3D9         _g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   _g_pd3dDevice; // Our rendering device

	LPDIRECT3DSWAPCHAIN9 _g_swapChain_0; // Swap chain 1
	LPDIRECT3DSWAPCHAIN9 _g_swapChain_1; // Swap chain 2
	
	LPDIRECT3DTEXTURE9 _g_skyboxTexture;
	LPD3DXBUFFER _pD3DXMtrlBuffer;//DirectX Material buffer.
	
	LPDIRECT3DVERTEXBUFFER9 _g_pVB; //Directx Vertex buffer
	LPDIRECT3DINDEXBUFFER9  _g_pIB; //Directx Index buffer

	std::map<std::string, DWORD> _g_dwNumMaterials;//A map which stores the amount of Materials in a Mesh.

	std::wstring s2ws(const std::string& s);//Converts a string to a wstring.

	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)
};

#endif