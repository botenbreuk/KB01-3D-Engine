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
	static LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );//Handles some of the possible messages this Window can receive.
	HWND GetHWND();

	void UpdateTitle(std::string title);

private:
	void SetWinClass();//
	void Initialize();//Initialises the Window for use.
	HWND _window;//
};

#endif