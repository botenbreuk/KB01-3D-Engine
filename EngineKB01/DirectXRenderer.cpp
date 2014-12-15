#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer(void)
{
	g_dwNumMaterials = 0;
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

    // Load the mesh from the specified file
	std::list<Mesh*>::const_iterator iter;
	for(iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		LoadMesh((*iter)->GetFilePath(), (*iter)->GetFilePath());
    

		// We need to extract the material properties and texture names from the 
		// pD3DXMtrlBuffer
		D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();
		Materials[(*iter)->GetFilePath()] = new D3DMATERIAL9[g_dwNumMaterials];
		if( Materials[(*iter)->GetFilePath()] == NULL )
			return E_OUTOFMEMORY;
		Textures[(*iter)->GetFilePath()] = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
		if( Textures[(*iter)->GetFilePath()] == NULL )
			return E_OUTOFMEMORY;

		for( DWORD i = 0; i < g_dwNumMaterials; i++ )
		{
			// Copy the material
			Materials[(*iter)->GetFilePath()][i] = d3dxMaterials[i].MatD3D;

			// Set the ambient color for the material (D3DX does not do this)
			Materials[(*iter)->GetFilePath()][i].Ambient = Materials[(*iter)->GetFilePath()][i].Diffuse;

			Textures[(*iter)->GetFilePath()][i] = NULL;
				if( d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
			{
				// Create the texture
					if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice,
                                                    d3dxMaterials[i].pTextureFilename,
                                                    &Textures[(*iter)->GetFilePath()][i] ) ) )
				{
					// If texture is not in current folder, try parent folder
					const CHAR* strPrefix = "..\\";
					CHAR strTexture[MAX_PATH];
					strcpy_s( strTexture, MAX_PATH, strPrefix );
					strcat_s( strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename );
					// If texture is not in current folder, try parent folder
					if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice,
                                                        strTexture,
                                                        &Textures[(*iter)->GetFilePath()][i] ) ) )
					{
						MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
					}
				}
			}
		}
	}
    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}

void DirectXRenderer::LoadMesh(std::string filePath, std::string name){
	// Load the mesh from the specified file

	LPD3DXBUFFER pD3DXMtrlBuffer;
	if( FAILED( D3DXLoadMeshFromX( s2ws(filePath).c_str(), D3DXMESH_SYSTEMMEM,
                                   g_pd3dDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
								   Meshes[name]* ) ))
    {
        // If model is not in current folder, try parent folder
        if( FAILED( D3DXLoadMeshFromX( s2ws(filePath).c_str(), D3DXMESH_SYSTEMMEM,
                                       g_pd3dDevice, NULL,
                                       &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                       Meshes[name]* ) ) )
        {
            MessageBox( NULL, L"Could not find tiger.x", L"Meshes.exe", MB_OK );
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