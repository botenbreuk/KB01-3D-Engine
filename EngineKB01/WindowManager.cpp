#include "WindowManager.h"

WindowManager::WindowManager()
{

}

WindowManager::~WindowManager()
{

}

HWND WindowManager::CreateNewWindow()
{
	Window* window = new Window();
	return window->GetHWND();
}