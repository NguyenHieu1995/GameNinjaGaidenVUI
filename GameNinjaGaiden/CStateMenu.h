#pragma once

#include "CStates.h"

class CStateMenu : public CState
{
public:
	CStateMenu();
	~CStateMenu();

private:
	int _iCount;

public:
	void Init();
	void Update(DWORD dt);
	void Render();
	void Exit();
};

