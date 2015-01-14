#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

#include <Windows.h>

class InputHandler
{
public:
	virtual ~InputHandler() = 0;
	virtual void InitInput(HWND hDlg) = 0;
};

#endif