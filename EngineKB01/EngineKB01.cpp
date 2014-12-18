#include <iostream>

#include "Kernel.h"

/*
Starts up the engine.
*/
int main()
{
	Kernel* kernel = new Kernel();
    
	kernel->Initialize();
	kernel->Run();
	kernel->CleanUp();

	delete kernel;
}