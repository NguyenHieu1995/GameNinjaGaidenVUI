#pragma once

#include <Windows.h>
#include "CGameObject.h"

class CKeyboardEventHandler
{
public:
	virtual void KeyState(BYTE* states, CGameObject* object) = 0;
	virtual void OnKeyDown(int keycode, CGameObject* object) = 0;
	virtual void OnKeyUp(int keycode, CGameObject* object) = 0;
};

typedef CKeyboardEventHandler* LPCKEYBOARDEVENTHANDLER;