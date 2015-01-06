#include "Kernel.h"

Kernel::Kernel()
{
	
}

Kernel::~Kernel()
{
}

/*
Initialises the compartments of the Engine.
*/
void Kernel::Initialize()
{

	Log* logger = new Log();
	_renderer = new DirectXRenderer(logger);
	_resourceManager = new ResourceManager();
	_meshManager = new MeshManager(logger,(DirectXRenderer*)_renderer);
	_windowManager = new WindowManager();
	_sceneManager = new SceneManager();

	Scene* s = _sceneManager->AddScene();
	
}

/*
The basic loop of the Engine.
*/
void Kernel::Run()
{
	//Creates a Window.
	HWND hWND = _windowManager->CreateNewWindow();

	//Initialises 3D
	_renderer->Init3D(hWND);

	//Loads in the Meshes.
	_meshManager->LoadMeshes();

	//
	MSG msg;

	//Cleans up some memory for the message.
	ZeroMemory( &msg, sizeof( msg ) );

	//While the Window does not get the order to stop, he checks for messages to be handled.
	while( msg.message != WM_QUIT )
	{
		//Checks if there are messages to be handled, otherwise the Engine will just keep on rendering.
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			//Takes care of the message.
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			_sceneManager->RenderAllScenes(_renderer, _meshManager);//Renders all the Scenes of this Engine.
	
		}
	}
}

/*
Cleans up the compartments of the Engine.
*/
void Kernel::CleanUp()
{
	delete _renderer;
	delete _resourceManager;
	delete _meshManager;
	delete _windowManager;
	delete _sceneManager;
}