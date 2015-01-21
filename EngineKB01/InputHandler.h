#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

#include <Windows.h>
#include "LoggerPool.h"

class InputHandler
{
public:
	virtual ~InputHandler() = 0;
	virtual void InitInput(HWND hDlg) = 0;//Initialises the input.
	virtual void FreeInput() = 0;//Frees the initialised input.
	virtual void Update() = 0;//

	bool GetMouseButton0();//

protected:
	Logger* _logger;//For writing a logfile.

	HWND _hDlg;

	virtual void InitMouse() = 0;//Initialises the system mouse.
	virtual void InitKeyboard() = 0;//Initialises the system keyboard.

	virtual void ResetMouseData() = 0;

	virtual void SetMouseData() = 0;

	long _mousePositionX;
	long _mousePositionY;
	bool _mouseButton0;
	bool _mouseButton1;
	bool _mouseButton2;
};

#endif