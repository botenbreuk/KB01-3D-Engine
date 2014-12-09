#include "DirectXRenderer.h"
#include "Scene.h"
#include "Kernel.h"
#include <string>
#include <iostream>
#include <stdio.h>


Kernel::Kernel()
{
	Renderer = new DirectXRenderer();
	Logger = new Log();
	TestLog();
	TestRescourceManager();
}

Kernel::~Kernel()
{
	delete Renderer;
	delete Logger;
}

/*
Testcode for the log
*/
void Kernel::TestLog()
{
	const char* logContent = "Test";
	Logger->WriteLog(logContent, Log::MessageType::Info);
	std::cout << "hello world" << std::endl;
}

/*
Testcode for the Rescource Manager
*/
void Kernel::TestRescourceManager()
{
	RescourceManager* rsm = new RescourceManager();
	Entity* e = new Entity("tiger", "tiger");

	//Tests the mesh adding part of the RescourceManager
	rsm->AddMesh("tiger", "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Samples\\C++\\Direct3D\\Tutorials\\Tut06_Meshes\\tiger.x");

	//Tests the texture adding part of the RescourceManager
	rsm->AddTexture("tiger", "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Samples\\C++\\Direct3D\\Tutorials\\Tut06_Meshes\\tiger.bmp");

	//Tests the getters through the entity.
	e->RenderEntity(Renderer, rsm);
}