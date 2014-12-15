#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <windows.h>
#include <windowsx.h>

#include "Scene.h"

class Window
{
public:
	Window();
	~Window(); 

private:
	void InitWindow();
	static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	
	Scene* scene;
};

#endif