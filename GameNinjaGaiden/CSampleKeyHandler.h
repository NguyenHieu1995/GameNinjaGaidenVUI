#pragma once

#include <Windows.h>
#include "CKeyboardEventHandler.h"
#include "CGameObject.h"
#include "CInput.h"
#include "CConstant.h"

class CSampleKeyHandler : public CKeyboardEventHandler
{

public:
	CSampleKeyHandler();
	~CSampleKeyHandler();
	void KeyState(BYTE* states, CGameObject* object);
	void OnKeyDown(int keycode, CGameObject* object);
	void OnKeyUp(int keycode, CGameObject* object);
};