#include "Kernel.h"

Kernel::Kernel()
{
	//TODO: refactor to ask/check which type of Renderer to use.
	_usedType = APIType::DirectX;
}

Kernel::~Kernel()
{
}

///Initialises the compartments of the Engine.
void Kernel::Initialize()
{
	Logger* logger = new Logger();

	//Checks the type of Renderer to use.
	switch (_usedType)
	{
		case DirectX:	_renderers[_usedType] = new DirectXRenderer(_logger);
			_inputHandler = new DirectXInputHandler();
			_logger->WriteLog("API used: DirectX", Logger::MessageType::Info);
			break;
		case OpenGL:	//TODO: Implement.
			_logger->WriteLog("API used: OpenGL", Logger::MessageType::Info);
			break;
		case Software:	//TODO: Implement.
			_logger->WriteLog("API used: Software", Logger::MessageType::Info);
			break;
	}

	_resourceManager = new ResourceManager(_logger,(DirectXRenderer*)_renderers[_usedType]);
	_windowManager = new WindowManager();
	_sceneManager = new SceneManager();

	Scene* s = _sceneManager->AddScene(_resourceManager);
	
	//Writes an info message to the logfile.
	_logger->WriteLog("Kernel initialised.", Logger::MessageType::Info);
}

///The basic loop of the Engine.
void Kernel::Run()
{
	//Creates a Window.
	HWND hWND = _windowManager->CreateNewWindow();

	//Initialises 3D
	_renderers[_usedType]->Init3D(hWND);

	//Loads in the Meshes.
	_resourceManager->LoadMeshes();

	//The message the program receives from the OS.
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
			//Renders all the Scenes of this Engine.
			_sceneManager->RenderAllScenes(_renderers[_usedType], _resourceManager);
		}
	}
}

///Cleans up the compartments of the Engine.
void Kernel::CleanUp()
{
	for(int i = APIType::First; i < APIType::Last; i++)
	{
		_renderers.erase((APIType)i);
	}
	delete _resourceManager;
	delete _windowManager;
	delete _sceneManager;

	//Writes an info message to the logfile.
	_logger->WriteLog("Kernel cleaned up.", Logger::MessageType::Info);
}