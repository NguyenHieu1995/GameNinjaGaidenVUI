#pragma once
#include <Windows.h>
#include "CConstant.h"
#include "CDebug.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class CWindow
{
private:
	HINSTANCE _hInstance;	// Instance of window current
	HWND _hWnd;				// Hwnd of window create
	int _iHeight;			// Height of window game
	int _iWidth;			// Width of window game

	static CWindow *_instance; // 

	CWindow();

public:
	~CWindow();

public:
	// Create Window of Game
	bool CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);

	static CWindow *GetInstance();
	HWND GetHwnd();
	HINSTANCE GetHIntance();
};
