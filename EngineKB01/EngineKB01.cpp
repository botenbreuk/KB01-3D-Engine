#include <iostream>

#include "Kernel.h"

///Starts up the engine.
int main()
{
	//Makes a Kernel object.
	Kernel* kernel = new Kernel();
    
	//initialises the components of the Kernel.
	kernel->Initialize();

	//Starts up the basic loop of the Engine.
	kernel->Run();

	//Cleans up the components of the Kernel.
	kernel->CleanUp();

	//Cleans up the Kernel itself.
	delete kernel;
}