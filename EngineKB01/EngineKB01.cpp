#include <iostream>

#include "Kernel.h"

///Starts up the engine.
int main()
{
	//Makes a Kernel object.
	Kernel* kernel = new Kernel();

	//Starts up the basic loop of the Engine.
	kernel->RunBasic();

	//Cleans up the components of the Kernel.
	kernel->CleanUp();

	//Cleans up the Kernel itself.
	delete kernel;
}