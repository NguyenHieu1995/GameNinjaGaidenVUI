#include "CStateIntro.h"
#include "CDebug.h"
#include "CStateMenu.h"

CStateIntro::CStateIntro() : CState()
{
	_iCount = 0;
}

CStateIntro::~CStateIntro()
{

}

void CStateIntro::Init()
{
	DebugOut(L"Init State Intro!\n");
}

void CStateIntro::Update(DWORD dt)
{
	_iCount++;

	if (_iCount >= 10)
	{
		CStates::GetInstance()->SwitchState(new CStateMenu());
	}

	DebugOut(L"Update State Intro!\n");
}

void CStateIntro::Render()
{
	DebugOut(L"Render State Intro!\n");
}

void CStateIntro::Exit()
{
	DebugOut(L"Exit State Intro!\n");
}