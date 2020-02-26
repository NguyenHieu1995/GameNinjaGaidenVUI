#pragma once

#include <Windows.h>
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CDebug.h"
#include "CConstant.h"
#include "CWindow.h"
#include "CKeyboardEventHandler.h"
#include "CGameObject.h"

class CInput
{
public:
	~CInput();

private:
	HINSTANCE _hInstance;
	HWND _hWnd;
	LPDIRECTINPUT8 _input;
	//LPDIRECTINPUTDEVICE8 _device; // Test Delete
	//BYTE _keyStates[256];
	
	unsigned char _keyboardState[256];
	DIMOUSESTATE _mouseState;

	LPDIRECTINPUTDEVICE8 _keyboard;
	LPDIRECTINPUTDEVICE8 _mouse;
	int _screenHeight, _screenWidth;
	int _mouseX, _mouseY;
	LPCKEYBOARDEVENTHANDLER _keyHandler;


	//=============================
	// TEST
	//=============================
	int _mousePosX, _mousePosY; // Position poiter on screen
	POINT _pointPointer;
	RECT _rectClientWindow;
	//=============================

	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];

public:
	//void InitKeyboard();
	bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight, LPCKEYBOARDEVENTHANDLER keyHandler);
	void ShutDown();
	bool Update(CGameObject* object);

	//void ProcessKeyboard();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput(CGameObject* object);
	CInput();
	static CInput* _instance;

public:
	static CInput* GetInstance();
	bool IsKeyDown(int keyCode);
};
