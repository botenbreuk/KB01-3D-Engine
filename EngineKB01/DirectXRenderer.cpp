#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer()
{
	_logger = LoggerPool::GetInstance()->GetLogger("Renderer");
	_logger->WriteLog("API used: DirectX", Logger::MessageType::Info);	
}

DirectXRenderer::~DirectXRenderer()
{
}

///Uses Skyboxtexture.jpg if parameter filePath is ignored
void DirectXRenderer::CreateSkyboxTexture(std::string filePath)
{
	std::wstring temp = std::wstring(filePath.begin(), filePath.end());

	D3DXCreateTextureFromFile(_g_pd3dDevice, temp.c_str(), &_g_skyboxTexture);
}

///_g_skyboxTexture: Texture saved in CreateSkyboxTexture()
void DirectXRenderer::SetSkyboxTexture()
{
	_g_pd3dDevice->SetTexture(0, _g_skyboxTexture);
	
	_g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
	_g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	_g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE); 
}

///Clear the backbuffer and the zbuffer.
void DirectXRenderer::ClearScreen()
{
	_g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 125, 202, 250 ), 1.0f, 0 );

}

///Switches swapchain (used for rendering to multiple windows)
///hWND: HWND of relevant window
void DirectXRenderer::SetTargetSwapChain(HWND hWND)
{
	LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	_swapchains[hWND]->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	
	_g_pd3dDevice->SetRenderTarget(0, pBackBuffer);
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
void DirectXRenderer::Present(HWND hWND)
{
	
	_swapchains[hWND]->Present(NULL, NULL, hWND, NULL, 0);
	//_g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
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
	_g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	// Turn on wireframes
	//_g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	//CREATE SWAPCHAINS HERE!
	_g_pd3dDevice->GetSwapChain(0, &_swapchains[hWnd]);

	// Turn on the zbuffer
	//_g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// Turn on ambient lighting 
	_g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );
	_g_pd3dDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR); 
	_g_pd3dDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR); 
	_g_pd3dDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);

	//Writes an info message to the log.
	_logger->WriteLog("DirectX initialised.", Logger::MessageType::Info);
}

///Initialises the geometry for a Scene.
///meshes: The Models that appear in the Scene.
void DirectXRenderer::InitGeometry(std::list<Mesh*> meshes)
{
	//Loads skybox texture
	CreateSkyboxTexture();
	
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
		_logger->WriteLog("Mesh: " + name + " failed loading into graphical memory.", Logger::MessageType::Error);

		//Gives a Message box with an error message.
		MessageBox( NULL, L"Could not find Mesh", L"Meshes.exe", MB_OK );
	}
	else
	{
		//Writes an info message to the log.
		_logger->WriteLog("Mesh: " + name + " loaded into graphical memory.", Logger::MessageType::Info);
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
		_logger->WriteLog("Materials from: " + filePath + " failed loading into graphical memory.", Logger::MessageType::Error);
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
	_logger->WriteLog("Materials from: " + filePath + " loaded into graphical memory.", Logger::MessageType::Info);
}

///Loads in a Texture.
void DirectXRenderer::LoadTextures(std::string filePath, D3DXMATERIAL* d3dxMaterials)
{
	_textures[filePath] = new LPDIRECT3DTEXTURE9[_g_dwNumMaterials[filePath]];
	if( _textures[filePath] == NULL )
	{
		//Writes an error message to the log.
		_logger->WriteLog("Textures from: " + filePath + " failed loading into graphical memory.", Logger::MessageType::Error);

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
				_logger->WriteLog("Textures from: " + filePath + " failed loading into graphical memory.", Logger::MessageType::Error);

				//Gives a Message box with an error message.
				MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
			}
			else
			{
				//Writes an info message to the log.
				_logger->WriteLog("Textures from: " + filePath + " loaded into graphical memory.", Logger::MessageType::Info);
			}
		}
	}
}

///Prepares a vertex buffer for rendering
void DirectXRenderer::SetVertexBuffer(CUSTOMVERTEX* vertices, int size)
{	
	if( FAILED( _g_pd3dDevice->CreateVertexBuffer( size * sizeof( CUSTOMVERTEX ),
                                                  0, D3DFVF_XYZ|D3DFVF_DIFFUSE,
                                                  D3DPOOL_DEFAULT, &_g_pVB, NULL ) ) )
    {
        
    }

	VOID* pVertices;

	if (FAILED(_g_pVB->Lock(0, size * sizeof( CUSTOMVERTEX ), (void**)&pVertices, 0)))
	{
		MessageBoxA(NULL,"Error trying to lock","FillVertices()",MB_OK);
	}
	memcpy(pVertices, vertices, size * sizeof( CUSTOMVERTEX ));
	_g_pVB->Unlock();

	_g_pd3dDevice->SetStreamSource(0, _g_pVB, 0, sizeof(CUSTOMVERTEX));
	_g_pd3dDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
	

	_g_pVB->Release();
	pVertices = NULL;
	_g_pVB = NULL;
}
	
