#include "WindowManager.h"

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{

}

///Creates a new Window.
Window* WindowManager::CreateNewWindow()
{
	Window* newWindow = new Window();
	newWindow->SetTitle("Window " + _windows.size());
	_windows.push_front(newWindow);
	return newWindow;
}