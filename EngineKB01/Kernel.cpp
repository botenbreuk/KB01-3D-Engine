#include "Kernel.h"

Kernel::Kernel()
{
	
}

Kernel::~Kernel()
{
}

void Kernel::Initialize()
{
	_renderer = new DirectXRenderer();
	_resourceManager = new ResourceManager();
	_meshManager = new MeshManager();
	_windowManager = new WindowManager();
}

void Kernel::Run()
{
	_windowManager->CreateNewWindow();

	MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );

	while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Kernel::CleanUp()
{

}