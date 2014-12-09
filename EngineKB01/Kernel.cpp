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
	Entity* e = new Entity("tiger");
	e->RenderEntity(Renderer, rsm);
}