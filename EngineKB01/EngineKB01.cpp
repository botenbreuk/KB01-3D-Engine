#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>

#include "Log.h"

int main()
{
	Log* log = new Log();
	const char* logContent = "Test";
	log->WriteLog(logContent, Log::MessageType::Info);
	std::cout << "hello world" << std::endl;
	system("pause");

	delete log;
}