#include "CGameBase.h"
#include "CStates.h"

CGameBase* CGameBase::_pInstance = NULL;

CGameBase* CGameBase::GetInstance()
{
	return _pInstance;
}

CGameBase::CGameBase()
{
	_isAlived = true;
	_isPaused = false;

	_pInstance = this;

	QueryPerformanceFrequency(&_timerFreq);
	QueryPerformanceCounter(&_timeStart);
	_fps = 0.0f;
}

CGameBase::~CGameBase()
{
	delete CStates::GetInstance();
}

void CGameBase::Pause()
{
	_isPaused = true;
}

void CGameBase::Resume()
{
	_isPaused = false;
}

void CGameBase::Exit()
{
	_isAlived = false;
}

void CGameBase::Run()
{
	while (true == _isAlived)
	{
		QueryPerformanceCounter(&_timeEnd);
		_frameTime = (float)(_timeEnd.QuadPart - _timeStart.QuadPart) / (float)_timerFreq.QuadPart;

		if (_frameTime < MIN_FRAME_TIME)
		{
			_sleepTime = (DWORD)((MIN_FRAME_TIME - _frameTime) * 1000);
			timeBeginPeriod(1);
			Sleep(_sleepTime);
			timeEndPeriod(1);
			return;
		}

		if (_frameTime > 0.0)
		{
			_fps = (_fps * 0.99f) + (0.01f / _frameTime);
		}

		if (_frameTime > MAX_FRAME_TIME)
		{
			_frameTime = MAX_FRAME_TIME;
		}

		_timeStart = _timeEnd;

		if (true == _isPaused)
		{
			CStates::GetInstance()->Update(true, DWORD(_frameTime * 1000));
		}
		else
		{
			CStates::GetInstance()->Update(false, DWORD(_frameTime * 1000));
		}
	}

	CStates::GetInstance()->SwitchState(0);
	CStates::GetInstance()->Update(false, 0);
}

bool CGameBase::IsAlive()
{
	return _isAlived;
}

bool CGameBase::IsPause()
{
	return _isPaused;
}