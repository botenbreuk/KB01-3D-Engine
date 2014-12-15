#include "Window.h"

Window::Window()
{
	InitWindow();
}


Window::~Window()
{
}

void Window::InitWindow()
{
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, MsgProc,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(CreateSolidBrush(RGB(0, 0, 255))),
                            0, L"WindowClass", LoadIcon(0,IDI_APPLICATION) } ;
    RegisterClassEx(&wndclass);
    HWND window = CreateWindowEx( 0, L"WindowClass", L"title",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0 );

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow( window );

	MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
    {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
	}
}

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