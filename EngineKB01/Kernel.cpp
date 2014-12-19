#include "Kernel.h"
#include "Scene.h"

Kernel::Kernel()
{
	
}

Kernel::~Kernel()
{
}

void Kernel::Initialize()
{

	Log* logger = new Log();
	_renderer = new DirectXRenderer();
	_resourceManager = new ResourceManager();
	_meshManager = new MeshManager(logger,(DirectXRenderer*)_renderer);
	_windowManager = new WindowManager();
	_sceneManager = new SceneManager();

	Scene* s = _sceneManager->AddScene();
	
}

void Kernel::Run()
{
	HWND hWND = _windowManager->CreateNewWindow();
	_renderer->Init3D(hWND);
	_meshManager->LoadMeshes();
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			_sceneManager->RenderAllScenes(_renderer, _meshManager);
	
		}
	}
}

void Kernel::CleanUp()
{

}