#include "DirectXInputHandler.h"


DirectXInputHandler::DirectXInputHandler()
{
}


DirectXInputHandler::~DirectXInputHandler()
{
}


void DirectXInputHandler::InitInput(HWND hDlg)
{
	struct MouseState
	{
		LONG lAxisX;
		LONG lAxisY;
		BYTE abButtons[3];
		BYTE bPadding;       // Structure must be DWORD multiple in size.   
	};

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
	#define numMouseObjects (sizeof(g_aObjectFormats) / sizeof(DIOBJECTDATAFORMAT))

	DIDATAFORMAT            g_dfMouse =
	{
		sizeof( DIDATAFORMAT ),
		sizeof( DIOBJECTDATAFORMAT ),
		DIDF_ABSAXIS,
		sizeof( MouseState ),
		numMouseObjects,
		g_aObjectFormats
	};

	// Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    if( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, ( VOID** )&g_pDI, NULL ) ) )
	{
		return;
	}

    // Retrieve the system mouse
	if( FAILED( g_pDI->CreateDevice( GUID_SysMouse, DirectInputDevices[Mouse], NULL ) ) )
    {
        MessageBox( NULL, TEXT( "Mouse not found. The sample will now exit." ), TEXT( "DirectInput Sample" ), MB_ICONERROR | MB_OK );
        EndDialog( hDlg, 0 );
        return;
    }

    // A data format specifies which controls on a device we are interested in,
    // and how they should be reported. This tells DInput that we will be
    // passing a MouseState structure to IDirectInputDevice::GetDeviceState().
    if( FAILED( (*DirectInputDevices[Mouse])->SetDataFormat( &g_dfMouse ) ) )
	{
	}

    // Set the cooperative level to let DInput know how this device should
    // interact with the system and with other DInput applications.
    if( FAILED( (*DirectInputDevices[Mouse])->SetCooperativeLevel( hDlg, DISCL_NONEXCLUSIVE |
                                                    DISCL_FOREGROUND ) ) )
	{
        return;
	}
}