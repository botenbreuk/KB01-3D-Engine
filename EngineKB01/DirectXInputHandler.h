#ifndef __DIRECTXINPUTHANDLER_H__
#define __DIRECTXINPUTHANDLER_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <map>

#include "InputHandler.h"

class DirectXInputHandler : public InputHandler
{
public:
	DirectXInputHandler();
	~DirectXInputHandler();
	enum InputHardware {Mouse = 0, Keyboard = 1, XboxController = 2, First = Mouse, Last = XboxController};//The different types of input hardware the handler knows and can use.
	void InitInput(HWND hDlg);//Initialises DirectInput.
	void FreeInput();//Frees up DirectInput.

private:
	LPDIRECTINPUT8          _g_pDI; // DirectInput interface
	LPDIRECTINPUTDEVICE8 _keyboard;
	std::map<InputHardware, LPDIRECTINPUTDEVICE8*> _directInputDevices;//The devices hooked up to this computer.

	void InitMouse(HWND hDlg);//Initialises the system mouse.
	void InitKeyboard(HWND hDlg);//Initialises the system keyboard.
};

#endif