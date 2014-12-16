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
	void SetWinClass();
	void CreateWnd();
	void StartWnd();
	static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

};

#endif