#include "CStateEnd.h"
#include "CDebug.h"
#include "CGameBase.h"

CStateEnd::CStateEnd() : CState()
{
	_iCount = 0;
}

CStateEnd::~CStateEnd()
{

}

void CStateEnd::Init()
{
	DebugOut(L"Init State End!\n");
}

void CStateEnd::Update(DWORD dt)
{
	_iCount++;

	if (_iCount >= 10)
	{
		CGameBase::GetInstance()->Exit();
	}

	DebugOut(L"Update State End!\n");
}

void CStateEnd::Render()
{
	DebugOut(L"Render State End!\n");
}

void CStateEnd::Exit()
{
	DebugOut(L"Exit State End!\n");
}