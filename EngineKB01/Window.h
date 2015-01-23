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

	void SetTitle(std::string title);//Sets the title for the window.
	void SetSize(int width, int length);//Sets the size of window

	void LeftMouseButtonPressed();
	void RightMouseButtonPressed();
	void MiddleMouseButtonPressed();

	void KeyTyped(char* c);

private:
	void SetWinClass();//Registers a Win class
	void Initialize();//Initialises the Window for use.
	HWND _window;//Window handler.
};

#endif