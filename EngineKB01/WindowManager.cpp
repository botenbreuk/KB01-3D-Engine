#include "WindowManager.h"

WindowManager::WindowManager()
{

}

WindowManager::~WindowManager()
{

}

/*
Creates a new Window.
*/
HWND WindowManager::CreateNewWindow()
{
	Window* window = new Window();
	window->UpdateTitle("Voorbeeldtitel");
	return window->GetHWND();
}