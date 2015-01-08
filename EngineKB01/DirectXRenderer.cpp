#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer(Logger* logger)
{
	_logger = logger;
}


DirectXRenderer::~DirectXRenderer()
{
}

///Clear the backbuffer and the zbuffer.
void DirectXRenderer::ClearScreen()
{
	_g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 255, 0, 0 ), 1.0f, 0 );

}

///Begin rendering.
void DirectXRenderer::BeginScene()
{
	_g_pd3dDevice->BeginScene();
}

///End rendering.
void DirectXRenderer::EndScene()
{
	_g_pd3dDevice->EndScene();
}

///Present the backbuffer contents to the display.
void DirectXRenderer::Present()
{
	_g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

///Initialises DirectX.
void DirectXRenderer::Init3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( _g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		//Writes an error message to the log.
		_logger->WriteLog("DirectX initialisation failed.", Logger::MessageType::Error);

        return;
	}

    // Set up the structure used to create the D3DDevice.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( _g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_g_pd3dDevice ) ) )
    {
		//Writes an error message to the log.
		_logger->WriteLog("DirectX initialisation failed.", Logger::MessageType::Error);

        return;
    }

    // Turn on the zbuffer
    _g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    _g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	//Writes an info message to the log.
	_logger->WriteLog("DirectX initialised.", Logger::MessageType::Info);
}

///Initialises the geometry for a Scene.
///meshes: The Models that appear in the Scene.
void DirectXRenderer::InitGeometry(std::list<Mesh*> meshes)
{
    //Loads the rescources from the specified file(s).
	std::list<Mesh*>::const_iterator iter;
	for(iter = meshes.begin(); iter != meshes.end(); iter++)
	{
		//Load in the Mesh.
		LoadMesh((*iter)->GetFilePath(), (*iter)->GetFilePath());
		//Prepares Materials.
		D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )_pD3DXMtrlBuffer->GetBufferPointer();
		//Load in the Materials associated with the Mesh.
		LoadMaterial((*iter)->GetFilePath(), d3dxMaterials);
		//Load in the Textures for the Mesh.
		LoadTextures((*iter)->GetFilePath(), d3dxMaterials);
	}
    //Done with the material buffer
    _pD3DXMtrlBuffer->Release();

	//Writes an info message to the log.
	_logger->WriteLog("Geometry initialised.", Logger::MessageType::Info);
}

///Loads in a Mesh.
void DirectXRenderer::LoadMesh(std::string filePath, std::string name)
{
	//Loads the mesh from the specified file
	if( FAILED( D3DXLoadMeshFromXA( filePath.c_str(), D3DXMESH_SYSTEMMEM, _g_pd3dDevice, NULL, &_pD3DXMtrlBuffer, NULL, &_g_dwNumMaterials[filePath], &_meshes[name] ) ))
	{
		//Writes an error message to the log.
		_logger->WriteLog("Mesh: " + name + " failed loading in.", Logger::MessageType::Error);

		//Gives a Message box with an error message.
		MessageBox( NULL, L"Could not find Mesh", L"Meshes.exe", MB_OK );
	}
	else
	{
		//Writes an info message to the log.
		_logger->WriteLog("Mesh: " + name + " loaded in.", Logger::MessageType::Info);
	}
}

///Loads in a Material.
void DirectXRenderer::LoadMaterial(std::string filePath, D3DXMATERIAL* d3dxMaterials)
{
	//Extracts the material properties and texture names from the pD3DXMtrlBuffer
	_materials[filePath] = new D3DMATERIAL9[_g_dwNumMaterials[filePath]];
	if( _materials[filePath] == NULL )
	{
		//Writes an error message to the log.
		_logger->WriteLog("Materials from: " + filePath + " failed loading in.", Logger::MessageType::Error);
		return;
	}

	for( DWORD i = 0; i < _g_dwNumMaterials[filePath]; i++ )
	{
		//Copy the material
		_materials[filePath][i] = d3dxMaterials[i].MatD3D;
		//Set the ambient color for the material (D3DX does not do this)
		_materials[filePath][i].Ambient = _materials[filePath][i].Diffuse;
	}

	//Writes an info message to the log.
	_logger->WriteLog("Materials from: " + filePath + " loaded in.", Logger::MessageType::Info);
}

///Loads in a Texture.
void DirectXRenderer::LoadTextures(std::string filePath, D3DXMATERIAL* d3dxMaterials)
{
	_textures[filePath] = new LPDIRECT3DTEXTURE9[_g_dwNumMaterials[filePath]];
	if( _textures[filePath] == NULL )
	{
		//Writes an error message to the log.
		_logger->WriteLog("Textures from: " + filePath + " failed loading in.", Logger::MessageType::Error);

		return;
	}
	for( DWORD i = 0; i < _g_dwNumMaterials[filePath]; i++ )
	{
        if(_textures[filePath] != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            // Create the Texture
			if(FAILED(D3DXCreateTextureFromFileA(_g_pd3dDevice, d3dxMaterials[i].pTextureFilename, &_textures[filePath][i])))
			{
				//Writes an error message to the log.
				_logger->WriteLog("Textures from: " + filePath + " failed loading in.", Logger::MessageType::Error);

				//Gives a Message box with an error message.
                MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
            }
			else
			{
				//Writes an info message to the log.
				_logger->WriteLog("Textures from: " + filePath + " loaded in.", Logger::MessageType::Info);
			}
        }
	}
}


///Prepares a Material for rendering.
void DirectXRenderer::SetMaterial(std::string filePath, DWORD i)
{
	_g_pd3dDevice->SetMaterial( &_materials[filePath][i] );
}

///Prepares a Texture for rendering.
void DirectXRenderer::SetTexture(std::string filePath, DWORD i)
{
	_g_pd3dDevice->SetTexture( 0, _textures[filePath][i] );
}


///Draw the Mesh subset
///filePath: The file path to the Mesh.
///i: The index for the subset to be drawn.

void DirectXRenderer::DrawSubset(std::string filePath, DWORD i)
{
		_meshes[filePath]->DrawSubset( i );
}

///Returns the 3DDevice.
LPDIRECT3DDEVICE9 DirectXRenderer::Get3DDevice(){
	return _g_pd3dDevice;
}


///Returns a Mesh.
///name: The Key to which the Mesh belongs.
LPD3DXMESH* DirectXRenderer::GetMesh(std::string name)
{
	return &_meshes[name];
}

///Setup matrices.
void DirectXRenderer::SetupMatrices()
{
    // Set up world matrix
    D3DXMATRIXA16 matWorld;
    D3DXMatrixRotationY( &matWorld, timeGetTime() / 1000.0f );
    _g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the 
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    _g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    _g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

///Gives back the number of Materials in a Mesh.
///filePath: The filepath to the Mesh
DWORD DirectXRenderer::GetNumberOfMaterials(std::string filePath)
{
	return _g_dwNumMaterials[filePath];
}