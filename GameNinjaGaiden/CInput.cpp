#include "CInput.h"

CInput* CInput::_instance = NULL;

CInput* CInput::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CInput();
	}

	return _instance;
}

CInput::CInput()
{
	_input = NULL;
	_keyboard = NULL;
	_mouse = NULL;
}

CInput::~CInput()
{
	if (_keyHandler != NULL)
	{
		delete _keyHandler;
		_keyHandler = NULL;
	}
}

//void CInput::InitKeyboard()
//{
//	HRESULT hr;
//
//	_hInstance = CWindow::GetInstance()->GetHItance();
//	_hWnd = CWindow::GetInstance()->GetHwnd();
//	_screenHeight = SCREEN_HEIGHT;
//	_screenWidth = SCREEN_WIDTH;
//	_mouseX = 0;
//	_mouseY = 0;
//
//
//	// Init Input
//	hr = DirectInput8Create(
//		_hInstance,
//		DIRECTINPUT_VERSION,
//		IID_IDirectInput8,
//		(void**)&_input,
//		NULL);
//
//	if (FAILED(hr))
//	{
//		DebugOut(L"[ERROR] Initialize Direct Input Object failed!");
//		return;
//	}
//
//	hr = _input->CreateDevice(GUID_SysKeyboard, &_device, NULL);
//	if (FAILED(hr))
//	{
//		DebugOut(L"[ERROR] Initialize Direct Input Device failed!");
//		return;
//	}
//
//	hr = _device->SetDataFormat(&c_dfDIKeyboard);
//	if (FAILED(hr))
//	{
//		DebugOut(L"[ERROR] Set Data Format failed!");
//		return;
//	}
//
//	hr = _device->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
//	if (FAILED(hr))
//	{
//		DebugOut(L"[ERROR] Set CooperativeLevel failed!");
//		return;
//	}
//
//	DIPROPDWORD dipdw;
//
//	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
//	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
//	dipdw.diph.dwObj = 0;
//	dipdw.diph.dwHow = DIPH_DEVICE;
//	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size
//
//	hr = _device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
//
//	hr = _device->Acquire();
//	if (FAILED(hr))
//	{
//		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
//		return;
//	}
//
//	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
//
//	// Init Keyboard
//
//	// Init Mouse
//	hr = _input->CreateDevice(GUID_SysMouse, &_mouse, NULL);
//	if (FAILED(hr))
//	{
//
//		return;
//	}
//
//	hr = _mouse->SetDataFormat(&c_dfDIMouse);
//	if (FAILED(hr))
//	{
//
//		return;
//	}
//
//	hr = _mouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND || DISCL_NONEXCLUSIVE);
//	if (FAILED(hr))
//	{
//
//		return;
//	}
//
//	hr = _mouse->Acquire();
//	if (FAILED(hr))
//	{
//
//		return;
//	}
//
//}

bool CInput::Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight, LPCKEYBOARDEVENTHANDLER keyHandler)
{
	_keyHandler = keyHandler;

	HRESULT hr;

	// Store the screen size which will be used for positioning the mouse cursor.
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_hWnd = hWnd;
	_hInstance = hInstance;

	// Initialize the location of the mouse on the screen.
	_mouseX = 0;
	_mouseY = 0;

	_mousePosX = 0;
	_mousePosY = 0;

	// Initialize the main direct input interface.
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_input, NULL);
	if (FAILED(hr))
	{
		return false;
	}
	// ==========
	// KEYBOARD
	// ==========
	// Initialize the direct input interface for the keyboard.
	hr = _input->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	hr = _keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	hr = _keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		return false;
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = _keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	// Now acquire the keyboard.
	hr = _keyboard->Acquire();
	if (FAILED(hr))
	{
		return false;
	}


	// ========
	// Mouse
	// ========
	// Initialize the direct input interface for the mouse.
	hr = _input->CreateDevice(GUID_SysMouse, &_mouse, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	//DIDATAFORMAT DIDataFormat;

	//CopyMemory(&DIDataFormat, &c_dfDIMouse2, sizeof(DIDataFormat));
	//DIDataFormat.dwFlags = DIDF_RELAXIS; // or DIDF_ABSAXIS
	//hr = _mouse->SetDataFormat(&DIDataFormat);

	// Set the data format for the mouse using the pre-defined mouse data format.
	hr = _mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	hr = _mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		return false;
	}

	// Acquire the mouse.
	hr = _mouse->Acquire();
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void CInput::ShutDown()
{
	// Release mouse
	if (_mouse != NULL)
	{
		_mouse->Unacquire();
		_mouse->Release();
		_mouse = NULL;
	}

	// Release keyboard
	if (_keyboard != NULL)
	{
		_keyboard->Unacquire();
		_keyboard->Release();
		_keyboard = NULL;
	}

	// Release direct input
	if (_input != NULL)
	{
		_input->Release();
		_input = NULL;
	}
	return;
}


