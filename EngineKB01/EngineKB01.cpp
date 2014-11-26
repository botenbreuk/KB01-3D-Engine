#include <iostream>

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