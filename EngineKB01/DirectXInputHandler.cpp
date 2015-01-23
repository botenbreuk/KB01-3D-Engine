#include "DirectXInputHandler.h"

	//Defines the data for the state of the mouse.
	struct MouseState
	{
		LONG lAxisX;
		LONG lAxisY;
		BYTE abButtons[3];
		BYTE bPadding;       // Structure must be DWORD multiple in size.
	};

	//The info that comes from the mouse.
	DIOBJECTDATAFORMAT g_aObjectFormats[] =
	{
		{ &GUID_XAxis, FIELD_OFFSET( MouseState, lAxisX ),    // X axis
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &GUID_YAxis, FIELD_OFFSET( MouseState, lAxisY ),    // Y axis
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ 0, FIELD_OFFSET( MouseState, abButtons[0] ),        // Button 0
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ 0, FIELD_OFFSET( MouseState, abButtons[1] ),        // Button 1 (optional)
			DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 },
		{ 0, FIELD_OFFSET( MouseState, abButtons[2] ),        // Button 2 (optional)
			DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 }
	};

	//Defines the number of mice.
	#define numMouseObjects (sizeof(g_aObjectFormats) / sizeof(DIOBJECTDATAFORMAT))

	//The dataformat for the mice.
	DIDATAFORMAT            g_dfMouse =
	{
		sizeof( DIDATAFORMAT ),
		sizeof( DIOBJECTDATAFORMAT ),
		DIDF_ABSAXIS,
		sizeof( MouseState ),
		numMouseObjects,
		g_aObjectFormats
	};

DirectXInputHandler::DirectXInputHandler()
{
	_logger = LoggerPool::GetInstance()->GetLogger("Input");
}


DirectXInputHandler::~DirectXInputHandler()
{
}

///Initialises DirectInput.
///hDlg: The window handler for which the input is initialised.
void DirectXInputHandler::InitInput(HWND hDlg)
{
	_hDlg = hDlg;

	//Gives the window the focus so it can find the input devices.
	HWND WINAPI SetFocus(_hDlg);

	// Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    if( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, ( VOID** )&_g_pDI, NULL ) ) )
	{
		return;
	}
	//InitKeyboard();
	//TODO: Implement InitXBoxController(hDlg);

	//Writes an info message to the log.
	_logger->WriteLog("DirectInput initialised.", Logger::MessageType::Info);

	//Initialises the different devices
	InitMouse();
}

///Initialises the system mouse.
///hDlg: The window for which the mouse is initialised.
void DirectXInputHandler::InitMouse()
{

    // Retrieve the system mouse
	if( FAILED( _g_pDI->CreateDevice( GUID_SysMouse, &_directInputDevices[Mouse], NULL ) ) )
    {
        MessageBox( NULL, TEXT( "Mouse not found." ), TEXT( "Engine LNK2019" ), MB_ICONERROR | MB_OK );
        EndDialog( _hDlg, 0 );
        return;
    }

    // A data format specifies which controls on a device we are interested in,
    // and how they should be reported. This tells DInput that we will be
    // passing a MouseState structure to IDirectInputDevice::GetDeviceState().
    if( FAILED( (_directInputDevices[Mouse])->SetDataFormat( &g_dfMouse ) ) )
	{
		return;
	}

    // Set the cooperative level to let DInput know how this device should
    // interact with the system and with other DInput applications.
    if( FAILED( (_directInputDevices[Mouse])->SetCooperativeLevel( _hDlg, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) )
	{
        return;
	}

	ResetMouseData();

	//Writes an info message to the log.
	_logger->WriteLog("Mouse initialised.", Logger::MessageType::Info);
}

///Initialises the system keyboard.
///hDlg: The window for which the keyboard is initialised.
void DirectXInputHandler::InitKeyboard()
{
	// Retrieve the system keyboard
	if( FAILED( _g_pDI->CreateDevice( GUID_SysKeyboard, &_directInputDevices[Mouse], NULL ) ) )
    {
        MessageBox( NULL, TEXT( "Keyboard not found." ), TEXT( "Engine LNK2019" ), MB_ICONERROR | MB_OK );
        EndDialog( _hDlg, 0 );
        return;
    }

	//Writes an info message to the log.
	_logger->WriteLog("Keyboard initialised.", Logger::MessageType::Info);
}

void DirectXInputHandler::Update()
{
	SetMouseData();
}

void DirectXInputHandler::ResetMouseData()
{
	this->_mouseButton0 = false;
	this->_mouseButton1 = false;
	this->_mouseButton2 = false;
	this->_mousePositionX = 0;
	this->_mousePositionY = 0;
}

void DirectXInputHandler::SetMouseData()
{
	HRESULT hr;
	TCHAR strText[128] = {0}; // Device state text
    MouseState mousestate;           // Custom mouse state 

    static POINT pOrigin = {0};           // Initial position
    static BOOL bInitialized = FALSE;    // Indicates offsets are valid

	if( NULL == _directInputDevices[Mouse] )
        return;

	// Poll the device to read the current state
    hr = _directInputDevices[Mouse]->Poll();
    if( FAILED( hr ) )
    {
        // DInput is telling us that the input stream has been
        // interrupted. We aren't tracking any state between polls, so
        // we don't have any special reset that needs to be done. We
        // just re-acquire and try again.
        hr = _directInputDevices[Mouse]->Acquire();
        while( hr == DIERR_INPUTLOST )
            hr = _directInputDevices[Mouse]->Acquire();

        // hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
        // may occur when the app is minimized or in the process of 
        // switching, so just try again later 
        return;
    }

	// Get the input's device state
	if(FAILED(hr = _directInputDevices[Mouse]->GetDeviceState( sizeof( MouseState ), &mousestate )))
		return; // The device should have been acquired during the Poll()

	// The initial mouse position should be subracted from the current point. 
    if( !bInitialized )
    {
        bInitialized = TRUE;
        pOrigin.x = mousestate.lAxisX;
        pOrigin.y = mousestate.lAxisY;
    }

	std::cout << "x:" << mousestate.lAxisX << std::endl << "y:" << mousestate.lAxisY << std::endl;

    /*// Store cursor position
    POINT pt;
    GetCursorPos( &pt );
    ScreenToClient( _hDlg, &pt );
	_mousePositionX = (long)pt.x;
    _mousePositionY = (long)pt.y;*/

	// Get pressed keys
	strText[0] = 0;
    for ( int i = 0; i < 3; i++ )
    {
        if ( mousestate.abButtons[i] & 0x80 )
        {
			std::cout << mousestate.abButtons[i];
        }
    }
}

///Cleans up the input devices and the interface.
void DirectXInputHandler::FreeInput()
{
	//Defines the safe release function.
	#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
	
	//Loops through the hardware map and unaquires all the hardware that is aquired.
	for(int i = First; i <= Last; i++)
	{
		if((_directInputDevices[(InputHardware)i]))
		{
			(_directInputDevices[(InputHardware)i])->Unacquire();
			SAFE_RELEASE((_directInputDevices[(InputHardware)i]));
		}
	}

	//Releases the DirectInput interface.
	SAFE_RELEASE(_g_pDI);

	//Writes an info message to the log.
	_logger->WriteLog("DirectInput freed.", Logger::MessageType::Info);
}