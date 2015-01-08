#include "DirectXInputHandler.h"


DirectXInputHandler::DirectXInputHandler()
{
}


DirectXInputHandler::~DirectXInputHandler()
{
}


void DirectXInputHandler::InitInput()
{
/*
	// Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    if( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,
                                         IID_IDirectInput8, ( VOID** )&g_pDI, NULL ) ) )

    // Retrieve the system mouse
    if( FAILED( g_pDI->CreateDevice( GUID_SysMouse, &g_pMouse, NULL ) ) )
    {
        MessageBox( NULL, TEXT( "Mouse not found. The sample will now exit." ),
                    TEXT( "DirectInput Sample" ),
                    MB_ICONERROR | MB_OK );
        EndDialog( hDlg, 0 );
        return;
    }

    // A data format specifies which controls on a device we are interested in,
    // and how they should be reported. This tells DInput that we will be
    // passing a MouseState structure to IDirectInputDevice::GetDeviceState().
    if( FAILED( g_pMouse->SetDataFormat( &g_dfMouse ) ) )
	{
	}

    // Set the cooperative level to let DInput know how this device should
    // interact with the system and with other DInput applications.
    if( FAILED( g_pMouse->SetCooperativeLevel( hDlg, DISCL_NONEXCLUSIVE |
                                                    DISCL_FOREGROUND ) ) )
	{
        return;
	}
*/
}
