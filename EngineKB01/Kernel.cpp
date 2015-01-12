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

///Initialises the compartments of the Engine.
void Kernel::Initialize()
{

	//Checks the type of Renderer to use.
	switch (_usedType)
	{
		case DirectX:
			_renderers[_usedType] = new DirectXRenderer();
			_inputHandler = new DirectXInputHandler();
			break;
		case OpenGL:	//TODO: Implement.
			_logger->WriteLog("API used: OpenGL", Logger::MessageType::Info);
			break;
		case Software:	//TODO: Implement.
			_logger->WriteLog("API used: Software", Logger::MessageType::Info);
			break;
	}

	_resourceManager = new ResourceManager((DirectXRenderer*)_renderers[_usedType]);
	_windowManager = new WindowManager();
	_sceneManager = new SceneManager();
	_WSC = new WindowSceneConnector();
	
	
	//Writes an info message to the logfile.
	_logger->WriteLog("Kernel initialised.", Logger::MessageType::Info);
}

///The basic loop of the Engine.
void Kernel::Run()
{
	//Create a default scene
	Scene* s = _sceneManager->AddScene(_resourceManager);

	//Creates a Window.
	Window* w = _windowManager->CreateNewWindow();
	Window* w2 = _windowManager->CreateNewWindow();
	w2->SetTitle("2e window yo");

	//Connect create scene and window
	_WSC->AddConnection(s, w2);
	_WSC->AddConnection(s, w);
	//Sets default scene to new window
	//_windowManager->SetNewestScene(s);

	//Initialises 3D
	_renderers[_usedType]->Init3D(w->GetHWND());
	_renderers[_usedType]->CreateSwapChain(w2->GetHWND());

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
			_sceneManager->RenderAllScenes(_renderers[_usedType], _resourceManager, _WSC);
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
	delete _WSC;

	//Writes an info message to the logfile.
	_logger->WriteLog("Kernel cleaned up.", Logger::MessageType::Info);
}