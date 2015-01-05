#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer()
{
}


DirectXRenderer::~DirectXRenderer()
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

// Clear the backbuffer and the zbuffer
void DirectXRenderer::ClearScreen(){
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB( 255, 0, 0 ), 1.0f, 0 );
}

void DirectXRenderer::BeginScene(){
	g_pd3dDevice->BeginScene();
}

void DirectXRenderer::EndScene(){
	g_pd3dDevice->EndScene();
}

void DirectXRenderer::Present(){
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


//TO DO: Clean up code!
void DirectXRenderer::Init3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return;

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
        return;
    }

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

    return;
}

void DirectXRenderer::InitGeometry(std::list<Mesh*> meshes)
{
    
	LPD3DXBUFFER pD3DXMtrlBuffer;
	D3DXMATERIAL* d3dxMaterials;

    // Load the mesh from the specified file
	std::list<Mesh*>::const_iterator iter;
	for(iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		LoadMesh((*iter)->GetFilePath(), (*iter)->GetFilePath(), &d3dxMaterials, &pD3DXMtrlBuffer);//Load in the mesh.
		LoadMaterial(pD3DXMtrlBuffer, (*iter)->GetFilePath(), d3dxMaterials);//Load in the materials associated with the mesh.
		LoadTextures((*iter)->GetFilePath(), d3dxMaterials);
	}
    // Done with the material buffer
    pD3DXMtrlBuffer->Release();
}

void DirectXRenderer::LoadMesh(std::string filePath, std::string name, D3DXMATERIAL** d3dxMaterials, LPD3DXBUFFER* pD3DXMtrlBufferptr)
{
	// Load the mesh from the specified file

	if( FAILED( D3DXLoadMeshFromXA( filePath.c_str(), D3DXMESH_SYSTEMMEM,
                                   g_pd3dDevice, NULL,
                                   pD3DXMtrlBufferptr, NULL, &g_dwNumMaterials[filePath],
								   &Meshes[name] ) ))
	{
        // If model is not in current folder, try parent folder
		if( FAILED( D3DXLoadMeshFromXA( filePath.c_str(), D3DXMESH_SYSTEMMEM,
                                       g_pd3dDevice, NULL,
                                       pD3DXMtrlBufferptr, NULL, &g_dwNumMaterials[filePath],
                                       &Meshes[name] ) ) )
		{
			MessageBox( NULL, L"Could not find Mesh", L"Meshes.exe", MB_OK );
		}
	}
	*d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBufferptr;
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
	//Textures[filePath] = NULL;
	for( DWORD i = 0; i < g_dwNumMaterials[filePath]; i++ )
	{
        if(Textures[filePath] != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            // Create the texture
			if(FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, d3dxMaterials[i].pTextureFilename, &Textures[filePath][i])))
			{
                    MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
            }
        }
	}
}

void DirectXRenderer::RenderModel(std::string filePath){
	for( DWORD i = 0; i < g_dwNumMaterials[filePath]; i++ )
        {
            // Set the material and texture for this subset
			g_pd3dDevice->SetMaterial( &Materials[filePath][i] );
            g_pd3dDevice->SetTexture( 0, Textures[filePath][i] );

            // Draw the mesh subset
			Meshes[filePath]->DrawSubset( i );
        }
}


LPDIRECT3DDEVICE9 DirectXRenderer::Get3DDevice(){
	return g_pd3dDevice;
}

LPD3DXMESH* DirectXRenderer::GetMesh(std::string name)
{
	return &Meshes[name];
}

void DirectXRenderer::SetupMatrices()
{
    // Set up world matrix
    D3DXMATRIXA16 matWorld;
    D3DXMatrixRotationY( &matWorld, timeGetTime() / 1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the 
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}