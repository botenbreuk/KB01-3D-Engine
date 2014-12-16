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
	window->CreateWnd();
	window->CreateWnd();
	window->StartWnd();

	delete kernel, window;
}