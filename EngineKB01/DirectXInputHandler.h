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
	void InitInput(Window* w);//Initialises DirectInput.
	void FreeInput();//Frees up DirectInput.
	void Update();//Runs the input cycles.

	struct KeyboardState
	{
		byte state[256];
	};

private:
	LPDIRECTINPUT8          _g_pDI; // DirectInput interface
	std::map<InputHardware, LPDIRECTINPUTDEVICE8> _directInputDevices;//The devices hooked up to this computer.

	void InitMouse();//Initialises the system mouse.
	void InitKeyboard();//Initialises the system keyboard.

	void ReadMouseData();//Reads the mouse data and acts accordingly.
	void ReadKeyboardData();//Reads the keyboard data and acts accordingly.

	char* TranslateKeyboardData(KeyboardState keyboardState);//Translates the keyboard data to a char*.
};

#endif