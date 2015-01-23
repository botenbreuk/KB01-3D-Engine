#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

#include <Windows.h>
#include "LoggerPool.h"
#include "Window.h"

class InputHandler
{
public:
	virtual ~InputHandler() = 0;
	virtual void InitInput(Window* w) = 0;//Initialises the input.
	virtual void FreeInput() = 0;//Frees the initialised input.
	virtual void Update() = 0;//

protected:
	Logger* _logger;//For writing a logfile.
	Window* _window;
	HWND _hDlg;

	virtual void InitMouse() = 0;//Initialises the system mouse.
	virtual void InitKeyboard() = 0;//Initialises the system keyboard.

	virtual void ReadMouseData() = 0;//Reads out the mouse data and acts accordingly.
	virtual void ReadKeyboardData() = 0;//Reads out the keyboard data and acts accordingly.


};

#endif