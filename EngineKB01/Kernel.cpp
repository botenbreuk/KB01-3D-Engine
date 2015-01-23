#include "Kernel.h"

Kernel::Kernel()
{
	//TODO: refactor to ask/check which type of Renderer to use.
	_usedType = APIType::DirectX;
	_logger = LoggerPool::GetInstance()->GetLogger("Kernel");
}

Kernel::~Kernel()
{
}

///The basic loop of the Engine.
void Kernel::RunBasic()
{

	//Checks the type of Renderer to use.
	switch (_usedType)
	{
		case DirectX:
			_renderers[_usedType] = new DirectXRenderer();
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

	//Initialises the managers
	_resourceManager = new ResourceManager(_renderers[_usedType]);
	_windowManager = new WindowManager();
	_sceneManager = new SceneManager();	
	
	//Writes an info message to the logfile.
	_logger->WriteLog("Kernel initialised.", Logger::MessageType::Info);

	//Create a default scene and custom scene from scenefile
	Scene* s = _sceneManager->AddSceneFromFile(_resourceManager, "CustomSceneFile.txt", _inputHandler);
	
	//Creates two windows
	Window* w = _windowManager->CreateNewWindow();

	AddConnection(s, w);

	//Initialises 3D
	_renderers[_usedType]->Init3D(w->GetHWND());

	//Initialises Input.
	_inputHandler->InitInput(w);

	//Loads in the Meshes.
	_resourceManager->LoadMeshes();

	//The message the program receives from the OS
	MSG msg;

	//Cleans up some memory for the message
	ZeroMemory( &msg, sizeof( msg ) );

	//While the Window does not get the order to stop, he checks for messages to be handled
	while( msg.message != WM_QUIT )
	{
		//Checks if there are messages to be handled, otherwise the Engine will just keep on rendering
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			//Takes care of the message
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			_sceneManager->UpdateAllScenes();

			//Renders all the Scenes of this Engine
			_sceneManager->RenderAllScenes(_renderers[_usedType], _resourceManager, _pairs);
		}
	}
}

///Cleans up the compartments of the Engine
void Kernel::CleanUp()
{
	for(int i = APIType::First; i < APIType::Last; i++)
	{
		_renderers.erase((APIType)i);
	}
	delete _resourceManager;
	delete _windowManager;
	delete _sceneManager;

	//Writes an info message to the logfile
	_logger->WriteLog("Kernel cleaned up.", Logger::MessageType::Info);
}

///Adds connection between a scene and a window
void Kernel::AddConnection(Scene* scene, Window* window)
{
	std::pair<Scene*, Window*> pair;
	pair = std::make_pair(scene, window);
	_pairs.push_front(pair);
}

///Creates resourcemanager with the correct renderer type
void Kernel::CreateResourceManager()
{
	_resourceManager = new ResourceManager((DirectXRenderer*)_renderers[_usedType]);
}

void Kernel::CreateWindowManager()
{
	_windowManager = new WindowManager();
}

void Kernel::CreateSceneManager()
{
	_sceneManager = new SceneManager();
}

///Load renderer based on which renderertype is used
void Kernel::LoadRenderer()
{
	//Checks the type of Renderer to use.
	switch (_usedType)
	{
		case DirectX:
			_renderers[_usedType] = new DirectXRenderer();
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
}

///Start the main loop
void Kernel::Start()
{

	//The message the program receives from the OS
	MSG msg;
	
	//Cleans up some memory for the message
	ZeroMemory( &msg, sizeof( msg ) );

	//While the Window does not get the order to stop, he checks for messages to be handled
	while( msg.message != WM_QUIT )
	{
		//Checks if there are messages to be handled, otherwise the Engine will just keep on rendering
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			//Takes care of the message
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			_sceneManager->UpdateAllScenes();

			//Renders all the Scenes of this Engine
			_sceneManager->RenderAllScenes(_renderers[_usedType], _resourceManager, _pairs);
		}
	}
}