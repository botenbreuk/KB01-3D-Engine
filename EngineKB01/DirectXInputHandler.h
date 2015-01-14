#ifndef __DIRECTXINPUTHANDLER_H__
#define __DIRECTXINPUTHANDLER_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <map>

#include "inputhandler.h"

class DirectXInputHandler : public InputHandler
{
public:
	DirectXInputHandler();
	~DirectXInputHandler();
	enum InputHardware {Mouse, Keyboard, XboxController};//The different types of input hardware the handler knows and can use.
	void InitInput(HWND hDlg);
	

private:
	LPDIRECTINPUT8          g_pDI; // DirectInput interface
	std::map<InputHardware, LPDIRECTINPUTDEVICE8*> DirectInputDevices;//The devices hooked up to this computer.
};

#endif