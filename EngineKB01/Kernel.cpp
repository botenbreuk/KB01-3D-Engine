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
	TestRescourceManagers();
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
Testcode for the Rescource Managers
*/
void Kernel::TestRescourceManagers()
{
	MeshManager* msm = new MeshManager();
	TextureManager* txm = new TextureManager();
	Entity* e = new Entity("tiger", "tiger");

	//Tests the mesh adding part of the RescourceManager
	msm->AddMesh("tiger", "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Samples\\C++\\Direct3D\\Tutorials\\Tut06_Meshes\\tiger.x");

	//Tests the texture adding part of the RescourceManager
	txm->AddTexture("tiger", "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Samples\\C++\\Direct3D\\Tutorials\\Tut06_Meshes\\tiger.bmp");

	//Tests the getters through the entity.
	e->RenderEntity(Renderer, msm, txm);
}