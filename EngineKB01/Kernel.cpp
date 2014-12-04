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