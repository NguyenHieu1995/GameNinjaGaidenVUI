#include "CStates.h"

CStates* CStates::_pInstance = NULL;

CStates* CStates::GetInstance()
{
	if (_pInstance == NULL)
	{
		_pInstance = new CStates();
	}

	return _pInstance;
}

CStates::CStates()
{
	_pCurrentState = NULL;
	_pNextState = NULL;
}

CStates::~CStates()
{
	if (_pNextState != _pCurrentState)
	{
		if (_pNextState != NULL)
		{
			_pNextState->Exit();
			delete _pNextState;
			_pNextState = NULL;
		}
	}

	if (_pCurrentState != NULL)
	{
		_pCurrentState->Exit();
		delete _pCurrentState;
		_pCurrentState = NULL;
	}

}

void CStates::Update(bool isPause, DWORD dt)
{
	if (_pCurrentState != _pNextState)
	{
		if (NULL != _pCurrentState)
		{
			_pCurrentState->Exit();
			delete _pCurrentState;
			_pCurrentState = NULL;
		}
		
		if (NULL != _pNextState)
		{
			_pNextState->Init();
		}

		_pCurrentState = _pNextState;
	}

	if (NULL != _pCurrentState)
	{
		if (false == isPause)
		{
			_pCurrentState->Update(dt);
		}
		_pCurrentState->Render();
	}
}

void CStates::SwitchState(CState* nextState)
{
	_pNextState = nextState;
}