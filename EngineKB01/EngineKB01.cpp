#include "Log.h"
#include "DirectXRenderer.h"
#include "Scene.h"


/*
Starts up the engine.
*/
int main()
{
	//Test code for the logger.
	Log* log = new Log();
	const char* logContent = "Test";
	log->WriteLog(logContent, Log::MessageType::Info);
	std::cout << "hello world" << std::endl;

	//Makes it so the system waits for imput before shutting down the application.
	system("pause");

	//Cleans up the memory before quitting the application.
	delete log;
}