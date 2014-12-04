#include "Kernel.h";

/*
Starts up the engine.
*/
int main()
{
	//Creates a new kernel to initialise the engine.
	Kernel* kernel = new Kernel();
	
	//Tests the logger.
	kernel->TestLog();

	//Makes it so the system waits for imput before shutting down the application.
	system("pause");

	//Cleans up the memory before quitting the application.
	delete kernel;

	//Exits the application correctly.
	return 0;
}