bool CInput::Update(CGameObject* object)
{
	// Read the current state of the keyboard.
	if (!ReadKeyboard())
	{
		return false;
	}
	// Read the current state of the mouse.
	if (!ReadMouse())
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput(object);

	return true;
}


bool CInput::ReadKeyboard()
{
	HRESULT hr;

	// Read the keyboard device.
	hr = _keyboard->GetDeviceState(sizeof(_keyboardState), (LPVOID)&_keyboardState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h;
			h = _keyboard->Acquire();
			if (SUCCEEDED(h))
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool CInput::ReadMouse()
{
	HRESULT hr;

	// Read the mouse device.
 	hr = _mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_mouseState);
	if (FAILED(hr))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h;
			h = _mouse->Acquire();

			if (SUCCEEDED(h))
			{
				DebugOut(L"[INFO] Mouse re-acquired!\n");
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void CInput::ProcessInput(CGameObject* object)
{
	HRESULT hr;

	_keyHandler->KeyState((BYTE*)_keyboardState, object);


	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = _keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] Get Device Data Failed!");
	}

	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _keyEvents[i].dwOfs;
		int KeyState = _keyEvents[i].dwData;

		if ((KeyState & 0x80) > 0)
		{
			_keyHandler->OnKeyDown(KeyCode, object);
		}
		else
		{
			_keyHandler->OnKeyUp(KeyCode, object);
		}
	}


	_mouseX += _mouseState.lX;
	_mouseY += _mouseState.lY;

	

	if (_mouseX < 0)
	{
		_mouseX = 0;
	}

	if (_mouseY < 0)
	{
		_mouseY = 0;
	}

	if (_mouseX > _screenWidth)
	{
		_mouseX = _screenWidth;
	}

	if (_mouseY > _screenHeight)
	{
		_mouseY = _screenHeight;
	}


	
	GetCursorPos(&_pointPointer);
	////DebugOut(L"\n[INFO] Mouse: X = %d, Y = %d", point.x, point.y);

	
	GetClientRect(_hWnd, (LPRECT)&_rectClientWindow); // get client coords
	ClientToScreen(_hWnd, (LPPOINT)&_rectClientWindow.left); // convert top-left
	ClientToScreen(_hWnd, (LPPOINT)&_rectClientWindow.right); // convert bottom-right
	//DebugOut(L"\n[INFO] Mouse: X = %d, Y = %d", rect.left, rect.top);
	//SetCursorPos(rect.left, rect.top);

	if (_pointPointer.x < _rectClientWindow.left)
	{
		_mousePosX = 0;
	}
	else
	{
		if (_pointPointer.x > _rectClientWindow.right)
		{
			_mousePosX = _screenWidth;
		}
		else
		{
			_mousePosX = _pointPointer.x - _rectClientWindow.left;
		}
	}

	if (_pointPointer.y < _rectClientWindow.top)
	{
		_mousePosY = 0;
	}
	else
	{
		if (_pointPointer.y > _rectClientWindow.bottom)
		{
			_mousePosY = _screenHeight;
		}
		else
		{
			_mousePosY = _pointPointer.y - _rectClientWindow.top;
		}
	}
	
	if (_mouseState.rgbButtons[0] & 0x80)
		DebugOut(L"\n[INFO] Click mouse left");

	if (_mouseState.rgbButtons[1] & 0x80)
		DebugOut(L"\n[INFO] Click mouse rigt");

	//DebugOut(L"\n[INFO] Mouse: X = %d, Y = %d", _mouseX, _mouseY);


	return;
}



//void CInput::ProcessKeyboard()
//{
//	HRESULT hr;
//
//	hr = _device->GetDeviceState(sizeof(_keyboardState), _keyboardState);
//	if (FAILED(hr))
//	{
//		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
//		{
//			HRESULT h = _device->Acquire();
//			if (SUCCEEDED(h))
//			{
//				DebugOut(L"[INFO] Keyboard re-acquired!\n");
//			}
//			else
//			{
//				return;
//			}
//		}
//		else
//		{
//			return;
//		}
//	}
//
//	//DWORD dwElements = KEYBOARD_BUFFER_SIZE;
//	//hr = _device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvents, &dwElements, 0);
//	//if (FAILED(hr))
//	//{
//	//	DebugOut(L"[ERROR] Get Device Data Failed!");
//	//}
//
//	//for (DWORD i = 0; i < dwElements; i++)
//	//{
//	//	int KeyCode = _keyEvents[i].dwOfs;
//	//	int KeyState = _keyEvents[i].dwData;
//
//	//	if ((KeyState & 0x80) > 0)
//	//	{
//	//		//DebugOut(L"\n[INFO] keyCode %d", KeyCode);
//	//		//DebugOut(L"\n[INFO] keyState %d", KeyState);
//	//	}
//	//	else
//	//	{
//
//	//	}
//	//}
//
//}

bool CInput::IsKeyDown(int keyCode)
{
	return (_keyboardState[keyCode] & 0x80) > 0;
}