///Prepares a index buffer for rendering
void DirectXRenderer::SetIndexBuffer(short* indices, int vertexSize, int size)
{
	// create an index buffer interface called i_buffer
    _g_pd3dDevice->CreateIndexBuffer(size * sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_DEFAULT,
                              &_g_pIB,
                              NULL);
	
	VOID* p_Indices;

	if (FAILED(_g_pIB->Lock(0, size * sizeof(short), (void**)&p_Indices, 0)))
    {
        MessageBoxA(NULL,"Error trying to lock","FillIndices()",MB_OK);
    }
    memcpy(p_Indices, indices, size * sizeof(short));
    _g_pIB->Unlock();
	
	_g_pd3dDevice->SetIndices(_g_pIB);
	_g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexSize, 0, (size / 6) * 2);
	
	_g_pIB->Release();
	p_Indices = NULL;
	_g_pIB = NULL;
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
LPDIRECT3DDEVICE9 DirectXRenderer::Get3DDevice()
{
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
	D3DXMatrixIdentity(&matWorld);
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

void DirectXRenderer::SetupWorldMatrix()
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY( &matWorld, timeGetTime() / 1000.0f );
	_g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
}

///Float z: default parameter at -5.0f.
///Edit to place camera further or closer
void DirectXRenderer::SetupViewMatrix(float z)
{
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	
	D3DXVECTOR3 vEyePt( 0.0f, 10.0f, z );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	_g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
}

void DirectXRenderer::SetupProjectionMatrix()
{
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

void DirectXRenderer::SetModelMatrix(float x, float y, float z, float scale, float rotation)
{
	D3DXMATRIXA16 matModel;
	D3DXMATRIX matRotY;
	D3DXMATRIX matScale;
	D3DXMATRIX matTranslate;

	D3DXMatrixRotationY(&matRotY, rotation);
	D3DXMatrixIdentity(&matModel);
	D3DXMatrixScaling(&matScale, scale, scale, scale);
	D3DXMatrixTranslation(&matTranslate, x, y, z);

	// Set up model matrix
	_g_pd3dDevice->SetTransform( D3DTS_WORLD, &(matModel * matRotY * matScale * matTranslate) );

}

///Gives back the number of Materials in a Mesh.
///filePath: The filepath to the Mesh
DWORD DirectXRenderer::GetNumberOfMaterials(std::string filePath)
{
	return _g_dwNumMaterials[filePath];
}

///Create swapchain, used for rendering to multiple windows
///hWND: HWND this swapchain is relevant for
void DirectXRenderer::CreateSwapChain(HWND hWND)
{
	_g_pd3dDevice->CreateAdditionalSwapChain( &d3dpp, &_swapchains[hWND]);
}

///Method to create skybox
void DirectXRenderer::InitSkybox()
{
	///Change num to enlarge or shrink Skybox
	long num = 50.0f;

	///Vertices of giant box
	CUSTOMVERTEX g_Vertices[] =
	{
		{ -num, num, -num, 1.0f, 0xffffffff, 0.0f, 0.0f },		// left up front
		{ num, num, -num, 1.0f, 0xffffffff, 1.0f, 0.0f },		// right up front	
		{ -num, -num, -num, 1.0f, 0xffffffff, 0.0f, 1.0f},		// left bottom front
		{ num, -num, -num, 1.0f, 0xffffffff, 1.0f, 1.0f },		// right bottom front
		{ -num, num, num, 1.0f, 0xffffffff, 0.0f, 0.0f },		// left up back
		{ num, num, num, 1.0f, 0xffffffff, 1.0f, 0.0f },		// right up back
		{ -num, -num, num, 0.0f, 0xffffffff, 1.0f, 1.0f },		// left bottom back
		{ num, -num, num, 1.0f, 0xffffffff, 1.0f, 1.0f },		// right bottom back
	};
	
	///Create and fill vertexbuffer
	_g_pd3dDevice->CreateVertexBuffer( 8 * sizeof( CUSTOMVERTEX ),
												  0, D3DFVF_CUSTOMVERTEX,
												  D3DPOOL_DEFAULT, &_g_pVB, NULL);

	VOID* pVertices;
	_g_pVB->Lock( 0, sizeof( g_Vertices ), ( void** )&pVertices, 0 );
	memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
	_g_pVB->Unlock();

	///Defines sides of box
	short indices[] =
	{
		7, 6, 5,    // side 3 Back
		6, 4, 5,
		4, 6, 0,    // side 2 Left
		6, 2, 0,
		3, 7, 1,    // side 4 Right
		7, 5, 1,
		0, 2, 1,    // side 1 Front
		1, 2, 3,
		4, 0, 5,    // side 5 Up
		0, 1, 5,
		3, 2, 7,    // side 6 Bottom
		2, 6, 7,
	};

	///Create and fill indexbuffer
	_g_pd3dDevice->CreateIndexBuffer(36*sizeof(short),
							  0,
							  D3DFMT_INDEX16,
							  D3DPOOL_DEFAULT,
							  &_g_pIB,
							  NULL);
	_g_pIB->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, indices, sizeof(indices));
	_g_pIB->Unlock();
}

///Draws box from indexbuffer and vertexbuffer
///Releases both buffers to clear memory
void DirectXRenderer::DrawSkybox()
{
	_g_pd3dDevice->SetStreamSource( 0, _g_pVB, 0, sizeof( CUSTOMVERTEX ) );
	_g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	_g_pd3dDevice->SetIndices(_g_pIB);
	_g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	///Releases both buffers to clear memory
	_g_pVB->Release();
	_g_pVB = NULL;

	_g_pIB->Release();
	_g_pIB = NULL;
}