#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include "Window.h"

class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	HWND CreateNewWindow();//Creates a new Window.
};

#endif