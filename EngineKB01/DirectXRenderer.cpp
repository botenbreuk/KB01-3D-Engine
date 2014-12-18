#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer(void)
{
}


DirectXRenderer::~DirectXRenderer(void)
{
}

/*
Renders a given mesh using DirectX.
meshPath: Filepath to used mesh.
*/
void DirectXRenderer::RenderMesh(std::string meshPath)
{
	//TOTO: Implement
}

/*
Renders a given texture using DirectX.
texturePath: Filepath to used texture.
*/
void DirectXRenderer::RenderTexture(std::string texturePath)
{
	//TOTO: Implement
}

HRESULT DirectXRenderer::Init3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

    return S_OK;
}

HRESULT DirectXRenderer::InitGeometry(std::list<Mesh*> meshes)
{
    
	LPD3DXBUFFER pD3DXMtrlBuffer;
	D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();

    // Load the mesh from the specified file
	std::list<Mesh*>::const_iterator iter;
	for(iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		LoadMesh((*iter)->GetFilePath(), (*iter)->GetFilePath());//Load in the mesh.
		LoadMaterial(pD3DXMtrlBuffer, (*iter)->GetFilePath(), d3dxMaterials);//Load in the materials associated with the mesh.
		LoadTextures((*iter)->GetFilePath(), d3dxMaterials);
	}
    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}

void DirectXRenderer::LoadMesh(std::string filePath, std::string name)
{
	// Load the mesh from the specified file

	LPD3DXBUFFER pD3DXMtrlBuffer;
	if( FAILED( D3DXLoadMeshFromXA( filePath.c_str(), D3DXMESH_SYSTEMMEM,
                                   g_pd3dDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[filePath],
								   &Meshes[name] ) ))
	{
        // If model is not in current folder, try parent folder
		if( FAILED( D3DXLoadMeshFromXA( filePath.c_str(), D3DXMESH_SYSTEMMEM,
                                       g_pd3dDevice, NULL,
                                       &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[filePath],
                                       &Meshes[name] ) ) )
		{
			MessageBox( NULL, L"Could not find Mesh", L"Meshes.exe", MB_OK );
		}
	}

}

void DirectXRenderer::LoadMaterial(LPD3DXBUFFER pD3DXMtrlBuffer, std::string filePath, D3DXMATERIAL* d3dxMaterials)
{
	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	Materials[filePath] = new D3DMATERIAL9[g_dwNumMaterials[filePath]];
	if( Materials[filePath] == NULL )
	{
		return;
	}

	for( DWORD i = 0; i < g_dwNumMaterials[filePath]; i++ )
	{
		// Copy the material
		Materials[filePath][i] = d3dxMaterials[i].MatD3D;
		// Set the ambient color for the material (D3DX does not do this)
		Materials[filePath][i].Ambient = Materials[filePath][i].Diffuse;
	}
}

void DirectXRenderer::LoadTextures(std::string filePath, D3DXMATERIAL* d3dxMaterials)
{
	Textures[filePath] = new LPDIRECT3DTEXTURE9[g_dwNumMaterials[filePath]];
	if( Textures[filePath] == NULL )
	{
		return;
	}
	Textures[filePath] = NULL;
	for( DWORD i = 0; i < g_dwNumMaterials[filePath]; i++ )
	{
        if(Textures[filePath] != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            // Create the texture
			if(FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, d3dxMaterials[i].pTextureFilename, Textures[filePath])))
			{
                    MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
            }
        }
	}
}

std::wstring DirectXRenderer::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

LPDIRECT3DDEVICE9 DirectXRenderer::Get3DDevice(){
	return g_pd3dDevice;
}

LPD3DXMESH* DirectXRenderer::GetMesh(std::string name)
{
	return &Meshes[name];
}