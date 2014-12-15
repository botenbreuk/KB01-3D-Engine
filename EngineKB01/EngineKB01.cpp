#include <iostream>

#include "Kernel.h"
#include "Window.h"

/*
Starts up the engine.
*/
int main()
{
	Kernel* kernel = new Kernel();
    
	Window* window = new Window();


	delete kernel, window;
}