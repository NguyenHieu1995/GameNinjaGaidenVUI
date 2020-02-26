#include "CStateMenu.h"
#include "CDebug.h"
#include "CStateFirst.h"
#include "CStateEnd.h"
#include "CStateThird.h"

CStateMenu::CStateMenu() : CState()
{
	_iCount = 10;
}

CStateMenu::~CStateMenu()
{
}

void CStateMenu::Init()
{
	DebugOut(L"Menu State Init!\n");
}

void CStateMenu::Update(DWORD dt)
{
	DebugOut(L"Menu State Update!\n");

	if (_iCount <= 1)
	{
		CStates::GetInstance()->SwitchState(new CStateFirst());
		//CStates::GetInstance()->SwitchState(new CStateThird());
	}
	_iCount--;
}
void CStateMenu::Render()
{
	DebugOut(L"Menu State Render!\n");
}

void CStateMenu::Exit()
{
	DebugOut(L"Menu State Exit!\n");
}