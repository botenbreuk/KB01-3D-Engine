#include "Kernel.h"

Kernel::Kernel()
{
	//TODO: refactor to ask/check which type of Renderer to use.
	_usedType = RendererType::DirectX;
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
	switch (_usedType)
	{
		case DirectX:	_renderers[_usedType] = new DirectXRenderer(_logger);
			_logger->WriteLog("Renderer used: DirectX", Log::MessageType::Info);
			break;
		case OpenGL:	//TODO: Implement.
			_logger->WriteLog("Renderer used: OpenGL", Log::MessageType::Info);
			break;
		case Software:	//TODO: Implement.
			_logger->WriteLog("Renderer used: Software", Log::MessageType::Info);
			break;
	}
	_resourceManager = new ResourceManager(_logger,(DirectXRenderer*)_renderers[_usedType]);
	_windowManager = new WindowManager();
	_sceneManager = new SceneManager();

	Scene* s = _sceneManager->AddScene();
	
	_logger->WriteLog("Kernel initialised.", Log::MessageType::Info);
}

/*
The basic loop of the Engine.
*/
void Kernel::Run()
{
	//Creates a Window.
	HWND hWND = _windowManager->CreateNewWindow();

	//Initialises 3D
	_renderers[_usedType]->Init3D(hWND);

	//Loads in the Meshes.
	_resourceManager->LoadMeshes();

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
			_sceneManager->RenderAllScenes(_renderers[_usedType], _resourceManager);//Renders all the Scenes of this Engine.
		}
	}
}

/*
Cleans up the compartments of the Engine.
*/
void Kernel::CleanUp()
{
	for(int i = RendererType::First; i < RendererType::Last; i++)
	{
		_renderers.erase((RendererType)i);
	}
	delete _resourceManager;
	delete _windowManager;
	delete _sceneManager;

	_logger->WriteLog("Kernel cleaned up.", Log::MessageType::Info);
}