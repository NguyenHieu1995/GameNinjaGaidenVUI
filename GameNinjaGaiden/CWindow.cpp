#include "CWindow.h"

CWindow *CWindow::_instance = NULL;

CWindow::CWindow()
{
	this->_hInstance = NULL;
	this->_hWnd = NULL;
}


CWindow::~CWindow()
{
	
}

CWindow *CWindow::GetInstance()
{
	if (_instance == NULL)
		_instance = new CWindow();

	return _instance;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

bool CWindow::CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	if (this->_hWnd == NULL)
	{
		this->_hInstance = hInstance;

		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = hInstance;

		wc.lpfnWndProc = (WNDPROC)WinProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = WINDOW_CLASS_NAME;
		wc.hIconSm = NULL;

		RegisterClassEx(&wc);

		this->_hWnd = CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			this->_hInstance,
			NULL);

		if (!this->_hWnd)
		{
			OutputDebugString(L"[ERROR] CreateWindow faiiled!");
			DWORD ErrCode = GetLastError();
			return false;
		}

		ShowWindow(this->_hWnd, nCmdShow);
		UpdateWindow(this->_hWnd);
	}
	//return this->_hWnd;

	return true;
}

HWND CWindow::GetHwnd()
{
	return this->_hWnd;
}

HINSTANCE CWindow::GetHIntance()
{
	return this->_hInstance;
}