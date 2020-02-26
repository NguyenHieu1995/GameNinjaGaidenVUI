#pragma once

#include "CStates.h"

class CStateIntro : public CState
{
public:
	CStateIntro();
	~CStateIntro();

private:
	int _iCount;

public:
	void Init();
	void Update(DWORD dt);
	void Render();
	void Exit();
};