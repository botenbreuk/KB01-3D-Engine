#include "Window.h"

Window::Window()
{
	SetWinClass();
	Initialize();
}


Window::~Window()
{

}

HWND Window::GetHWND()
{
	return _window;
}

///Registers a Win class.
void Window::SetWinClass()
{
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, MsgProc, 0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION), LoadCursor(0,IDC_ARROW), HBRUSH(CreateSolidBrush(RGB(0, 0, 0))), 0, L"WindowClass", LoadIcon(0,IDI_APPLICATION) };
    RegisterClassEx(&wndclass);
}

///Initialises the Window for use.
void Window::Initialize()
{
    _window = CreateWindowEx( 0, L"WindowClass", L"title",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0 );

	ShowWindow(_window, SW_SHOWDEFAULT);
	UpdateWindow( _window );
}

///Updates the title of the window.
///title: The new title for the window.
void Window::SetTitle(std::string title)
{
	/*
	Converts string to LCWSTR
	*/
	std::wstring stemp = std::wstring(title.begin(), title.end());
	LPCWSTR sw = stemp.c_str();

	SetWindowText(_window, sw);
}

///Sets the size of the window
void Window::SetSize(int width, int length)
{
	MoveWindow(_window, 100, 100, width, length, TRUE);
}

///Handles some of the possible messages this Window can receive.
///hWnd:
///msg: The message to be handled.
///wParam:
///lParam:
LRESULT CALLBACK Window::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_LBUTTONDOWN:
            std::cout << "\nmouse left button down at (" << LOWORD(lParam)
                      << ',' << HIWORD(lParam) << ")\n" ;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}