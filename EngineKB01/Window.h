#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <windows.h>
#include <windowsx.h>


class Window
{
public:
	Window();
	~Window();
	static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	HWND GetHWND();

private:
	void SetWinClass();
	void Initialize();
	HWND _window;
};

#endif