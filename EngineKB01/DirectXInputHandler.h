#ifndef __DIRECTXINPUTHANDLER_H__
#define __DIRECTXINPUTHANDLER_H__

#include "inputhandler.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <map>

class DirectXInputHandler : public InputHandler
{
public:
	DirectXInputHandler();
	~DirectXInputHandler();
	enum InputHardware {Mouse, Keyboard, XboxController};//The different types of input hardware the handler knows and can use.
	void InitInput();
	//std::map<InputHardware, DirectInputDevice*> DirectInputDevices;

private:
//	LPDIRECTINPUT8          g_pDI = NULL; // DirectInput interface       
//	LPDIRECTINPUTDEVICE8    g_pMouse = NULL; // Device interface
};

#endif