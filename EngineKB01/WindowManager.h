#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include <list>
#include "Window.h"
#include "Scene.h"

class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	Window* CreateNewWindow();//Creates a new Window.
private:
	std::list<Window*> _windows;
};

#endif