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

protected:
	Logger* _logger;//For writing a logfile.
};

#endif