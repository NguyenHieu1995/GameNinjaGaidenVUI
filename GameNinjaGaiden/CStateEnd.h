#pragma once

#include "CStates.h"

class CStateEnd : public CState
{
public:
	CStateEnd();
	~CStateEnd();

private:
	int _iCount;

public:
	void Init();
	void Update(DWORD dt);
	void Render();
	void Exit();
};