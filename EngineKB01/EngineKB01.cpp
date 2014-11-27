#include <iostream>
#include "Renderer.h"
#include "Log.h"
#include "DirectXRenderer.h"

int main()
{
	Renderer* renderer = new DirectXRenderer();

	Log* log = new Log();
	const char* logContent = "Test";
	log->WriteLog(logContent, Log::MessageType::Info);
	std::cout << "hello world" << std::endl;
	system("pause");

	delete log;
}